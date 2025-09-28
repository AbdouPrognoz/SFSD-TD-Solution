#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
typedef struct {
    char name[20];
    int year;
} Student;

// Define the Teacher structure
typedef struct {
    char name[20];
    char subject[30];
} Teacher;

int main() {
    FILE *infos;
    infos = fopen("fread_fwrite.txt", "w+");
    if (infos == NULL) {
        printf("Impossible to open the file.\n");
        exit(1);
    }

    // Array of students
    Student students[] = {
        {"Isaac", 20},
        {"Alice", 22},
        {"Bob", 19},
        {"Clara", 21}
    };
    int numStudents = sizeof(students) / sizeof(students[0]);

    // Array of teachers
    Teacher teachers[] = {
        {"Mr. Johnson", "Mathematics"},
        {"Ms. Smith", "Physics"},
        {"Dr. Brown", "Chemistry"}
    };
    int numTeachers = sizeof(teachers) / sizeof(teachers[0]);

    // Writing students to the file
    fwrite(students, sizeof(Student), numStudents, infos);

    // Writing teachers to the file
    fwrite(teachers, sizeof(Teacher), numTeachers, infos);

    // Reset the file pointer to the beginning of the file
    fseek(infos, 0, SEEK_SET);

    // Reading and displaying all students
    Student s;
    printf("Stored students:\n");
    for (int i = 0; i < numStudents; i++) {
        fread(&s, sizeof(Student), 1, infos);
        printf("Name: %s, Year: %d\n", s.name, s.year);
    }

    // Reading and displaying all teachers
    Teacher t;
    printf("\nStored teachers:\n");
    for (int i = 0; i < numTeachers; i++) {
        fread(&t, sizeof(Teacher), 1, infos);
        printf("Name: %s, Subject: %s\n", t.name, t.subject);
    }

    fclose(infos);
    printf("\nStudents and teachers saved and read successfully from the file.\n");
    return 0;
}
