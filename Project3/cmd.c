#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cmd.h"

static const internal_cmd commands[] = {
    { "exit", &cmd_exit },
    { "pwd", &cmd_pwd },
    { "cd", &cmd_cd },
};

int check_ret(char *s) {
    int ret = atoi(s);

    if (ret == 0 && strcmp("0\0", s) != 0) {
        printf("ERR: Invalid input\n"); 
        ret = -1;
    }

    return ret;
}

int cmd_cd(int argc, char (*argv)[MAX_ARG_LEN]) {
    char *d = argv[1];

    if (argc == 1) {
        d = getenv("HOME");
        if (d == NULL) {
            return -1;
        }
    }

    if (chdir(d) != 0) {
        printf("cd: no such file or directory: %s\n", d);
        return errno;
    }

    return 0;
}

int cmd_exit(int argc, char (*argv)[MAX_ARG_LEN]) {
    int ret = 0; // Default to success if no argument given

    if (argc > 1) {
        ret = check_ret(argv[1]);
        if (ret == -1) {
            printf("ERR: Invalid argument for command %s\n", argv[0]);
            return ret;
        }
    }

    fflush(stdout);
    _Exit(ret);
}

int cmd_pwd(int argc, char (*argv)[MAX_ARG_LEN]) {
    char buf[MAX_ARG_LEN];
    if (getcwd(buf, MAX_ARG_LEN) == NULL) {
        return errno;
    }
    printf("%s\n", buf);
    return 0;
}

int execute_external(int argc, char (*argv)[MAX_ARG_LEN]) {
    // TODO
    return EXIT_SUCCESS;
}

int execute_internal(int argc, char (*argv)[MAX_ARG_LEN]) {
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        internal_cmd cmd = commands[i];

        if (strcmp(cmd.cmd, argv[0]) == 0) {
            return (*cmd.callback)(argc, argv);
        }
    }

    return -1; // Command was not found, is not internal
}

