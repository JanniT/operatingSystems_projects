#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "argparse.h"
#include "const.h"

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
            printerr("%s: %s: no such file or directory\n", PROGNAME, argv[1]);
            return errno;
        }
        ret = run_shell(file);
        fclose(file);
    }

    return ret;
}
