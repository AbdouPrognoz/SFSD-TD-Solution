#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    
    FILE *infos;
    infos = fopen("read-text.txt", "r"); 
    if (infos == NULL) {
        printf("Impossible to open the file");
        exit(1);
    }
    
    int carActuel = fgetc(infos);
    /*
    while (carActuel != EOF)
    {

        printf("%c",carActuel);
        carActuel = fgetc(infos);
        
    }
    */

    char str[1000];
    while(fgets(str,1000,infos) != NULL){
        printf("%s",str);
    }
    

    // Reset the file pointer to the beginning of the file
    fseek(infos, 0, SEEK_SET);

   
    printf("\n\n");
    /*
    while (!feof(infos))
    {
        fscanf(infos,"%s ",&str2);
        printf("%s",str2);
        
    */
    char str2[1000];
    while (fscanf(infos, "%999s", str2) == 1) {  // Use %999s to avoid buffer overflow
        printf("%s ", str2);
    }
    fclose(infos);
    
    return 0;
}
