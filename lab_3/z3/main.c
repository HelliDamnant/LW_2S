#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_path();
int input(char *path);

int main()
{
    printf("Enter file name: ");
    char *path = get_path();

    if (input(path))
    {
        printf("Error!");
        exit(1);
    }
    
    free(path);
    return 0;
}

char* get_path()
{
    char *s = (char*)calloc(200, sizeof(char));
    fgets(s, 200, stdin);
    s[strlen(s) - 1] = 0;
    s = (char*)realloc(s, strlen(s) * sizeof(char));
    return s;
}

int input(char *path)
{
    FILE *f = NULL;
    if ((f = fopen(path, "r + w")) == NULL) return -1;

    printf("Enter the number of items: ");
    int n;
    if (scanf("%d", &n) == 0)
    {
        printf("Error");
        return 1;
    }

    printf("Enter the numbers:\n");
    int a, b;
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

    if (!n) return 1;

    fclose(f);
    return 0;
}