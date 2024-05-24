#include "util.h"

// Print str including hidden characters for debug purposes
void reveal(char *str) {
#ifdef DEBUG
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
#endif
}

// Print stuff to stdout
void debuglog(char *format, ...) {
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
#endif
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
        // 'i' is offset to the beginning of last dir name
        // /home/foobar/Downloads
        //              ^ i would be set there
        i = strlen(buf);
        while (buf[i--] != '/' && i > 0) {}

        // Handle when cwd is root "/" or some dir in root, like "/home"
        // /                  | /home
        // ^ i would be there |  ^ i would be set here
        if (i != 0) {
            i += 2;
        } else {
            if (strlen(buf) > 1) { i++; }
        }
    }

    // Append dollar sign and space to the end of the prompt
    strcat(buf, "$ ");
    printf("%s", buf + i);
    fflush(stdout);
}

// Print error in stderr
void printerr(char *format, ...) {
    char errbuf[MAX_ARG_LEN] = { 0 };

    va_list args;
    va_start(args, format);
    vsnprintf(errbuf, sizeof(errbuf), format, args);

    write(STDERR_FILENO, errbuf, strlen(errbuf));
}

bool is_interactive(int nextvalue) {
    static bool interactive = false;
    if (nextvalue == 1) { interactive = true; }
    if (nextvalue == 0) { interactive = false; }

    return interactive;
}

