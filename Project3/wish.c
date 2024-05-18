#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include "const.h"
#include "cmd.h"

void print_prompt(void) {
    char buf[MAX_ARG_LEN];
    int is_path = 1;

    if (getcwd(buf, MAX_ARG_LEN) == NULL) {
        strcpy(buf, "INVALID");
        is_path = 0;
    }

    if (strcmp(buf, getenv("HOME")) == 0) {
        strcpy(buf, "~");
        is_path = 0;
    }

    // Calculate offset to path string where the last directory is
    // "/home/<user>/Downloads" could be printed as "Downloads"
    unsigned long i = 0;
    if (is_path) {
        i = strlen(buf);
        while (buf[i--] != '/' && i > 0) {}

        // Handle when cwd is root "/" or some dir in root, like "/home"
        if (i != 0) {
            i += 2;
        } else {
            if (strlen(buf) > 1) {
                i++;
            }
        }
    }

    strcat(buf, " $ ");
    printf("%s", buf + i);
}

void reveal(char *str, size_t *len) {
    for (size_t i = 0; i < *len; ++i) {
        switch (str[i]) {
            case '\n':
                printf("\\n");
                break;
            case '\0':
                printf("\\0");
                break;
            default:
                printf("%c", str[i]);
        }
    }
    printf("\n");
}

int execute_command(int argc, char (*argv)[MAX_ARG_LEN]) {
    int ret = execute_internal(argc, argv);
    if (ret != -1) { // Command was internal
        return ret;
    }

    if (ret != 0) {
        printf("%s: command not found\n", argv[0]);
        return ret;
    }

    // TODO: Command is external program
    return 0;
}

// Parse arguments from a string into an array by using a whitespace as 
// a delimiter. The delimiter is ignored when in quotes, and will update
// the "quote" arg with non-zero value.
//
// argv  -> parsed argument array
// str   -> string to be parsed
// argc  -> num of args
// quote -> can whitespace be ignored?
void argparse(char (*argv)[MAX_ARG_LEN], char *str, int *argc, int *quote) {
    int len = *quote - 1; // Lenght of curren argument that is being parsed
    bool split = false;

    if (len < 0) {
        len = 0;
    }
    
    // Current character offset from input string
    int offset = 0;

    while (str[offset++] != '\0') {
        char cur = str[offset - 1];

        if (cur == '"') {
            *quote = (int)(*quote == 0);
            continue;
        }

        if (*quote != 0) {
            (*quote)++;
        }

        // Check for whitespace characters like \n \t and spaces
        bool isWhitespace = false;
        switch (cur) {
            case ' ': case '\n': case '\t':
                isWhitespace = true;
        }

        // Consume all whitespace if not in quotes
        if (isWhitespace && *quote == 0) {
            split = true;
            continue;
        }

        // Split string
        if (split) {
            // Null terminate current arg
            argv[*argc][len] = '\0';

            split = false;
            (*argc)++;
            len = 0;
        }

        // Copy character over to the buffer
        argv[*argc][len++] = cur;
    }

    // Null terminate last arg
    argv[*argc][len] = '\0';

    // Increase argument count to include command as one argument
    (*argc)++;
}

// Read stdin and execute command right away
int run_interactive(void) {
    char current_line[MAX_ARG_LEN] = { 0 };
    char buf[MAX_ARG_ROWS][MAX_ARG_LEN] = { 0 };
    
    print_prompt();

    // Current character offset from input string
    int num_of_args = 0;
    int quote = 0; // Buffer has unclosed quote

    int ret = EXIT_SUCCESS;

    while (fgets(current_line, MAX_ARG_LEN, stdin) != NULL) {
        argparse(buf, current_line, &num_of_args, &quote);

        // If quote is left unclosed, parse lines until closing quote is found.
        // This allows for user to input multi-line text, with all whitespace
        // included.
        if (quote) {
            printf("dquote> ");
            continue;
        }

        // Ignore empty lines and comment lines that start with '#'
        if (strlen(buf[0]) != 0 && buf[0][0] != '#') {
            ret = execute_command(num_of_args, buf);
        }

        quote = 0;
        num_of_args = 0;

        print_prompt();
    }

    return ret;
}

// Run file that contains commands
int run_batch(FILE *file) {
    char line[128];
    char buf[MAX_ARG_ROWS][MAX_ARG_LEN] = {0};
    int quote = 0;

    int ret = EXIT_SUCCESS;

    while (fgets(line, MAX_ARG_LEN, file) != NULL) {
        int num_of_args = 0;

        argparse(buf, line, &num_of_args, &quote);

        // TODO: Test if multi-line quotes work here too
        //if (quote) {
        //    continue;
        //}
        if (quote) {
            printf("ERR: Unclosed quote\n->%s\n", line);
            ret = EXIT_FAILURE;
            break;
        }

        // Ignore empty lines and comment lines that start with '#'
        if (strlen(buf[0]) != 0 && buf[0][0] != '#') {
            ret = execute_command(num_of_args, buf);
        }
    }

    return ret;
}

int main(int argc, char **argv) {
    int ret = EXIT_SUCCESS;

    if (argc < 2) {
        ret = run_interactive();
    } else {
        FILE *file = fopen(argv[1], "r");
        ret = run_batch(file);
        fclose(file);
    }

    return ret;
}
