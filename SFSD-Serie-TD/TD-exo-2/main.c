#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Display.h" 

void read_from_file(FILE *file) {
    fseek(file, 0, SEEK_SET);
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        Green ();
        putchar(ch);
        Reset();
    }
    if (ferror(file)) {
        perror("Error reading from file");
    }
}

void copy_content(char*first_file,char*seconde_file) {

    FILE *ptr_file_1,*ptr_file_2 ;
    ptr_file_1 = fopen(first_file, "a+");
    ptr_file_2 = fopen(seconde_file, "r");
    if (ptr_file_1 == NULL && ptr_file_2 != NULL) {
        Red();
        perror("Couldn't open the first  file");
        Reset();
        printf("The content of the seconde file  is : \n");
        read_from_file(ptr_file_2);
        return;
        
    }else if (ptr_file_2 == NULL && ptr_file_1 != NULL){
        Red();
        perror("Couldn't open the seconde  file");
        Reset();
        printf("The content of the first file  is : \n");
        read_from_file(ptr_file_1);
        return;
    }else
        if (ptr_file_1 != NULL && ptr_file_2 != NULL){
        printf("The content of the file one is : \n");
        read_from_file(ptr_file_1);
        printf("The content of the seconde file is : \n");
        read_from_file(ptr_file_2);
        fseek(ptr_file_2,0,SEEK_SET);
        char ch;
        while ((ch = fgetc(ptr_file_2)) != EOF) {
        if (fputc(ch, ptr_file_1) == EOF) {
            Red();
            perror("Error writing to destination file");
            Reset();
            break;
        }
    }
        printf("\nThe content of the first file after modification : \n");
        read_from_file(ptr_file_1);
    }else{
        Red();
        printf("\nBoth files have errors !!!!\n");
        Reset();
        return;

    }
}
    



int main(){
    
    
    copy_content("file-1.txt","file-2.txt");


    return 0;
}