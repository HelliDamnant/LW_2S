#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = NULL;
    if ((f = fopen("data.bin", "wb")) == NULL)
    {
        printf("Error!");
        exit(1);
    }

    int a;
    printf("Begin input:\n");
    while (scanf("%d", &a))
        if (a)
        {
            fwrite(&a, sizeof(int), 1, f);
            fflush(stdin);
        }
        else
        {
            fclose(f);
            printf("End");
            return 0;
        }
    
    printf("Error!");
    exit(1);
}