#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// How many characters can one line contain
// -> Lines end with characters \n\0
#define LINEBUF_SIZE 8192

// Helper function that prints given string with \n and \0 showing
void reveal(char *str) {
    for (unsigned i = 0; i < strlen(str); ++i) {
        switch (str[i]) {
            case '\n':
                printf("\\n");
            case '\0':
                printf("\\0");
            default:
                printf("%c", str[i]);
        }
    }
}

int main(void) {
    // Current line buffer
    char line_buf[LINEBUF_SIZE] = {0};

    // Current line pointer
    char *line;
    // Read stdin until Control+d
    while ((line = fgets(line_buf, LINEBUF_SIZE, stdin)) != NULL) {
        reveal(line);
    }
    return 0;
}
