#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char group;
} student;

typedef struct p{
    int qs1[1000];
    int qu2;
    int qu0[1000];
    int qu3;
    int qu4;
    int qu5;
}answer;

void normalize_delimiters(char *line, bool *is_empty) {
    *is_empty = (line[0] == '\n');
    if (*is_empty) return;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ',' || line[i] == ';' || line[i] == '|' || line[i] == '\t') {
            line[i] = ' ';
        }
    }
}

bool parse_line(char *line, student *stud) {
    bool is_empty;
    normalize_delimiters(line, &is_empty);
    if (!is_empty) {
        int result = sscanf(line, "%d %49s %49s %c", &stud->id, stud->first_name, stud->last_name, &stud->group);
        return result == 4;
    }
    return false;
}

int read_file(FILE *file, student **students) {
    char line[MAX_LINE_LENGTH];
    int count = 0;
    *students = malloc(sizeof(student) * 10000);  // Allocate memory dynamically

    if (!*students) {
        perror("Error allocating memory for students");
        exit(1);
    }

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (parse_line(line, &(*students)[count])) {
            count++;
        }
    }
    return count;
}



answer compare_files(FILE *ptr1, FILE *ptr2) {
    int Tai1, Tai2;
    student *e, *x;
    answer a = {0, 0, 0, 0};

    Tai1 = read_file(ptr1, &e);
    Tai2 = read_file(ptr2, &x);

    char last_name_e[MAX_NAME_LENGTH],last_name_x[MAX_NAME_LENGTH];
    char first_name_e[MAX_NAME_LENGTH],first_name_x[MAX_NAME_LENGTH];
       
    int i = 0;
    int j = i;
    int k = 0;
    while(i < Tai1 ){
        if(e[i].id == x[j].id){
            
            strcpy(first_name_e, e[i].first_name);
            strcpy(first_name_e, x[j].first_name);
            if (e[i].group != x[j].group)   {
                    a.qu5++ ;   
            }
            if(strcmp(last_name_e, last_name_x) == 0 && strcmp(e[i].first_name, x[j].first_name) == 0 && e[i].group != x[j].group){
                       a.qu4++;
                       
            }
            
            i++;
            j++;
            
        }else{
            while(i < Tai1 && e[i].id != x[j].id){
                i++;
                if(e[i].id == x[j].id){
                    break;
                }
            }
            
        }
        
    }
    i = 0;
    j = i;
    k = 0;
    while(i < Tai1 ){
        if(e[i].id == x[j].id){
            strcpy(first_name_e, e[i].first_name);
            strcpy(first_name_e, x[j].first_name);
            strcpy(last_name_e, e[i].last_name);
            strcpy(last_name_x, x[j].last_name);
            if (strcmp(first_name_e, first_name_e) != 0) {
                    a.qu0[k] = i + 1;    
                    k++;    
            }
            
            i++;
            j++;
            
        }else{
            while(i < Tai1 && e[i].id != x[j].id){
                i++;
                if(e[i].id == x[j].id){
                    break;
                }
            }
            
        }
        
    }

    i = 0;
    j = 0;
     while(i < Tai1 ){
        if(e[i].id == x[j].id){
            i++;
            j++;
        }else{
            while(i < Tai1 && e[i].id != x[j].id){
                i++;
                a.qu3++;
                if(e[i].id == x[j].id){
                    break;
                }
            }
            
        }
        
    }

    i = 0;
 j = 0;



while (i < Tai1 && j < Tai2) {
    if (e[i].id == x[j].id) {
        if (strcmp(e[i].first_name, x[j].first_name) == 0 && strcmp(e[i].last_name, x[j].last_name) == 0 && e[i].group == x[j].group) {
            i++;
            j++;
        } else {
            a.qu2++;
            

            i++;
            j++;
        }
    } else {
        while (i < Tai1 && e[i].id != x[j].id) {
            i++;
        }
    }
}


    return a;
}

int main(){

    FILE*ptr1 = fopen("random_students_info_arabic.txt","r");
    FILE*ptr2 = fopen("random_students_info_arabic_3.txt","r");
    answer a;
    a = compare_files(ptr1,ptr2);
    printf("question 3 :  %d",a.qu3);
    printf("question 4 :  %d",a.qu4);
    printf("question 2 :  %d",a.qu2);
    printf("question 1 :  %d",a.qu5);
    printf("question (first name) 0 :  %d",a.qu0[0]);
    
    

    fclose(ptr1);
    fclose(ptr2);
    return 0;
}
