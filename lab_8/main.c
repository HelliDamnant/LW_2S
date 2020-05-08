#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR {printf("Error!");exit(1);}
#define STR_SIZE 20

typedef struct Node {
    char original[STR_SIZE];
    char translated[STR_SIZE];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Stack {
    Node *data;
    struct Stack *next;
} Stack;

void push(Stack**, Node*);
int get_command();
Node* pop(Stack**);
Node* get_free_node(char*, char*);
void add_node(Node**, char*, char*);
Node* delete_node(Node**, char*);
void view_tree(Node*);
void view_tree_without_rec(Node*);
void free_tree(Node*);

int main()
{
    printf("1 - add node\n2 - delete node\n3 - tree view\n4 - view tree without recursion\n5 - exit\n\n");
    Node *root = NULL;
    while (1)
    {
        printf("Type command: ");
        switch (get_command())
        {
            case 1: {
                printf("Enter a word and its translation separated by a space: ");
                char original[STR_SIZE], translated[STR_SIZE];
                if (scanf("%s%s", original, translated) != 2) ERROR
                add_node(&root, original, translated);
                break;
            }
            case 2: {
                printf("Enter the word you want to delete: ");
                char param[STR_SIZE];
                if (!scanf("%s", param)) ERROR
                delete_node(&root, param);
                break;
            }
            case 3: {
                view_tree(root);
                break;
            }
            case 4: {
                view_tree_without_rec(root);
                break;
            }
            case 5: {
                if (root) free_tree(root);
                return 0;
            }
        }
    }
}

int get_command()
{
    int a;
    if (!scanf("%d", &a) || a < 1 || a > 5) ERROR;
    return a;
}

void push(Stack **stack, Node *node)
{
    Stack *temp = (Stack*)malloc(sizeof(Stack));
    if (temp == NULL) ERROR

    temp->data = node;
    temp->next = *stack;

    *stack = temp;   
}

Node* pop(Stack **stack)
{
    if (stack == NULL) ERROR

    Stack *previous = *stack;
    Node *top = (*stack)->data;
    *stack = (*stack)->next;
	
    free(previous);

    return top;
}

Node* get_free_node(char s1[STR_SIZE], char s2[STR_SIZE])
{
    Node *temp = (Node*)malloc(sizeof(Node));
    if (!temp) ERROR

    strcpy(temp->original, s1);
    strcpy(temp->translated, s2);
    temp->left = temp->right = NULL;

    return temp;
}

void add_node(Node **node, char s1[STR_SIZE], char s2[STR_SIZE])
{
    if (!(*node)) {
        *node = get_free_node(s1, s2);
    } else {
        if (!strcmp(s1, (*node)->original)) ERROR
        if (strlen(s1) < strlen((*node)->original))
            add_node(&(*node)->left, s1, s2);
        else
            add_node(&(*node)->right, s1, s2);
    }
}

Node* delete_node(Node **node, char param[STR_SIZE])
{
    if (!(*node))
        return *node;
    else if (strcmp((*node)->original, param))
        if (strlen(param) < strlen((*node)->original))
            (*node)->left = delete_node(&(*node)->left, param);
        else
            (*node)->right = delete_node(&(*node)->right, param);
    else
        if (!(*node)->left && !(*node)->right) {
            free(*node);
            *node = NULL;
        } else if ((*node)->left && !(*node)->right) {
            Node *temp = *node;
            *node = (*node)->left;
            free(temp);
        } else if (!(*node)->left && (*node)->right) {
            Node *temp = *node;
            *node = (*node)->right;
            free(temp);
        } else {
            Node *temp = (*node)->right;
            while (temp) temp = temp->left;
            strcpy((*node)->original, temp->original);
            strcpy((*node)->translated, temp->translated);
            (*node)->right = delete_node(&(*node)->right, temp->original);
        }

    return *node;
}

void view_tree(Node *node)
{
    if (node) {
        view_tree(node->left);
        view_tree(node->right);
        printf("%s %s\n", node->original, node->translated);
    }
}

void view_tree_without_rec(Node *node)
{
    Stack *stack = NULL;
    while (1)
        if (node) {
            push(&stack, node);
            node = node->left;
        } else if (stack) {
            node = pop(&stack);
            printf("%s %s\n", node->original, node->translated);
            node = node->right;
        } else {
            break;
        }
}

void free_tree(Node *node)
{
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}