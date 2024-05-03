#include <stdio.h>
#include <stdlib.h>

void my_zip(FILE *file){
    int char_current = fgetc(file);
    int count = 1;

    if (char_current == EOF) {
        return;
    }

    while (char_current != EOF) {
        int char_next = fgetc(file);
        if (char_next == char_current){
            count ++;
        } else {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&char_current, sizeof(char), 1, stdout);
            // printf("%d%c ", count, char_current);
            count = 1;
            char_current = char_next;
        }
    }
}

int main(int argc, char *argv[]){
    // checking if there's no files provided as input
    if (argc < 2){
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i=1; i < argc; i++){
        FILE *file = fopen(argv[i], "r");
        if (file == NULL){
            perror(argv[i]);
            return 1;
        }
        my_zip(file);
        fclose(file);
    }
    return 0;
}