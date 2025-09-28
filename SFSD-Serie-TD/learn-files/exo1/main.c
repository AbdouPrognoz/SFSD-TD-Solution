#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *ptr1, *ptr2;
    char name1[30], name2[30];

    // Get the name of the first file
    printf("Enter the name of the first file: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = '\0';  // Remove the newline character from the string

    // Open the first file in read and append mode
    ptr1 = fopen(name1, "a+");  // Open in read and append mode
    if (ptr1 == NULL) {
        printf("There was an error opening the file %s\n", name1);
        return 1; // Exit if the file cannot be opened
    }

    // Display the content of the first file
    printf("The content of the first file is:\n");
    int carActuel = fgetc(ptr1);
    while (carActuel != EOF) {
        putchar(carActuel);
        carActuel = fgetc(ptr1);
    }
    rewind(ptr1);  // Reset the file pointer to the beginning after reading

    // Get the name of the second file
    printf("\nEnter the name of the second file: ");
    fgets(name2, sizeof(name2), stdin);
    name2[strcspn(name2, "\n")] = '\0';  // Remove newline character

    // Open the second file in read mode
    ptr2 = fopen(name2, "r");
    if (ptr2 == NULL) {
        printf("There was an error opening the file %s\n", name2);
        fclose(ptr1);
        return 1;
    }

    // Display the content of the second file
    printf("\nThe content of the second file is:\n");
    carActuel = fgetc(ptr2);
    while (carActuel != EOF) {
        putchar(carActuel);
        carActuel = fgetc(ptr2);
    }
    rewind(ptr2);  // Reset the file pointer to the beginning after reading

    // Append content from the second file to the first
    fseek(ptr1, 0, SEEK_END);  // Move to the end of the first file
    fputc('\n',ptr1);
    while ((carActuel = fgetc(ptr2)) != EOF) {
        fputc(carActuel, ptr1);
    }

    // Reset ptr1 to the beginning to read its full content after appending
    rewind(ptr1);
    printf("\n\n");
    // Display the content of the first file after appending
    printf("\nThe content of the first file after appending is:\n");
    carActuel = fgetc(ptr1);
    while (carActuel != EOF) {
        putchar(carActuel);
        carActuel = fgetc(ptr1);
    }

    // Close the file pointers
    fclose(ptr1);
    fclose(ptr2);

    return 0;
}
