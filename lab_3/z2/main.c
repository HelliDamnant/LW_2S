#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = NULL;
    if ((f = fopen("data.bin", "rb")) == NULL)
    {
        printf("Error!");
        exit(1);
    }

    int a, b;
    if ((b = fread(&a, sizeof(int), 1, f)) > 0)
    {
        while (fread(&b, sizeof(int), 1, f) > 0 && b > a) a = b;
        printf("This number: %d", a);
        fclose(f);
        return 0;
    }
    
    printf("The file is empty :|");
    return 0;
}