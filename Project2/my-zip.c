#include <stdio.h>
#include <stdlib.h>

void my_zip(FILE *file){
    int char_current = fgetc(file);
    int count = 1;

    // checking if the given file is empty
    if (char_current == EOF) {
        return;
    }

    // looping through the file
    while (char_current != EOF) {
        int char_next = fgetc(file);
        if (char_next == char_current){
            count ++;
        } else {
            // writing the count and character as binary integer
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&char_current, sizeof(char), 1, stdout);
            // printf("%d%c ", count, char_current);
            count = 1;
            char_current = char_next;
        }
    }
    // making sure that each file can be separated
    long int separator = 0;
    fwrite(&separator, sizeof(int)+sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]){
    // checking if there's no files provided as input
    if (argc < 2){
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        return 1;
    }

    // looping through all given files
    for (int i=1; i < argc; i++){
        FILE *file = fopen(argv[i], "r");

        // checking if the file exists
        if (file == NULL){
            perror(argv[i]);
            return 1;
        }

        // calling the function to perform the run-lenght encoding compression for the file
        my_zip(file);
        fclose(file);
    }
    return 0;
}

