#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Display.h"  


void normalize_delimiters(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ',' || line[i] == ';' || line[i] == '|' || line[i] == '\t') {
            line[i] = '|';
        }
    }
}


void read_from_file(FILE *file) {
   
    fseek(file, 0, SEEK_SET);
    char ch;

    
    while ((ch = fgetc(file)) != EOF) {
        Green ();
        putchar(ch);
        Reset();
    }
    
    /*
    
    while (!feof(file)) {
    ch = fgetc(file);
    putchar(ch); 
   }
    
    */
    
    if (ferror(file)) {
        perror("Error reading from file");
    }
}
void read_from_file_2(FILE *file) {
    
    fseek(file, 0, SEEK_SET);
    char line[50];

    // Reading the file character by character
    while (fgets(line,sizeof(line),file) != NULL) {
        normalize_delimiters(line);
        Green ();
        printf("%s", line);
        Reset();
    }

   
    if (ferror(file)) {
        perror("Error reading from file");
    }
}
int main() {
    
    FILE *ptr_file = fopen("exo-1.txt", "r+");
    FILE *ptr_file_2 = fopen("random_students_info_arabic.txt","r+");
    if (ptr_file == NULL) {
        perror("Couldn't open the file");
        exit(1);
    }
    if (ptr_file_2 == NULL) {
        perror("Couldn't open the file");
        exit(1);
    }

    
    printf("The content of the file 1 is:\n\n");
    read_from_file(ptr_file);
    printf("\n\nThe content of student file  is:\n\n");
    read_from_file_2(ptr_file_2);
    fclose(ptr_file_2);
    fclose(ptr_file);

    return 0;
}
