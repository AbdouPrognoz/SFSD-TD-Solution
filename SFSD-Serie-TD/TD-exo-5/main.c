#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Display.h"  
#include <stdbool.h>


#define MAX_TEXT_LENGTH 1024

typedef char TEXT[MAX_TEXT_LENGTH];
void read_text(TEXT text){
     
    int i = 0;
    char ch;

    printf("Enter a multiline text (press Enter twice to finish):\n");

    do {
        ch = getchar();

        if (ch == '\n') {
            // Check if the previous character was also a newline
            if (i > 0 && text[i - 1] == '\n') {
                break; // Exit the loop if two consecutive newlines are detected
            }
        }

        text[i++] = ch;

        // Check if the buffer is full
        if (i == MAX_TEXT_LENGTH - 1) {
            printf("Text limit reached. Press Enter to finish.\n");
            break;
        }

    } while (ch != EOF);

    // Null-terminate the string
    text[i] = '\0';
    printf("\n");
}

void write_in_file(TEXT text, FILE *file) {
    // Writing text to file
    if (fprintf(file, "%s\n", text) < 0) {
        // Check if there is an error
        if (ferror(file)) {
            perror("Error writing to file");
        }
    } 
}

void read_from_file(FILE *file) {
    // Reset file pointer to the beginning
    fseek(file, 0, SEEK_SET);
    char ch;

    // Reading the file character by character
    while ((ch = fgetc(file)) != EOF) {
        Green ();
        putchar(ch);
        Reset();
    }

    // Check if there was an error during reading
    if (ferror(file)) {
        perror("Error reading from file");
    }
}


void crypto_file(char *key, FILE *file, FILE *file_2) {
    if (!file || !file_2) {
        Red();
        perror("Error opening file");
        Reset();
        exit(1);
    }

    fseek(file, 0, SEEK_SET);
    int key_len = strlen(key);
    char line[MAX_TEXT_LENGTH];
    char ch;
    int j = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int line_len = strlen(line);
        for (int i = 0; i < line_len; i++) {
            if (line[i] != '\n' && line[i] != '\0') {
                ch = (line[i] + key[j % key_len]) % 256; 
                fputc(ch, file_2); 
                j++;
            }
        }
    }
}


void decrypt_text_file(char *key, FILE *file, FILE *file_2) {
    fseek(file, 0, SEEK_SET);
    int key_len = strlen(key);
    char line[MAX_TEXT_LENGTH];
    char buffer;
    int i = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int line_len = strlen(line);
        for (int j = 0; j < line_len; j++) {
            if (line[j] != '\n' && line[j] != '\0') {
                buffer = (line[j] - key[i % key_len]) % 256; 
                fputc(buffer, file_2); 
                i++;
            }
        }
    }
}

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w+");
    FILE *decrypt_file = fopen("decrypt.txt", "w+");

    if (!input_file) {
        Red();
        perror("Error reading from input file");
        Reset();
        exit(1);
    }

    char key[3] = "esi";


    printf("The content of the origin file :\n");
    read_from_file(input_file);

  
    crypto_file(key, input_file, output_file);

    
    printf("\nThe content of the file after crypt:\n");
    read_from_file(output_file);
    decrypt_text_file(key, output_file, decrypt_file);
    printf("\nThe content of the file after decrypt:\n");
    read_from_file(decrypt_file);

    fclose(input_file);
    fclose(output_file);
    fclose(decrypt_file);

    return 0;
}