#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!");exit(1);}
#define VOID_TYPE void *
#define CONST_VOID_TYPE const void *

typedef struct Node {
    VOID_TYPE data;
    struct Node *next;
} Node;

typedef struct Queue {
    int count;
    Node *head;
    Node *tail;
} Queue;

Queue** read_file(int*);
int comparison(Queue*, Queue*);
void queue_init(Queue**);
void push(Queue**, CONST_VOID_TYPE, unsigned);
void pop(Queue**);
void queue_free(Queue*);

int main()
{
    int size;
    Queue **array_queues = read_file(&size);

    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
            if (comparison(*(array_queues + i), *(array_queues + j))) break;
        if (j != size) break;
    }
    printf("Queue number %d and queue number %d are equal", i + 1, j + 1);
 
    for (int i = 0; i < size; i++) queue_free(*(array_queues + i));
    free(array_queues);

    return 0;
}

int comparison(Queue *queue_1, Queue *queue_2)
{
    if (queue_1->count != queue_2->count) return 0;
    
    Node *temp_1 = queue_1->head,
         *temp_2 = queue_2->head;

    int t = queue_1->count;
    while (t--)
        if (!strcmp((char*)temp_1->data, (char*)temp_2->data)) {
            temp_1 = temp_1->next;
            temp_2 = temp_2->next;
        } else {
            return 0;
        }
    return 1;
}

Queue** read_file(int *_size)
{
    FILE *f = NULL;
    if ((f = fopen("data.txt", "r")) == NULL) ERROR
    
    Queue **temp = NULL;
    if ((temp = (Queue**)malloc(sizeof(Queue*))) == NULL) ERROR
    queue_init(temp + 0);
    
    char *str = NULL;
    if ((str = (char*)calloc(1,1)) == NULL) ERROR
    
    int temp_size = 1,
        str_size = 0;

    char c;
    while ((c = fgetc(f)) != EOF)
        if (c == '\n') {
            push(temp + (temp_size - 1), (CONST_VOID_TYPE)str, str_size * sizeof(char));
            str_size = 0;
            temp = (Queue**)realloc(temp, ++temp_size * sizeof(Queue*));
            queue_init(temp + (temp_size - 1));
        } else if (c == ' ') {
            push(temp + (temp_size - 1), (CONST_VOID_TYPE)str, str_size * sizeof(char));
            str_size = 0;
        } else {
            str = (char*)realloc(str, ++str_size * sizeof(char));
            str[str_size - 1] = c;
        }

    free(str);
    fclose(f);
    *_size = temp_size;
    return temp;
}

void queue_init(Queue **q)
{
    if (((*q) = (Queue*)malloc(sizeof(Queue))) == NULL) ERROR
    (*q)->count = 0;
    (*q)->head = NULL;
    (*q)->tail = NULL;
}

void push(Queue **queue, CONST_VOID_TYPE _data, unsigned t_size)
{
    Node *tmp = NULL;
    if ((tmp = (Node*)malloc(sizeof(Node))) == NULL) ERROR
    
    tmp->data = NULL;
    tmp->next = NULL;

    if ((tmp->data = malloc(t_size)) == NULL) ERROR
    memcpy(tmp->data, _data, t_size);

    if ((*queue)->count)
        (*queue)->tail = (*queue)->tail->next = tmp;
    else
        (*queue)->head = (*queue)->tail = tmp;

    (*queue)->count++;
}

void pop(Queue **queue)
{
    if (!(*queue)->count) ERROR

    Node *tmp = (*queue)->head;

    (*queue)->head = (*queue)->head->next;
    (*queue)->count--;

    free(tmp->data);
    free(tmp);
}

void queue_free(Queue *queue)
{
    if (queue == NULL) ERROR

    while (queue->count) pop(&queue);

    free(queue);
	queue = NULL;
}