#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!\n");exit(1);}

char* get_str();
int search(char *path);

int main()
{
    printf("Enter file name: ");
    char *path = get_str();

    if (search(path)) ERROR

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

int search(char *path)
{
	FILE *f = fopen(path, "rb");
    if (!f) return 1;

    int a, b;
    if (fread(&a, sizeof(int), 1, f) > 0) {
        while (fread(&b, sizeof(int), 1, f) > 0 && b > a) a = b;
        printf("This number: %d", a);
    } else {
        printf("The file is empty.");
	}

    fclose(f);
    return 0;
}