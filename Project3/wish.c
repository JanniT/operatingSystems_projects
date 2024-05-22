#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "argparse.h"
#include "const.h"

void reveal(char *str) {
    for (size_t i = 0; i < strlen(str) + 5; ++i) {
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

    strcat(buf, "$ ");
    printf("%s", buf + i);
}

// Read stdin and execute command right away
int run_shell(FILE *file) {
    char current_line[MAX_ARG_LEN] = { 0 };

    bool interactive = (file == NULL);

    if (interactive) { 
        file = stdin;
        print_prompt();
    }

    int ret = EXIT_SUCCESS;

    while (fgets(current_line, MAX_ARG_LEN, file) != NULL) {
        parsed_command cmd = { 0, {0}, {0}, stdout, 0, false };
        ret = parse_and_execute(&cmd, current_line);

        if (interactive) { print_prompt(); }
    }

    return ret;
}

int main(int argc, char **argv) {
    int ret = EXIT_SUCCESS;

    if (argc < 2) {
        ret = run_shell(NULL);
    } else {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("wish: %s: No such file or directory\n", argv[1]);
            return errno;
        }
        ret = run_shell(file);
        fclose(file);
    }

    return ret;
}
