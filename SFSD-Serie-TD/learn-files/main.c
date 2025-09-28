// C Program to illustrate file opening
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *infos;
    infos = fopen("informations.txt", "w"); 
    if (infos == NULL) {
        printf("Impossible to open the file");
        exit(1);
    }

    char name[25];
    int year;

    // Get year input
    printf("Enter the year: ");
    scanf("%d", &year);

    // Clear input buffer to avoid fgets issues
    getchar(); // This removes the leftover newline from the input buffer

    // Get name input
    printf("Enter the name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove the newline character from the string

    // Write to file
    fputc('A', infos);
    fputs("\nisaac", infos);
    fputs("\nESI Alger", infos);
    fprintf(infos, "\nLanguage C created by %s in %d", name, year);

    // Close the file
    fclose(infos);
    printf("The file is saved successfully.\n");

    return 0;
}























