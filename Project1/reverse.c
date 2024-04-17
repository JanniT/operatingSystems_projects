#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// How many characters can one line contain
// -> Lines end with characters \n\0
#define LINEBUF_SIZE 128

// Helper function that prints given string with \n and \0 showing
void reveal(char *str) {
    //for (size_t i = 0; i < strlen(str); ++i) {
    for (size_t i = 0; i < LINEBUF_SIZE; ++i) {
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

int main(void) {
    // Current line buffer
    char line_buf[LINEBUF_SIZE] = {0};

    int line_offset[100]; 
    size_t line_offset_index = 0;

    // Current line pointer
    char *line;
    char *file_buf = (char*)malloc(LINEBUF_SIZE);

    if (file_buf == NULL) {
            printf("Memory allocation failed");
            return 1;
    }

    int num_lines = 0;

    // Read stdin until Control+d
    while ((line = fgets(line_buf, LINEBUF_SIZE, stdin)) != NULL) {
        size_t line_len = strlen(line) + 1;
        line_offset[line_offset_index++] = num_lines;
        
        memcpy(file_buf + num_lines, line, line_len);
        num_lines += line_len;
    }

    for(int i = line_offset_index - 1; i>=0; i--){
        printf("%s", file_buf+line_offset[i]);
    }
    
    free(file_buf);
    return 0;
}
