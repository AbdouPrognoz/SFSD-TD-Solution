#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Display.h"  
#define MAX_LINE_LENGTH 1024
#define MAX_NAME_LENGTH 50


typedef struct  {
    int id;
    char first_name[MAX_NAME_LENGTH];
    char second_name[MAX_NAME_LENGTH];
    char group;
}Person;

void normalize_delimiters(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ',' || line[i] == ';' || line[i] == '|' || line[i] == '\t') {
            line[i] = ' ';
        }
    }
}


Person parse_line(char *line) {
    Person person;
    normalize_delimiters(line);
    sscanf(line, "%d %s %s %c", &person.id, person.first_name, person.second_name, &person.group);
    
    return person;
}

int main() {
    FILE *file = fopen("random_students_info_arabic.txt", "r+"); 
    if (!file) {
        Red();
        perror("Error opening file");
        Reset();
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Person person;

   
    while (fgets(line, sizeof(line), file) != NULL) {
        person = parse_line(line);
        Green();
        printf("ID: %d, First Name: %s, Second Name: %s, Group: %c\n",
               person.id, person.first_name, person.second_name, person.group);
        Reset();       
    }

    fclose(file);
    return 0;
}
