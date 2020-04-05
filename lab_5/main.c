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
void input(char *path);
void push(Stack **stack, CONST_STACK_TYPE data, unsigned int t_size);
void pop(Stack **stack);
void stack_free(Stack **stack);
unsigned int stack_size(Stack *stack);

int main()
{
    printf("Enter the name of the file with numeric information: ");
    char *file_numeric = get_filename();
    printf("Enter the name of the file with text information: ");
    char *file_text = get_filename();
    printf("Enter a name for the new file: ");
    char *new_file = get_filename();

    FILE *f1 = NULL,
         *f2 = NULL,
         *f3 = NULL;
    if ((f1 = fopen(file_numeric, "r")) == NULL) ERROR
    if ((f2 = fopen(file_text, "r")) == NULL) ERROR
    if ((f3 = fopen(new_file, "w")) == NULL) ERROR

    Stack *univ_stack = NULL;

    // код без говнокода это плохой код
    char *number = (char*)calloc(100, sizeof(char)),
         *word = (char*)calloc(100, sizeof(char));
    while (fscanf(f1, "%s", number) != EOF && fscanf(f2, "%s", word) != EOF)
    {
        number = (char*)realloc(number, strlen(number) * sizeof(char));
        word = (char*)realloc(word, strlen(word) * sizeof(char));

        push(&univ_stack, (CONST_STACK_TYPE)word, strlen(word) * sizeof(char));
        push(&univ_stack, (CONST_STACK_TYPE)number, strlen(number) * sizeof(char));

        number = (char*)realloc(number, 100 * sizeof(char));
        word = (char*)realloc(word, 100 * sizeof(char));
    }
    // но надо знать меру

    while (univ_stack->_next != NULL)
    {
        fprintf(f3, "%s ", (char*)univ_stack->_data);
        pop(&univ_stack);
    }
    fprintf(f3, "%s", (char*)univ_stack->_data);
    pop(&univ_stack);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;   
}

// получение имени файла
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

// удаление элемента из стека
void pop(Stack **stack)
{
    Stack *previous = NULL;
    if (stack == NULL) ERROR

    previous = (*stack);
    (*stack) = (*stack)->_next;
	
    free(previous->_data);
    free(previous);
}

// получение размера стека
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

// освобождение стека
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