#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Display.h"  
#include <stdbool.h>

typedef struct 
{
   char city_name[50];
   char date[20];
   int temperature;
   char delete;
}eng;

void add_to_file(FILE *file){

    eng city;
     while (true) {
        fseek(file, 0, SEEK_END);
        printf("Enter city name: ");
        fgets(city.city_name, sizeof(city.city_name), stdin);
        city.city_name[strcspn(city.city_name, "\n")] = '\0';  

        printf("Enter the date (year/month/day): ");
        fgets(city.date, sizeof(city.date), stdin);
        city.date[strcspn(city.date, "\n")] = '\0'; 

        printf("Enter the temperature: ");
        scanf("%d", &city.temperature);

        city.delete = 'N';
        fwrite(&city, sizeof(city), 1, file);

        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Do you want to add another city or temperature? (Y/N): ");
        char ch;
        scanf(" %c", &ch);  
        if (ch == 'N' || ch == 'n') {
            break;
        }

        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void modify_city_info(FILE *file) {
    if (file == NULL) {
        printf("Error: Unable to open file for modification.\n");
        return;
    }

    eng city;
    char city_name[50];
    char date[20];
    int found = 0;  // Flag to check if city was found

    printf("Please enter the city information:\n\n");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Enter the city name: ");
    fgets(city_name, sizeof(city_name), stdin);
    city_name[strcspn(city_name, "\n")] = '\0';  

    printf("Enter the date: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';  

    fseek(file, 0, SEEK_SET);

    while (fread(&city, sizeof(city), 1, file) != 0) {
        if (strcmp(strlwr(city.city_name), strlwr(city_name)) == 0 &&
            strcmp(city.date, date) == 0 &&
            city.delete != 'Y' && city.delete != 'y') {

            printf("Enter the new temperature of the city: ");
            scanf("%d", &city.temperature);

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fseek(file, -sizeof(city), SEEK_CUR);

            if (fwrite(&city, sizeof(city), 1, file) > 0) {
                printf("\nThe modification was successful.\n");
            } else {
                printf("\nError writing to the file.\n");
            }

            found = 1; 
            break;  
        }
    }

    if (!found) {
        printf("The city does not exist in the file!\n");
    }
}

void status_city(FILE *file) {
    eng city;
    float min = 70.0;  
    float max = -50.0;
    float moy = 0.0;
    int count = 0;
    float total = 0.0;
    char city_name[50];
    char max_date[20];
    char min_date[20];

    fseek(file, 0, SEEK_SET);
    printf("Enter the city name: ");
    fgets(city_name, sizeof(city_name), stdin);
    city_name[strcspn(city_name, "\n")] = '\0';  

    while (fread(&city, sizeof(city), 1, file) != 0) {
        
        if (strcmp(strlwr(city.city_name), strlwr(city_name)) == 0 && city.delete != 'Y' && city.delete != 'y') {
            
            if (city.temperature < min) {
                min = city.temperature;
                strcpy(min_date, city.date); 
            }

            if (city.temperature > max) {
                max = city.temperature;
                strcpy(max_date, city.date);  
            }
            total += city.temperature;
            count++;
        }
    }
    if (count == 0) {
        printf("The city does not exist in the file !!\n");
        return;
    }

    moy = total / count;
    printf("The maximum temperature of %s is %.2f°C on %s\n", city_name, max, max_date);
    printf("The minimum temperature of %s is %.2f°C on %s\n", city_name, min, min_date);
    printf("The average temperature of %s is: %.2f°C.\n", city_name, moy);
}

 
void delete_city(FILE *file) {
    if (file == NULL) {
        printf("Error: Unable to open file for deletion.\n");
        return;
    }

    eng city;
    char city_name[50];
    int counter = 0;

    printf("Enter the city name: ");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(city_name, sizeof(city_name), stdin);
    city_name[strcspn(city_name, "\n")] = '\0';

    fseek(file, 0, SEEK_SET);

    while (fread(&city, sizeof(city), 1, file) > 0) {
        if (strcasecmp(city.city_name, city_name) == 0 && (city.delete != 'Y' && city.delete != 'y')) {
            city.delete = 'Y';
            fseek(file, -sizeof(city), SEEK_CUR); // Go back to update the record
            if (fwrite(&city, sizeof(city), 1, file) == 1) {
                printf("\nThe city %s has been deleted.\n", city.city_name);
                counter++; 
            } else {
                printf("Error: Unable to write to file.\n");
            }
        }
    }

    if (counter == 0) {
        printf("\nThe city %s does not exist in the file !!\n", city_name);
    }

    fflush(file); // Ensure data is written to disk
}


void display(FILE *file) {
    eng city;

    if (file == NULL) {
        printf("Error: Unable to open file for display.\n");
        return;
    }

    fseek(file, 0, SEEK_SET);
    printf("Displaying the File Information:\n");

    size_t readCount;
    while ((readCount = fread(&city, sizeof(city), 1, file)) > 0) { 
        if (city.delete != 'Y' && city.delete != 'y') {
            printf("City: %s, Date: %s, Temperature: %d\n", city.city_name, city.date, city.temperature);
        }
    }

    if (ferror(file)) {
        printf("Error reading the file.\n");
    } else if (feof(file)) {
        printf("Reached the end of the file.\n");
    } else {
        printf("No valid records found.\n");
    }
}




int main(){

    FILE*file = fopen("weather.bin","rb+");
    if(file == NULL){
        perror("There is an error in opening the file ");
        exit(1);
    }
/*

add_to_file(file);
    display(file);
    delete_city(file);
    display(file);
    modify_city_info(file);
    display(file);
    status_city(file);
*/
    add_to_file(file);
    display(file);
    delete_city(file);
    display(file);
    modify_city_info(file);
    display(file);
    status_city(file);

    fclose(file);
    return 0;
}