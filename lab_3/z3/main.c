#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!\n");exit(1);}

char* get_str();
int input(char *path);

int main()
{
    printf("Enter file name: ");
    char *path = get_str();

    if (input(path)) ERROR

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

int input(char *path)
{
	FILE *f = fopen(path, "r + w");
    if (!f) return 1;

    printf("Enter the number of items: ");
    int n;
    if (!scanf("%d", &n)) return 1;

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