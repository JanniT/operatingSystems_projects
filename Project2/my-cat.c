#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// How many characters can one line contain
// -> Lines end with characters \n\0
#define LINEBUF_SIZE 4096

int main(int argc, char **argv) {
    //char *line;
    char line_buf[LINEBUF_SIZE];

    for (unsigned i = 1; i < argc; ++i) {
        FILE *fileptr;
        fileptr = fopen(argv[i], "r");

        if (fileptr == NULL) {
            printf("File '%s' could not be opened", argv[i]);
            continue;
        }

        while (fgets(line_buf, LINEBUF_SIZE, fileptr)) {
            printf("%s", line_buf);
        }

        fclose(fileptr);
    }

    if (argc == 1) {
        char *line;

        // Read stdin until Control+d
        while ((line = fgets(line_buf, LINEBUF_SIZE, stdin)) != NULL) {
            printf("%s", line);
        }
    }

    return 0;
}
