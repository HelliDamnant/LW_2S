#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = NULL;
    if ((f = fopen("./data.bin", "w + b")) == NULL)
    {
        printf("Error!");
        exit(1);
    }

    int a, b, n;
    printf("Enter the number of items: ");
    
    if (scanf("%d", &n) == 0)
    {
        printf("Error");
        exit(1);
    }
    
    printf("Enter the numbers:\n");
    
    while (n-- && scanf("%d", &a))
    {
        fflush(stdin);
        while (ftell(f))
        {
            fseek(f, -1 * sizeof(int), 1);
            fread(&b, sizeof(int), 1, f);
            
            if (a > b) break;
            
            fwrite(&b, sizeof(int), 1, f);
            fseek(f, -2 * sizeof(int), 1);
        }
        fwrite(&a, sizeof(int), 1, f);
        fseek(f, 0, 2);
    }

    if (n)
    {    
        fseek(f, 0, 0);
        while (fread(&a, sizeof(int), 1, f) > 0) printf("%d ", a);
        printf("\n");
        
        fclose(f);
        return 0;
    }
    else
    {
        printf("Error");
        exit(1);
    }
}