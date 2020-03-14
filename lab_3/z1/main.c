#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_path();
int input(char *path);

int main()
{
    printf("Enter file name: ");
    char *path = get_path();

    printf("Begin input (to finish enter 0):\n");
    if (input(path))
    {
        printf("Error!");
        exit(1);
    }
    printf("End");

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
    if ((f = fopen(path, "wb")) == NULL) return 1;

    int a;
    while(scanf("%d", &a))
        if (a)
        {
            fwrite(&a, sizeof(int), 1, f);
            fflush(stdin);
        }
        else
        {
            fclose(f);
            return 0;
        }

    return 1;
}