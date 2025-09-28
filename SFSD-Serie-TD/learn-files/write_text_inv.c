#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *p_fichier;
    char c;
    int i, pos;

    p_fichier = fopen("read-text.txt", "r");
    if (p_fichier == NULL) {
        printf("There was an error opening the file\n");
        exit(1);
    }

    // Move the file pointer to the end and get the position (size)
    fseek(p_fichier, 0, SEEK_END);
    pos = ftell(p_fichier);

    if (pos == -1) {
        printf("Error determining the file size\n");
        fclose(p_fichier);
        return 1;
    }

    // Read the file in reverse
    for (i = 1; i <= pos; i++) {
        fseek(p_fichier, -i, SEEK_END);
        c = fgetc(p_fichier);
        if (c != EOF) {
            printf("%c", c);
        }
    }

    fclose(p_fichier);
    return 0;
}
