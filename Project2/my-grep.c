#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1024

int main(int argc, char *argv[]){
    // checking if there's no file(s) and search term
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }

    // taking the search term from the command-line arguments
    const char *term = argv[1];

    // checking if files aren't provided -> reading stdin
    if (argc == 2) {
        char line[LINE_LENGTH];

       // Reading lines from stdin until EOF (Ctrl+D)
        while (fgets(line, LINE_LENGTH, stdin) != NULL) {
            if (strstr(line, term) != NULL) {
                printf("%s", line);
            }
        }
        return 0;

    } else {
        // looping through the files
        for (int i = 2; i < argc; i++){
            FILE *file = fopen(argv[i], "r");
            if (file == NULL){
                printf("my-grep: cannot open file '%s'\n", argv[i]);
                return 1;
            }
            char line[LINE_LENGTH];

            // reading lines from the file
            while (fgets(line, LINE_LENGTH, file) != NULL){
                if (strstr(line, term) != NULL){
                    printf("%s\n", line);
                }
            }

            fclose(file);
        }
    }
    return 0;
}