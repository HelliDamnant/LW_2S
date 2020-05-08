#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define type_list "\
\nEnter:\n\
1 duration\n\
2 name\n\
3 genre\n\
4 year\n\
Type: "

#define commands_list "\
Enter:\n\
0 exit\n\
1 add\n\
2 delete by parameter\n\
3 show info\n\
4 show new movies\n\
5 delete by genre"

#define ERROR {printf("Error!\n");exit(1);}
#define STR_SIZE 10

union sub {
	char genre[STR_SIZE];
	int year;
};

typedef struct {
    int duration;
    char *title;
	union sub 
} film;

typedef struct {
    int *set;
    int size;
} set;

int check_year(int);
int get_num();
char* get_str();
void get_static_str();

set set_init();
void add_ind(int, set*);
set search(int, film*, int);
int delete(film*, int, set*);

void add_info(film**, int*);
void delete_info(film**, int*);
void output_info(film*, int);
void new_movies(film*, int);
void delete_by_genre(film**, int*);

int main()
{
    film *films = (film*)malloc(sizeof(film));
	if (!films) ERROR
    int n = 0;

    printf(commands_list);
    while (1)
    {
        printf("\nIn the list %d films\nEnter command: ", n);
        switch (get_num())
        {
            case 1: {
                add_info(&films, &n);
                break;
            } case 2: {
                delete_info(&films, &n);
                break;
            } case 3: {
                output_info(films, n);
                break;
            } case 4: {
                new_movies(films, n);
                break;
            } case 5: {
                delete_by_genre(&films, &n);
                break;
            } case 0: {
                if (n) free(films);
                return 0;
            } default: {
                ERROR
            }
        }
    }
}

int check_year(int a)
{
    return a > 1887 && a < 2021? 1 : 0;
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
    if (s == NULL) ERROR
    int k = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (!(s = (char*)realloc(s, ++k))) ERROR
        s[k - 1] = c;
    }
    if (!k) ERROR
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

set set_init()
{
    set set = {NULL, 0};
    set.set = (int*)malloc(1);
    if (!set.set) ERROR
    return set;
}

set search(int type, film *films, int n)
{
    set indexes = set_init();
    switch(type)
    {
        case 1: {
            printf("Enter duration: ");
            int param = get_num();

            for (int i = 0; i < n; i++) if (films[i].duration == param) add_ind(i, &indexes);

            return indexes;
        } case 2: {
            printf("Enter title: ");
            char *param = get_str();

            for (int i = 0; i < n; i++) if (strcmp(films[i].title, param) == 0) add_ind(i, &indexes);

            free(param);
            return indexes;
        } case 3: {
            printf("Enter genre: ");
            char param[STR_SIZE];
            get_static_str(param);

            for (int i = 0; i < n; i++) 
                if (!check_year(films[i].year))
                    if (!strcmp(films[i].sub.genre, param))
                        add_ind(i, &indexes);

            return indexes;
        } case 4: {
            printf("Enter year: ");
            int param = get_num();

            for (int i = 0; i < n; i++)
                if (check_year(films[i].year))
                    if (films[i].sub.year == param)
                        add_ind(i, &indexes);

            return indexes;
        } default: {
            ERROR
        }
    }
}

void add_info(film **films, int *n)
{
    *films = (film*)realloc(*films, (*n + 1) * sizeof(film));

    printf("\nEnter the duration of the movie: ");
    (*films)[*n].duration = get_num();

    printf("Enter the name of the movie: ");
    (*films)[*n].title = get_str();

    printf("1 - genre, 2 - year: ");
    switch (get_num())
    {
        case 1: {
            printf("Enter the genre of the movie: ");
            get_static_str((*films)[*n].sub.genre);
            break;
        } case 2: {
            printf("Enter the release year of the movie: ");
            (*films)[*n].year = get_num();
            if (!check_year((*films)[*n].sub.year)) ERROR
            break;
        } default: {
            ERROR
        }
    }

    ++(*n);
}

void output_info(film *films, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n%d.\nDuration: %d\nName: %s\n", i + 1, films[i].duration, films[i].title);
        if (check_year(films[i].year))
            printf("Year: %d\n", films[i].sub.year);
        else
            printf("Genre: %s\n", films[i].sub.genre);
    }
}

void delete_info(film **films, int *n)
{
    printf(type_list);
    set indexes = search(get_num(), *films, *n);
    
    if (!indexes.size) {
        printf("Not found\n");
        free(indexes.set);
        return;
    }

    *n = delete(*films, *n, &indexes);
    *films = (film*)realloc(*films, *n * sizeof(film));

    free(indexes.set);
}

void new_movies(film *films, int n)
{
    set inds = set_init();
    for (int i = 0; i < n; i++) if (check_year(films[i].sub.year)) add_ind(i, &inds);

    if (inds.size < 3) {
        printf("Not enough elements\n");
        return;
    }

    for (int i = 0; i < inds.size / 3; i++)
    {
        int max = inds.set[i];

        for (int j = max + 1; j < inds.size; j++)
			if (films[inds.set[max]].sub.year < films[inds.set[j]].sub.year) max = j;

        printf("\nDuration: %d\nName: %s\nYear: %d\n",\
               films[inds.set[max]].duration,\
               films[inds.set[max]].title,\
               films[inds.set[max]].sub.year\
              );
    }

    free(inds.set);
}

void delete_by_genre(film **films, int *n)
{
    set indexes = search(3, *films, *n);
    
    if (!indexes.size) {
        printf("Not found\n");
        free(indexes.set);
        return;
    }

    *n = delete(*films, *n, &indexes);
    *films = (film*)realloc(*films, *n * sizeof(film));

    free(indexes.set);
}