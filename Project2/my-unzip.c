#include <stdio.h>
#include <stdlib.h>

void my_unzip(FILE *file){
    int count;
    char character;

    // reading the 4-byte integers and characters until the end of the file
    while(fread(&count, sizeof(int), 1, file) != 0) {
        fread(&character, sizeof(char), 1, file);
        // checking the if there's the separator which separates files inside the zip
        if (count == 0){
            printf("\n");
            continue;
        }

        // printing the character count times
        for (int i = 0; i < count; i++){
            printf("%c", character);
        }

    }
}


int main(int argc, char *argv[]){
    // checking if there's no files provided as input
    if (argc < 2){
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    // looping through the given files
    for (int i=1; i < argc; i++){
        FILE *file = fopen(argv[i], "r");

        // checking if the file exists
        if (file == NULL){
            perror(argv[i]);
            return 1;
        }

        // calling the function to perform the decompression for the file
        my_unzip(file);
        fclose(file);
    }
    return 0;
}

