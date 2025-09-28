#include <stdio.h>

int main() {
    FILE *file = fopen("fseek.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Move the file pointer to the 5th byte from the start
    fseek(file, 5, SEEK_SET);

    // Read and display the next character
    char ch = fgetc(file);
    printf("Character at position 5: %c\n", ch);

    // Move the file pointer 2 bytes forward from the current position
    fseek(file, 2, SEEK_CUR);

    // Read and display the next character
    ch = fgetc(file);
    printf("Character at position 8: %c\n", ch);

    // Move the file pointer to 3 bytes before the end of the file
    fseek(file, -3, SEEK_END);

    // Read and display the character at this position
    ch = fgetc(file);
    printf("Character 3 bytes from the end: %c\n", ch);

    fclose(file);
    return 0;
}
