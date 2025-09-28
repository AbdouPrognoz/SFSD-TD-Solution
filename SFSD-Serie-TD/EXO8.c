#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bin
{
    int ccp;
    int balanc;
} F1;

typedef struct txt
{
    int ccp_account;
    int amount;
} F2;

int aleatoir_ccp()
{
    return rand() % 50 + 121100;
}

int aleatoir_balanc()
{
    return rand() % 200 + 0;
}

int aleatoir_add_amnt()
{
    return rand() % 200 + 0;
}

void replir_file_bin(FILE *k)
{
    F1 rec;
    int i, z;

    printf("\nEnter the number of accounts:");
    printf("\n-->");
    scanf("%d", &z);
    fseek(k, 0, SEEK_SET);
    for (i = 0; i < z; i++)
    {
        rec.ccp = aleatoir_ccp();
        rec.balanc = aleatoir_balanc() * 100;
        fwrite(&rec, sizeof(rec), 1, k);
    }
}

void replir_file_txt(FILE *t)
{
    F2 rec;
    int i, z;

    printf("\nEnter the number of accounts:");
    printf("\n-->");
    scanf("%d", &z);
    fseek(t, 0, SEEK_SET);
    for (i = 0; i < z; i++)
    {
        rec.ccp_account = aleatoir_ccp();
        rec.amount = aleatoir_add_amnt() * 100;
        fprintf(t, "%d %d\n", rec.ccp_account, rec.amount);
    }
}

void ajout_amont(FILE *k, FILE *t)
{
    F1 rec;
    F2 e;
    fseek(k, 0, SEEK_SET);

    while (fread(&rec, sizeof(rec), 1, k))
    {
        fseek(t, 0, SEEK_SET);
        while (fscanf(t, "%d %d", &e.ccp_account, &e.amount) == 2)
        {
            if (rec.ccp == e.ccp_account)
            {
                rec.balanc += e.amount;
                fseek(k, -sizeof(rec), SEEK_CUR);
                fwrite(&rec, sizeof(rec), 1, k);
                fseek(k, sizeof(rec), SEEK_CUR);
            }
        }
    }
}

void display(FILE *f)
{
    F1 rec;
    int i = 1;
    fseek(f, 0, SEEK_SET);
    printf("\nCCP Accounts & Cash before edit:\n");
    printf("---------------------------------------------------------\n");
    while (fread(&rec, sizeof(rec), 1, f) != 0)
    {
        printf("CCP Account: %d | Cash: %d DZD\n", rec.ccp, rec.balanc);
        i++;
    }
    if (i == 1)
    {
        printf("\nThe file is empty.\n");
    }
}

void display_2(FILE *f)
{
    F2 rec;
    int i = 1;
    fseek(f, 0, SEEK_SET);
    printf("\nCCP Accounts & Cash in TXT file:\n");
    printf("---------------------------------------------------------\n");
    while (fscanf(f, "%d %d", &rec.ccp_account, &rec.amount) == 2)
    {
        printf("CCP Account: %d | Cash: %-10d DZD\n", rec.ccp_account, rec.amount);
        i++;
    }
    if (i == 1)
    {
        printf("\nThe file is empty.\n");
    }
}

int main()
{
    srand(time(NULL));

    FILE *f, *l;
    char nam[30], nam1[30];

    printf("\nEnter the name of the TXT file:");
    scanf("%s", nam);
    f = fopen(nam, "w+");
    if (f == NULL)
    {
        printf("The file doesn't exist.");
        exit(1);
    }

    printf("\nEnter the name of the BIN file:");
    scanf("%s", nam1);
    l = fopen(nam1, "wb+");
    if (l == NULL)
    {
        printf("The file doesn't exist.");
        fclose(f);
        exit(1);
    }

    replir_file_txt(f);
    replir_file_bin(l);
    fclose(f);
    fclose(l);

    f = fopen(nam, "r");
    if (f == NULL)
    {
        printf("The file doesn't exist.");
        exit(1);
    }
    l = fopen(nam1, "rb+");
    if (l == NULL)
    {
        printf("The file doesn't exist.");
        fclose(f);
        exit(1);
    }

    display(l);
    display_2(f);
    ajout_amont(l, f);
    display(l);

    fclose(f);
    fclose(l);
    getchar();
    return 0;
}
