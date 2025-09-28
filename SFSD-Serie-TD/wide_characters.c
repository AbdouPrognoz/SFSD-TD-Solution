#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    // Set the locale to support wide characters
    setlocale(LC_ALL, "");

    // Open the file in read mode for wide characters
    FILE *file = fopen("read-text.txt", "r");
    if (file == NULL) {
        wprintf(L"Unable to open the file\n");
        return 1;
    }

    // Variable to store each wide character
    wchar_t ch;

    // Read each character from the file until the end of the file is reached
    while ((ch = fgetwc(file)) != WEOF) {  // WEOF represents the end of the file for wide characters
        wprintf(L"%lc", ch);  // Print the wide character
        // putwchar(wc); to write in the file
    }

    // Close the file
    fclose(file);

    return 0;
}
