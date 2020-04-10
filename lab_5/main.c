#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!");exit(1);}
#define CONST_VOID_TYPE const void *

typedef struct Stack
{
    void *data;
    struct Stack *next;
} Stack;

void writing_stack(Stack*, FILE*);
char* read_str(FILE*);
char* get_str();
void push(Stack**, CONST_VOID_TYPE, unsigned int);
void pop(Stack**);
void stack_free(Stack*);

int main()
{
    printf("Enter the name of the file with numeric information: ");
    char *file_numeric = get_str();
    printf("Enter the name of the file with text information: ");
    char *file_text = get_str();
    printf("Enter a name for the new file: ");
    char *new_file = get_str();

    FILE *f_num = NULL, *f_text = NULL;
    if ((f_num = fopen(file_numeric, "r")) == NULL) ERROR
    if ((f_text = fopen(file_text, "r")) == NULL) ERROR
    if (feof(f_num) || feof(f_text)) ERROR

    Stack *stack = NULL;
    char *number, *word;
    while ((number = read_str(f_num)) != NULL && (word = read_str(f_text)) != NULL)
    {
        push(&stack, (CONST_VOID_TYPE)number, strlen(number) * sizeof(char));
        push(&stack, (CONST_VOID_TYPE)word, strlen(word) * sizeof(char));
    }

    fclose(f_num);
    fclose(f_text);

    FILE *f_new = NULL;
    if ((f_new = fopen(new_file, "w")) == NULL) ERROR
    writing_stack(stack, new_file);
    fclose(f_new);

    stack_free(stack);
    return 0;   
}

void writing_stack(Stack *stack, FILE *f)
{
    Stack *temp = stack;
    while (temp != NULL)
    {
        fprintf(f, "%s ", (char*)temp->data);
        temp = temp->next;
    }
}

char* read_str(FILE *f)
{
    if (feof(f)) return NULL;
    
    // удаление пробелов и переносов строки
    char c;
    while ((c = fgetc(f)) != EOF) if (c != ' ' && c != '\n') break;
    if (feof(f)) return NULL;

    // считывание слова
    int k = 0;
    char *s = NULL;
    if ((s = (char*)calloc(1,1)) == NULL) ERROR
    do
    {
        s = (char*)realloc(s, ++k * sizeof(char));
        s[k - 1] = c;
    }
    while ((c = fgetc(f)) != ' ' && c != '\n' && c != EOF);
    return s;
}

char* get_str()
{
    char *s = (char*)calloc(200, sizeof(char));
    fgets(s, 200, stdin);
    s[strlen(s) - 1] = 0;
    s = (char*)realloc(s, strlen(s) * sizeof(char));
    return s;
}

void push(Stack **stack, CONST_VOID_TYPE data, unsigned int t_size)
{
    Stack *temp = (Stack*)malloc(sizeof(Stack));
    if (temp == NULL) ERROR
   
    temp->data = malloc(t_size);
    if (temp->data == NULL) ERROR
    
    memcpy(temp->data, data, t_size);
    
    temp->next = *stack;
    *stack = temp;   
}

void pop(Stack **stack)
{
    Stack *previous = NULL;
    if (stack == NULL) ERROR

    previous = (*stack);
    (*stack) = (*stack)->next;
	
    free(previous->data);
    free(previous);
}

void stack_free(Stack *stack)
{
    if (stack == NULL) ERROR;
    while (stack != NULL) pop(&stack);
}