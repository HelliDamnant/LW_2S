#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!\n");exit(1);}

char* get_str();
int flip_substring(char *path, char c1, char c2);

int main()
{
    printf("Enter file name: ");
    char *path = get_str();

    char index_beggining, index_end;
    printf("Enter symbols: ");
    scanf("%c%c", &index_beggining, &index_end);

    if (flip_substring(path, index_beggining, index_end) == -1) ERROR

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

int flip_substring(char *path, char c1, char c2)
{
	FILE *f = fopen(path, "r + w");
    if (!f) return -1;

    int c;
    while ((c = getc(f)) != EOF && c != c1);
    if (c == EOF) return -1;
    int p1 = ftell(f) - 1;

    while ((c = getc(f)) != EOF && c != c2);
    if (c == EOF) return -1;
    int p2 = ftell(f) - 1;

    do {
        fseek(f, p1, 0);
        c1 = getc(f);
        fseek(f, p2, 0);
        c2 = getc(f);

        fseek(f, p1, 0);
        putc(c2, f);
        fseek(f, p2, 0);
        putc(c1, f);
    } while (++p1 < --p2);

    fclose(f);
    return 0;
}