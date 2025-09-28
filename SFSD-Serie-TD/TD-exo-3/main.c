#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "..\Display.h" 
#include <stdbool.h>

#define MAX_TEXT_LENGTH 1000

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

int count_occurrences_word(FILE*file, char* word){
    int count = 0;
    int found = 0;
    char line[1024];
    char deter[] = ";,./!$|\n\t ";
    
    while(fgets(line,sizeof(line),file) != NULL ){
       char *token = strtok(line, deter);
       while (token != NULL)
       {
         if(strcmp(strlwr(word),strlwr(token)) == 0){
         count++;
        }
        token = strtok(NULL,deter);
       }
       
       
    }

    return count;
}

int count_occurrences_word_2(FILE *file, const char *word) {
    int count = 0;
    char line[1024];
    int len = strlen(word);
    char lower_word[256];
    strncpy(lower_word, word, sizeof(lower_word) - 1);
    lower_word[sizeof(lower_word) - 1] = '\0';
    for (int i = 0; lower_word[i]; i++) {
        lower_word[i] = tolower(lower_word[i]);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        int i = 0;
        int j = 0;

        while (line[i] != '\0') {
            while (line[i] != '\0' && !isalpha(line[i])) {
                i++;
            }

            if (tolower(line[i]) == lower_word[j]) {
                j++;
                if (j == len) {
                    count++;
                    j = 0; 
                }
            } else {
                j = 0; 
            }
            
            if (line[i] != '\0') {
                i++;
            }
        }
    }

    return count;
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






int main(){

    FILE *ptr_file ;
    TEXT text ;
    ptr_file = fopen("file-1.txt", "a+");
    if (ptr_file == NULL) {
        perror("Couldn't open the file");
        exit(1);
    }
    read_text(text);
    write_in_file(text, ptr_file);
    printf("\n");
    read_from_file(ptr_file);

    printf("\n enter the word you want to research for : ");
    char research[50];
    fgets(research,sizeof(research),stdin);
    research[strcspn(research, "\n")] = '\0';
    fseek(ptr_file,0,SEEK_SET);
    int count = count_occurrences_word_2(ptr_file,research);
    printf("\nThe word %s repeats : %d times in the text file.\n",research,count);
    fclose(ptr_file);

    return 0;
}