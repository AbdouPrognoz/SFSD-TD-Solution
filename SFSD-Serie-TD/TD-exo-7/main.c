#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "..\Display.h"  
#define MAX_TEXT_LENGTH 1000

void compare_files(const char *file1, const char *file2) {
    FILE *ptr_1 = fopen(file1, "r");
    FILE *ptr_2 = fopen(file2, "r");

    if (ptr_1 == NULL || ptr_2 == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char text_1[MAX_TEXT_LENGTH] = "";
    char text_2[MAX_TEXT_LENGTH] = "";
    int ch1, ch2;
    int line_number = 1;
    int char_position = 0;
    bool files_identical = true;

    while (true) {
        ch1 = fgetc(ptr_1);
        ch2 = fgetc(ptr_2);

        while (ch1 == ' ' || ch1 == '.' || ch1 == ',' || ch1 == '\n') {
            if (ch1 == '\n') line_number++; 
            ch1 = fgetc(ptr_1);
        }

        while (ch2 == ' ' || ch2 == '.' || ch2 == ',' || ch2 == '\n') {
            ch2 = fgetc(ptr_2);  
        }

        if (ch1 == EOF || ch2 == EOF) {
            break;
        }

        if (ch1 != ch2) {
            files_identical = false;
            int i = 0, j = 0;

            while (ch1 != ch2 && ch1 != EOF && ch2 != EOF) {
                if (i < MAX_TEXT_LENGTH - 1) {
                    text_1[i++] = (char)ch1;
                    text_1[i] = '\0'; 
                }
                if (j < MAX_TEXT_LENGTH - 1) {
                    text_2[j++] = (char)ch2;
                    text_2[j] = '\0'; 
                }

                ch1 = fgetc(ptr_1);
                ch2 = fgetc(ptr_2);
                 
                /*

                while ( ch1 == '.' || ch1 == ',' || ch1 == '\n') {
                    if (ch1 == '\n') line_number++;
                    ch1 = fgetc(ptr_1);
                }

                while ( ch2 == '.' || ch2 == ',' || ch2 == '\n') {
                    ch2 = fgetc(ptr_2);
                }
                
                */
                
            }

            printf("Difference found at line %d, character position %d:\n", line_number, char_position + 1);
            printf("File 1: \"%s\"\n", text_1);
            printf("File 2: \"%s\"\n", text_2);

            text_1[0] = '\0';
            text_2[0] = '\0';
        }

        char_position++;
    }

    if (ch1 != ch2) {
        files_identical = false;
        Red();
        if (ch1 != EOF) {
            printf("File 1 has extra content starting at line %d, character position %d.\n", line_number, char_position + 1);
        } else {
            printf("File 2 has extra content starting at line %d, character position %d.\n", line_number, char_position + 1);
        }
        Reset();
    }

    if (files_identical) {
        Green();
        printf("The files are identical (ignoring spaces, punctuation, and line breaks).\n");
        Reset();
    }

    fclose(ptr_1);
    fclose(ptr_2);
}

int main() {
    const char *file1 = "random_students_info_arabic.txt";
    const char *file2 = "random_students_info.txt";
    compare_files(file1, file2);
    return 0;
}
