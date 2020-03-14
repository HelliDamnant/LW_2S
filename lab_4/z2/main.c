#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_path();
int counting_occurrences(char *path, char c);

int main()
{
    printf("Enter file name: ");
    char *path = get_path();

    char c;
    printf("Enter symbol: ");
    scanf("%c", &c);
    
    int number_char;
    if ((number_char = counting_occurrences(path, c)) == -1)
    {
        printf("Error!");
        exit(1);
    }
    printf("Number occurrences: %d", number_char);

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

int counting_occurrences(char *path, char c)
{
    FILE *f = NULL;
    if ((f = fopen(path, "r")) == NULL) return -1;

    int k = 0;
    char ch;
    while ((ch = getc(f)) != EOF) if (ch == c) k++;

    fclose(f);
    return k;
}