#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!");exit(1);}
#define CONST_VOID_TYPE const void *

typedef struct Stack {
    void *data;
    struct Stack *next;
} Stack;

char* read_str(FILE*);
char* get_str();
void push(Stack**, CONST_VOID_TYPE, unsigned int);
void pop(Stack**);

int main()
{
    printf("Enter the name of the file with numeric information: ");
    char *file_numeric = get_str();
    printf("Enter the name of the file with text information: ");
    char *file_text = get_str();
    printf("Enter a name for the new file: ");
    char *new_file = get_str();

    FILE *f_num = fopen(file_numeric, "r"),
         *f_text = fopen(file_text, "r");
    if (!f_num || !f_text) ERROR
    if (feof(f_num) || feof(f_text)) ERROR

    Stack *stack = NULL;

    char *number, *word;
    while ((number = read_str(f_num)) && (word = read_str(f_text)))
    {
        push(&stack, (CONST_VOID_TYPE)number, strlen(number) * sizeof(char));
        push(&stack, (CONST_VOID_TYPE)word, strlen(word) * sizeof(char));
    }
    fclose(f_num);
    fclose(f_text);

    FILE *f_new = fopen(new_file, "w");
    if (!f_new) ERROR

    while (stack)
    {
        fprintf(f_new, "%s ", (char*)stack->data);
        pop(&stack);
    }

    fclose(f_new);
    return 0;
}

char* read_str(FILE *f)
{
    if (feof(f)) return NULL;

    char c;
    while ((c = fgetc(f)) != EOF) if (c != ' ' && c != '\n') break;
    if (feof(f)) return NULL;

    int k = 0;
    char *s = (char*)calloc(1,1);
    if (!s) ERROR
    do
    {
        s = (char*)realloc(s, ++k * sizeof(char));
        if (!s) ERROR
        s[k - 1] = c;
    }
    while ((c = fgetc(f)) != ' ' && c != '\n' && c != EOF);
    return s;
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

void push(Stack **stack, CONST_VOID_TYPE data, unsigned int t_size)
{
    Stack *temp = (Stack*)malloc(sizeof(Stack));
    if (!temp) ERROR

    temp->data = malloc(t_size);
    if (!temp->data) ERROR

    memcpy(temp->data, data, t_size);

    temp->next = *stack;
    *stack = temp;
}

void pop(Stack **stack)
{
    if (!stack) ERROR

    Stack *previous;
    previous = *stack;
    *stack = (*stack)->next;

    free(previous->data);
    free(previous);
}