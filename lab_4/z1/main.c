#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!\n");exit(1);}

char* get_str();
int input_and_write(char *path);
int read_and_output(char *path);

int main()
{
    printf("Enter file name: ");
    char *path = get_str();

    printf("Enter symbols: ");
    if (input_and_write(path)) ERROR

    printf("Result: ");
    if (read_and_output(path)) ERROR

    free(path);
    return 0;
}

char* get_str()
{
	char *s = (char*)calloc(1, 1);
	if (!s) ERROR

	int k = 0;
	char c;
	while ((c = getchar()) != '\n')
	{
		if (!(s = (char*)realloc(s, ++k))) ERROR
		s[k - 1] = c;
	}

	return s;
}

int input_and_write(char *path)
{
	FILE *f = fopen(path, "w");
    if (!f) return 1;

    char c;
    while (scanf("%c", &c) && c != '\n')
    {
        fflush(stdin);
        putc(c, f);
    }
    putc(EOF, f);

    if (c == '\n') {
        fclose(f);
        return 0;
    } else {
		return 1;
	}
}
int read_and_output(char *path)
{
	FILE *f = fopen(path, "r");
    if (!f) return 1;

    char c;
    while ((c = getc(f)) != EOF) printf("%c ", c);

    fclose(f);
    return 0;
}