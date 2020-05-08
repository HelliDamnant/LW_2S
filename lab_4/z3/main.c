#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_path();
int flip_substring(char *path, char c1, char c2);

int main()
{
    printf("Enter file name: ");
    char *path = get_path();

    char index_beggining, index_end;
    printf("Enter symbols: ");
    scanf("%c%c", &index_beggining, &index_end);
    
    if (flip_substring(path, index_beggining, index_end) == -1)
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

int flip_substring(char *path, char c1, char c2)
{
    FILE *f = NULL;
    if ((f = fopen(path, "r + w")) == NULL) return -1;

    int c;
    while ((c = getc(f)) != EOF && c != c1);
    if (c == EOF) return -1;
    int p1 = ftell(f) - 1;

    while ((c = getc(f)) != EOF && c != c2);
    if (c == EOF) return -1;
    int p2 = ftell(f) - 1;
    
    do
    {
        fseek(f, p1, 0);
        c1 = getc(f);
        fseek(f, p2, 0);
        c2 = getc(f);

        fseek(f, p1, 0);
        putc(c2, f);
        fseek(f, p2, 0);
        putc(c1, f);
    }
    while (++p1 < --p2);

    fclose(f);
    return 0;
}