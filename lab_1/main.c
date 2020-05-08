#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define type_list "\
Enter:\n\
1 duration\n\
2 name\n\
3 genre\n\
4 release\n\
Type: "

#define commands_list "\
Enter:\n\
0 to exit\n\
1 to add\n\
2 to delete by parameter\n\
3 to delete by duration\n\
4 to find movie having title\n\
5 to output all info\n"

#define ERROR {printf("Error!\n");exit(1);}
#define STR_SIZE 20

typedef struct {
    char genre[STR_SIZE];
} sub;

typedef struct {
    int duration;
    char *title;
    sub sub;
    int year;
} film;

typedef struct {
    int *set;
    int size;
} set;

int get_num();
char* get_str();
void get_static_str(char*);

set set_init();
void add_ind(int, set*);

set search_by_parametr(int, film*, int);
int delete(film*, int, set*);

void add_info(film**, int*);
void delete_info(film**, int*);
void delete_longest(film**, int*);
void find_having_title(film*, int);
void output_info(film*, int);


int main()
{
    film *films = (film*)malloc(sizeof(film));
    if (!films) ERROR
    int n = 0;

    printf(commands_list);
    while(1)
    {
        printf("\nIn the list %d films\nEnter command: ", n);
        switch(get_num())
        {
            case 1: {
                add_info(&films, &n);
                break;
            } case 2: {
                delete_info(&films, &n);
                break;
            } case 3: {
                delete_longest(&films, &n);
                break;
            } case 4: {
                find_having_title(films, n);
                break;
            } case 5: {
                output_info(films, n);
                break;
            } case 0: {
                if (n) free(films);
                return 0;
            } default: {
                if (n) free(films);
                ERROR
            }
        }
    }
}

int get_num()
{
    unsigned int a;
    if (scanf("%d", &a)) {
        getchar();
        return a;
    } else {
        ERROR
    }
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

void get_static_str(char *s)
{
    int k = 0;
    char c;
    while ((c = getchar()) != '\n' && k < STR_SIZE - 1) s[k++] = c;
    if (!k) ERROR
    s[k] = 0;
    fflush(stdin);
}

void add_ind(int index, set *indexes)
{
    indexes->size++;
    indexes->set = (int*)realloc(indexes->set, indexes->size * sizeof(int));
    indexes->set[indexes->size] = index;
}

set search_by_parametr(int type, film *films, int n)
{
    set indexes = set_init();
    printf("Enter parameter: ");
    switch(type)
    {
        case 1: {
            int param = get_num();

            for (int i = 0; i < n; i++) if (films[i].duration == param) add_ind(i, &indexes);

            return indexes;
        } case 2: {
            char *param = get_str();

            for (int i = 0; i < n; i++) if (!strcmp(films[i].title, param)) add_ind(i, &indexes);

            free(param);
            return indexes;
        } case 3: {
            char param[STR_SIZE];
            get_static_str(param);

            for (int i = 0; i < n; i++) if (strcmp(films[i].sub.genre, param) == 0) add_ind(i, &indexes);

            return indexes;
        } case 4: {
            int param = get_num();

            for (int i = 0; i < n; i++) if (films[i].year == param) add_ind(i, &indexes);

            return indexes;
        } default: {
            free(indexes.set);
            ERROR
        }
    }
}

set set_init()
{
    set set = {NULL, 0};
    set.set = (int*)malloc(1);
    if (!set.set) ERROR
    return set;
}

int delete(film *films, int n, set *indexes)
{
    if (indexes->size > 1)
    {
        int i = indexes->set[1],
            j = i + 1,
            t = 2;

        while (t <= indexes->size && j < n)
            if (j++ != indexes->set[t])
                films[i++] = films[j];
            else
                t++;
        
        n = i;
    }
    else
    {
        n = n - 1;
        for (int i = indexes->set[1]; i < n; i++) films[i] = films[i + 1];
    }

    return n;
}

void add_info(film **films, int *n)
{
    *films = (film*)realloc(*films, (*n + 1) * sizeof(film));

    printf("\nEnter the duration of the movie: ");
    (*films)[*n].duration = get_num();

    printf("Enter the name of the movie: ");
    (*films)[*n].title = get_str();

    printf("Enter the genre of the movie: ");
    get_static_str((*films)[*n].sub.genre);
    
    printf("Enter the release year of the movie: ");
    (*films)[*n].year = get_num();

    ++(*n);
}

void delete_info(film **films, int *n)
{
    printf(type_list);
    set indexes = search_by_parametr(get_num(), *films, *n);
    
    if (!indexes.size) {
        printf("Not found\n");
        free(indexes.set);
        return;
    }

    *n = delete(*films, *n, &indexes);
    *films = (film*)realloc(*films, *n * sizeof(film));

    free(indexes.set);
}

void delete_longest(film **films, int *n)
{
    set indexes = set_init();

    printf("Enter duration: ");
    int param = get_num();

    for (int i = 0; i < *n; i++) if ((*films)[i].duration > param) add_ind(i, &indexes);

    if (indexes.size) {
        printf("Not found\n");
        free(indexes.set);
        return;
    }

    *n = delete(*films, *n, &indexes);
    *films = (film*)realloc(*films, *n * sizeof(film));

    free(indexes.set);
}

void find_having_title(film *films, int n)
{
    printf("Have title:\n");
    for (int i = 0; i < n; i++) if (strlen(films[i].title)) printf("%s\n", films[i].title);
}

void output_info(film *films, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d.\nDuration: %d\nTitle: %s\n", i + 1, films[i].duration, films[i].title);
}