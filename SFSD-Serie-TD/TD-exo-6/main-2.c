#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_DAYS 365

typedef struct {
    int id;
    char city_name[50];
    char date[MAX_DAYS][20];
    int temperature[MAX_DAYS];
    char delete;
    int NB;
} eng;


typedef struct Date
{
    int day;
    int month;
    int year;
} Date;


void dateToString(Date date, char *dateString) {
    sprintf(dateString, "%04d-%02d-%02d", date.year, date.month, date.day);
}    


void scanDate(Date *date)
{
scan:
    fflush(stdin);
    system("color 07");
    int inputs = scanf("%d-%d-%d", &date->year, &date->month,  &date->day);

    if(inputs != 3)
    {
error:
        system("color 47");
        printf("\033[A\33[2K\r\tDate (yyyy-mm-dd): ");
        goto scan;
    }
    if(date->year < 2015){
        goto error;
    }
    if((date->day < 1) || (date->month < 1) || (date->month > 12))
        goto error;

    if((date->year % 4 == 0) && (date->year % 100 != 0)) 
    {
        if((date->month == 2) && (date->day > 29))
            goto error;
    }
    else 
    {
        if((date->month == 2) && (date->day > 28))
            goto error;
    }

    if((date->month == 4) || (date->month == 6) || (date->month == 9) || (date->month == 11)) 
    {
        if(date->day > 30)
            goto error;
    }
    else if(date->day != 2) 
    {
        if(date->day > 31)
            goto error;
    }

    fflush(stdin);
}




bool find_city(FILE *file, int id, long *position) {
    eng city;
    fseek(file, 0, SEEK_SET);
    while (fread(&city, sizeof(city), 1, file) > 0) {
        if (city.id == id && city.delete != 'Y' && city.delete != 'y') {
            *position = ftell(file) - sizeof(city);
            return true;
        }
    }
    return false;
}

bool date_exist(FILE *file, const char *date, int id) {
    eng city;
    fseek(file, 0, SEEK_SET);
    long position;
    bool found = find_city(file, id, &position);
    
    if (found) {
        fseek(file, position, SEEK_SET);
        fread(&city, sizeof(city), 1, file);
        for (int i = 0; i < city.NB; i++) {
            if (strcmp(city.date[i], date) == 0) {
                printf("This date already exists. Please enter a different date.\n");
                return true;
            }
        }
    }
    return false;
}

void add_to_file(FILE *file) {
    eng city;
    Date date;
    while (true) {
        fseek(file, 0, SEEK_SET);
        printf("Enter the id of the city: ");
        scanf("%d", &city.id);

        long position;
        bool found = find_city(file, city.id, &position);
        char day[20];
        if (found) {
            fseek(file, position, SEEK_SET);
            fread(&city, sizeof(city), 1, file);

            printf("Enter the date (year-month-day): ");
            bool existDate;
            do {
                scanDate(&date);
                dateToString(date, day);
                existDate = date_exist(file, day, city.id);
                if(existDate){
                    printf("Enter the date (year-month-day): ");
                }
                
            } while (existDate);
            strcpy(city.date[city.NB], day);

            printf("Enter the temperature: ");
            scanf("%d", &city.temperature[city.NB]);
            city.NB++;

            fseek(file, position, SEEK_SET);
            fwrite(&city, sizeof(city), 1, file);
        } else {
            printf("Enter city name: ");
            getchar();
            fgets(city.city_name, sizeof(city.city_name), stdin);
            city.city_name[strcspn(city.city_name, "\n")] = '\0';

            city.NB = 0;

            printf("Enter the date (year-month-day): ");
            bool existDate;
            do {
                scanDate(&date);
                dateToString(date, day);
                existDate = date_exist(file, day, city.id);
                
            } while (existDate);
            strcpy(city.date[city.NB], day);

            printf("Enter the temperature: ");
            scanf("%d", &city.temperature[city.NB]);
            city.NB++;

            city.delete = 'N';
            fwrite(&city, sizeof(city), 1, file);
        }

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
    int city_id;
    char date[20];
    int found = 0;

    printf("Please enter the city information:\n\n");
    printf("Enter the city ID: ");
    scanf("%d", &city_id);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter the date: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    long position;
    if (find_city(file, city_id, &position)) {
        fseek(file, position, SEEK_SET);
        fread(&city, sizeof(city), 1, file);

        for (int i = 0; i < city.NB; i++) {
            if (strcmp(city.date[i], date) == 0 && city.delete != 'Y' && city.delete != 'y') {
                printf("Enter the new temperature of the city: ");
                scanf("%d", &city.temperature[i]);

                while ((ch = getchar()) != '\n' && ch != EOF);

                fseek(file, position, SEEK_SET);
                if (fwrite(&city, sizeof(city), 1, file) > 0) {
                    printf("\nThe modification was successful.\n");
                } else {
                    printf("\nError writing to the file.\n");
                }

                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("The city or date does not exist in the file!\n");
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
    printf("Enter the city id: ");
    scanf("%d", &city.id);  
    long position;
    bool found = find_city(file,city.id,&position);
    int i = 0;
    if(found){
        fseek(file, position, SEEK_SET);
        fread(&city, sizeof(city), 1, file);
        strcpy(city_name, city.city_name); 
        for(i = 0;i < city.NB;i++ ){
            if (city.temperature[i] < min) {
                min = city.temperature[i];
                strcpy(min_date, city.date[i]); 
            }

            if (city.temperature[i] > max) {
                max = city.temperature[i];
                strcpy(max_date, city.date[i]);  
            }
            total += city.temperature[i];
            count++;
        }
         
    }else{
       printf("The city does not exist in the file !!\n");
       return;
    }

    moy = total / count;
    printf("The maximum temperature of %s is %.2f %cC on %s\n", city_name, max,248, max_date);
    printf("The minimum temperature of %s is %.2f %cC on %s\n", city_name, min,248, min_date);
    printf("The average temperature of %s is: %.2f %cC.\n", city_name, moy,248);
}

void delete_city(FILE *file) {
    if (file == NULL) {
        printf("Error: Unable to open file for deletion.\n");
        return;
    }
    eng city;
    int city_id;
    printf("Enter the city ID: ");
    scanf("%d", &city_id);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    long position;
    bool found = find_city(file, city_id, &position);

    if (found) {
        fseek(file, position, SEEK_SET);
        fread(&city, sizeof(city), 1, file);
        city.delete = 'Y';

        fseek(file, position, SEEK_SET);
        if (fwrite(&city, sizeof(city), 1, file) == 1) {
            printf("\nThe city %s has been deleted.\n", city.city_name);
        } else {
            printf("Error: Unable to write to file.\n");
        }
    } else {
        printf("The city with ID %d was not found.\n", city_id);
    }

    

    fflush(file);
}



void write_table(FILE *file) {
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    eng city;

    // Print the table header
    printf("+------------+----------------------+----------------------+----------------------+\n");
    printf("| %-10s | %-20s | %-20s | %-20s |\n", "ID", "City Name", "Date", "Temperature");
    printf("+------------+----------------------+----------------------+----------------------+\n");

    // Print each city's data in a row
    fseek(file, 0, SEEK_SET); // Ensure we start reading from the beginning of the file
    while (fread(&city, sizeof(city), 1, file) == 1) {
        if (city.delete != 'Y' && city.delete != 'y') {
            printf("| %-10d | %-20s | %-20s | %-20d |\n", city.id, city.city_name, city.date[0], city.temperature[0]);
            for (int j = 1; j < city.NB; j++) {
                printf("| %-10s | %-20s | %-20s | %-20d |\n", "", "", city.date[j], city.temperature[j]);
            }
            printf("+------------+----------------------+----------------------+----------------------+\n");
        }
    }
}

void display_deleted_cities(FILE*file){
    if(file == NULL){
        perror("error in opening the file !!");
        exit(1);
    }
    fseek(file, 0, SEEK_SET); 
    eng city;
    int count=0;
    printf("the deleted cities are : \n");
    while (fread(&city, sizeof(city), 1, file) == 1) {
        if (city.delete == 'Y' && city.delete == 'y') {
            printf("%s",city.city_name);
            count++;
        }
    }
    if(count == 0){
        printf("There are no deleted city");
    }
}

int main(){
    
    FILE*file = fopen("weather_2.bin","rb+");
    if(file == NULL){
        perror("There is an error in opening the file ");
        exit(1);
    }
    printf("\nadd to file : \n");
    add_to_file(file);
    write_table(file);
    printf("\nmodify : \n");
    modify_city_info(file);
    write_table(file);
    printf("Status\n");
    status_city(file);
    printf("delete \n");
    delete_city(file);
    write_table(file);
    return 0;
}