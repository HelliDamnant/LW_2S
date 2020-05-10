#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!\n");exit(1);}

char* get_str();
int counting_occurrences(char *path, char c);

int main()
{
    printf("Enter file name: ");
    char *path = get_str();

    char c;
    printf("Enter symbol: ");
    scanf("%c", &c);

    int number_char;
    if ((number_char = counting_occurrences(path, c)) == -1) ERROR
    printf("Number occurrences: %d", number_char);

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

int counting_occurrences(char *path, char c)
{
	FILE *f = fopen(path, "r");
    if (!f) return -1;

    int k = 0;
    char ch;
    while ((ch = getc(f)) != EOF) if (ch == c) k++;

    fclose(f);
    return k;
}