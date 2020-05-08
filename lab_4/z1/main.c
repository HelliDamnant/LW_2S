#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_path();
int input_and_write(char *path);
int read_and_output(char *path);

int main()
{
    printf("Enter file name: ");
    char *path = get_path();

    printf("Enter symbols: ");
    if (input_and_write(path))
    {
        printf("Error!");
        exit(1);
    }

    printf("Result: ");
    if (read_and_output(path))
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

int input_and_write(char *path)
{
    FILE *f = NULL;
    if ((f = fopen(path, "w")) == NULL) return 1;

    char c;
    while (scanf("%c", &c) && c != '\n')
    {
        fflush(stdin);
        putc(c, f);
    }
    putc(EOF, f);

    if (c == '\n')
    {
        fclose(f);
        return 0;   
    }
    else
        return 1;
}
int read_and_output(char *path)
{
    FILE *f = NULL;
    if ((f = fopen(path, "r")) == NULL) return 1;
    
    char c;
    while ((c = getc(f)) != EOF) printf("%c ", c);

    fclose(f);
    return 0;
}