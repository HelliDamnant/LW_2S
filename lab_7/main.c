#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!");exit(1);}
#define CONST_VOID_TYPE const void *

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    int size;
    Node *head;
} List;

void insert(List*, int, CONST_VOID_TYPE, unsigned int);
void push_back(List*, CONST_VOID_TYPE, unsigned int);
void inserting_words(List*);
char* read_str(FILE*);
char* get_str();
void push(List**, CONST_VOID_TYPE, unsigned int);
void pop(List**);
void list_free(List*);

int main()
{
	FILE *f = fopen("data.txt", "r");
    if (!f) ERROR

    List *list = (List*)malloc(sizeof(List));
    if (!list) ERROR
    list->size = 0;

    char *str;
    while ((str = read_str(f))) push(&list, (CONST_VOID_TYPE)str, strlen(str) * sizeof(char));

    inserting_words(list);

    while (list->head)
    {
        printf("%s ", (char*)list->head->data);
        pop(&list);
    }

    free(list);
    return 0;   
}

void inserting_words(List *list)
{
    printf("Enter a parameter: ");
    char *param = get_str();

    int i = 1;
    Node *temp = list->head;
    while (temp)
    {
        if (!strcmp((char*)temp->data, param)) {
            printf("Enter a new element: ");
            char *str = get_str();
            if (i == 1)
                push(&list, (CONST_VOID_TYPE)str, strlen(str) * sizeof(char));
            else
                insert(list, i - 1, (CONST_VOID_TYPE)str, strlen(str) * sizeof(char));
            i++;
        }
        temp = temp->next;
        i++;
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
    if (!(s = (char*)calloc(1,1))) ERROR
    do {
        s = (char*)realloc(s, ++k * sizeof(char));
        s[k - 1] = c;
    } while ((c = fgetc(f)) != ' ' && c != '\n' && c != EOF);
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

void insert(List *list, int pos, CONST_VOID_TYPE data, unsigned int t_size)
{
    Node *prev = list->head;
    while (--pos) prev = prev->next;

    Node *temp = (Node*)malloc(sizeof(Node));
    if (!temp) ERROR
   
    temp->data = malloc(t_size);
    if (!temp->data) ERROR
    
    memcpy(temp->data, data, t_size);

    temp->next = prev->next;
    prev->next = temp;
    list->size++;
}

void push(List **list, CONST_VOID_TYPE data, unsigned int t_size)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    if (!temp) ERROR
   
    temp->data = malloc(t_size);
    if (!temp->data) ERROR
    
    memcpy(temp->data, data, t_size);
    
    (*list)->size++;
    temp->next = (*list)->head;
    (*list)->head = temp;
}

void pop(List **list)
{
    if (!(*list)->head) ERROR

    Node *previous = (*list)->head;
    (*list)->size--;
    (*list)->head = (*list)->head->next;
	
    free(previous->data);
    free(previous);
}

void list_free(List *list)
{
    if (!list) ERROR;
    while (list) pop(&list);
}