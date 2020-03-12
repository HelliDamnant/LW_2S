#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(int a, FILE *f)
{
    int p;
    
    do
    {
        fseek(f, -1 * sizeof(int), 1);
        fread(&p, sizeof(int), 1, f);
        fwrite(&p, sizeof(int), 1, f);
        fseek(f, -2 * sizeof(int), 1);
    }
    while (ftell(f) != 0 && a < p);
    
    fwrite(&a, sizeof(int), 1, f);
    fseek(f, 0, 2);
}

int main()
{
    FILE *f = NULL;
    if ((f = fopen("./data.bin", "w + b")) == NULL)
    {
        printf("Error!");
        exit(1);
    }

    int a, n;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the numbers:\n");
    if (scanf("%d", &a))
    {
        fwrite(&a, sizeof(int), 1, f);        
        while (--n)
        {
            fflush(stdin);
            if (scanf("%d", &a))
                insert(a, f);
            else
            {
                printf("Error");
                exit(1);
            }
        }
    }
    else
    {
        printf("Error");
        exit(1);
    }

    fseek(f, 0, 0);
    while (fread(&a, sizeof(int), 1, f) > 0) printf("%d ", a);
    printf("\n");
        
    fclose(f);
    return 0;
}