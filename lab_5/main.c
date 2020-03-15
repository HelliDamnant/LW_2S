#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!");exit(1);}
#define STACK_TYPE void *
#define CONST_STACK_TYPE const void *

typedef struct Stack
{
    STACK_TYPE _data;
    struct Stack *_next;
} Stack;

char* get_filename();
void push(Stack **stack, CONST_STACK_TYPE data, unsigned int t_size);
void pop(Stack **stack);
void stack_free(Stack **stack);
unsigned int stack_size(Stack *stack);

int input(char *path)
{
    FILE *f = NULL;
    if ((f = fopen(path, "w")) == NULL) return 1;

    int a;
    while(scanf("%d", &a))
        if (a)
        {
            fwrite(&a, sizeof(int), 1, f);
            fflush(stdin);
        }
        else
        {
            fclose(f);
            return 0;
        }

    return 1;
}

int main()
{
    printf("Enter the name of the file with text information: ");
    char *file_text = get_filename();
    printf("Enter the name of the file with numeric information: ");
    char *file_numeric = get_filename();
    printf("Enter a name for the new file: ");
    char *new_file = get_filename();

    printf("Begin input (to finish enter 0):\n");
    if (input(file_numeric)) ERROR
    printf("End\n");

    FILE *f1 = NULL;
    if ((f1 = fopen(file_numeric, "r")) == NULL) ERROR

    Stack *univ_stack = NULL;
    int a, n = 0;
    while (fread(&a, sizeof(int), 1, f1) && a != EOF)
    {
        n++;
        push(&univ_stack, (CONST_STACK_TYPE)&a, sizeof(int));
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%d element: %d\n", i, *((int*)univ_stack->_data));
        pop(&univ_stack);
    }

    fclose(f1);
    return 0;   
}

char* get_filename()
{
    char *s = (char*)calloc(200, sizeof(char));
    fgets(s, 200, stdin);
    s[strlen(s) - 1] = 0;
    s = (char*)realloc(s, strlen(s) * sizeof(char));
    return s;
}

// добавление элемента в стек
void push(Stack **stack, CONST_STACK_TYPE data, unsigned int t_size)
{
    Stack *temp = (Stack*)malloc(sizeof(Stack));
    if (temp == NULL) ERROR
   
    temp->_data = malloc(t_size);
    if (temp->_data == NULL) ERROR
    
    memcpy(temp->_data, data, t_size);
    
    temp->_next = *stack;
    *stack = temp;
}

void pop(Stack **stack)
{
    Stack *previous = NULL;
    if (stack == NULL) ERROR

    previous = (*stack);
    (*stack) = (*stack)->_next;
	
    free(previous->_data);
    free(previous);
}

unsigned int stack_size(Stack *stack)
{
	Stack *temp = stack;
	unsigned int size = 0;

	while (temp != NULL)
    {
		++size;
		temp = temp->_next;
	}

	return size;
}

void stack_free(Stack **stack)
{
    if (*stack == NULL) ERROR;
    while ((*stack)->_next != NULL)
    {
        pop(stack);
        *stack = (*stack)->_next;
    }

	free((*stack)->_data);
    free(*stack);
	*stack = NULL;
}