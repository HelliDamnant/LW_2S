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

    printf("Begin input (to finish enter 0):\n");
    if (input(path)) ERROR
    printf("End");

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
    FILE *f = fopen(path, "wb");
	if (!f) return 1;

    int a;
    while(scanf("%d", &a))
        if (a) {
            fwrite(&a, sizeof(int), 1, f);
            fflush(stdin);
        } else {
            fclose(f);
            return 0;
        }

    return 1;
}