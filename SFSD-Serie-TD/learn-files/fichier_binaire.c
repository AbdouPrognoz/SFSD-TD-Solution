#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[20];
    int year;
}Student;


int main(){
    FILE *infos;
    infos = fopen("info.bin", "wb+"); 
    if (infos == NULL) {
        printf("Impossible to open the file");
        exit(1);
    }

    Student e = {"Isaac",20};
    fwrite(&e,sizeof(Student),1,infos); 
    fseek(infos, 0, SEEK_SET);
    while (fread(&e,sizeof(Student),1,infos) ==1)
    {
        printf("%s %d",e.name,e.year);
        /* code */
    }
    

    fclose(infos);
    printf("\nText saved successfully in the file");
    return 0; 
}