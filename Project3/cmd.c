#include "cmd.h"

extern char path[MAX_PATH_LEN];

// Map command names to functions
static const internal_cmd commands[] = {
    { "exit", &cmd_exit },
    { "pwd", &cmd_pwd },
    { "cd", &cmd_cd },
    { "path", &cmd_path },
};

// Check if atoi actually failed in the case the string actually was a 0
// Since atoi will return 0 when parsing failed, which is also a valid
// parsing result
int check_atoi_ret(char *s) {
    int ret = atoi(s);

    if (ret == 0 && strcmp("0\0", s) != 0) {
        printerr("%s: invalid input\n", PROGNAME);
        ret = -1;
    }

    return ret;
}

// Get or modify path
int cmd_path(parsed_command *cmd) {
    if (cmd->argc == 1) {
        printf("%s\n", path);
        return 0;
    }

    for (int i = 1; i < cmd->argc; ++i) {
        update_path(cmd->argv[i]);
    }

    return 0;
}

// Change directory
int cmd_cd(parsed_command *cmd) {
    char *d = cmd->argv[1];

    // If no argument is given, default to home dir
    if (cmd->argc == 1) {
        d = getenv("HOME");
        if (d == NULL) {
            return -1;
        }
    }

    if (chdir(d) != 0) {
        printerr("%s: no such file or directory: %s\n", cmd->argv[0], d);
        return errno;
    }

    return 0;
}

// Exit shell
int cmd_exit(parsed_command *cmd) {
    int ret = 0; // Default to success if no argument given

    if (cmd->argc > 1) {
        ret = check_atoi_ret(cmd->argv[1]);
        if (ret == -1) {
            printerr("%s: invalid argument for command %s\n", PROGNAME, cmd->argv[0]);
            return ret;
        }
    }

    fflush(stdout);
    _Exit(ret);
}

// Print current working directory
int cmd_pwd(parsed_command *cmd) {
    char buf[MAX_ARG_LEN];
    if (getcwd(buf, MAX_ARG_LEN) == NULL) {
        return errno;
    }
    printf("%s\n", buf);
    return 0;
}

// Fork and execute external program
int execute_external(parsed_command *cmd) {
    // Find program from path
    char cmdpath[MAX_ARG_LEN];
    if (which_path(cmd->argv[0], cmdpath) != 0) {
        printerr("%s: command not found: %s\n", PROGNAME, cmd->argv[0]);
        return EXIT_FAILURE;
    }

    char *cmdargs[MAX_ARG_LEN] = { 0 };
    for (int i = 0; i < cmd->argc; ++i) {
        cmdargs[i] = cmd->argv[i];
    }

    pid_t pid = 0;
    int rc = fork();
    if (rc < 0) {
        printerr("%s: forking failed\n", PROGNAME);
        return EXIT_FAILURE;
    } else if (rc == 0) {
        pid = getpid();
        if (cmd->background && is_interactive(-1) ) { printf("-> %d\n", pid); }

        if (strlen(cmd->output_redirect_filename) != 0) {
            (void)remove(cmd->output_redirect_filename);
            int fd = open(cmd->output_redirect_filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }
        execv(cmdpath, cmdargs);
    } else {
        if (!cmd->background) { wait(NULL); }
    }

    fflush(stdout);
    return errno;
}

// Execute internal command
int execute_internal(parsed_command *cmd) {
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        internal_cmd icmd = commands[i];

        if (strcmp(icmd.cmd, cmd->argv[0]) == 0) {
            return (*icmd.callback)(cmd);
        }
    }

    return -1; // Command was not found, is not internal
}

// Execute parsed command
int execute_command(parsed_command *cmd) {
    // First try if it's internal command
    int ret = execute_internal(cmd);
    if (ret != -1) { return ret; }

    // If command was internal, but failed
    if (ret > 0) {
        printerr("%s: command not found\n", cmd->argv[0]);
        return ret;
    }

    // Otherwise it can be external program
    ret = execute_external(cmd);

    return ret;
}

