#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define parameteres_list "\
\nEnter:\n\
1 to search by duration.\n\
2 to search by name.\n\
3 to search by genre.\n\
4 to search by year of release.\n\
Type: "

#define commands_list "\
Enter:\n\
0 to exit\n\
1 to add an element\n\
2 to delete movies by parameter\n\
3 to display movies by parameter\n\
4 to display new movies\n\
5 to delete movies by genre"

#define ERROR {printf("Error!\n");exit(1);}
#define STR_SIZE 10

typedef struct {
    int duration;
    char *title;
    union {
        char genre[STR_SIZE];
        int year;
    }; 
} film;

int* search_by_genre(film*, int);
int check_year(int);
void new_movies(film*, int);
int get_pos_num();
char* get_str();
void get_static_str();
film add_info();
void display_info(film*, int*);
void delete_info(film*, int*, int*);
void add_index(int, int*);
int* search_by_parametr(film*, int);

int main()
{
    int n = 0;
    film *films = (film*)malloc(sizeof(film));
    if (films == NULL) ERROR
    printf(commands_list);
    while (1)
    {
        printf("\nIn the list %d films\nEnter command: ", n);
        switch (get_pos_num())
        {
            case 0: { // выход из программы
                if (n) free(films);
                return 0;
            } case 1: { // добавление
                films = (film*)realloc(films, ++n * sizeof(film));
                films[n - 1] = add_info();
                break;
            } case 2: { // удаление по параметру
                int *indexes = search_by_parametr(films, n);
                if (indexes[0])
                    delete_info(films, &n, indexes);
                else
                    printf("Not found\n");
                break;
            } case 3: { // поиск по параметру и вывод соответствий
                int *indexes = search_by_parametr(films, n);
                if (indexes[0])
                    display_info(films, indexes);
                else
                    printf("Not found\n");
                break;
            } case 4: { // вывод новейших фильмов
                new_movies(films, n);
                break;
            } case 5: { // удаление по жанру
                int *indexes = search_by_genre(films, n);
                if (indexes[0])
                    delete_info(films, &n, indexes);
                else
                    printf("Not found\n");
                break;
            } default: {
                ERROR
            }
        }
    }
}

int* search_by_genre(film *films, int n)
{
    int *indexes;
    indexes = (int*)malloc(sizeof(int));
    indexes[0] = 0;
    printf("Enter genre: ");
    char param[STR_SIZE];
    get_static_str(param);
    for (int i = 0; i < n; i++) 
        if (!check_year(films[i].year))
            if (!strcmp(films[i].genre, param))
                add_index(i, indexes);
    return indexes;
}

void new_movies(film *films, int n)
{
    int *ind = (int*)malloc(sizeof(int));
    ind[0] = 0;
    for (int i = 0; i < n; i++) if (check_year(films[i].year)) add_index(i, ind);
    
    if (ind[0] < 3) {
        printf("Not enough elements\n");
        return;
    }

    for (int t = ind[0] / 3; t; t--)
    {
        int max = ind[1 + ind[0] / 3 - t];
        for (int i = 1 + max; i <= ind[0]; i++)
        {
            printf("%d %d\n", films[ind[max]].year, films[ind[i]].year);
            if (films[ind[max]].year < films[ind[i]].year) max = i;
        }
        printf("\nDuration: %d\nName: %s\n", films[ind[max]].duration, films[ind[max]].title);
        if (check_year(films[ind[max]].year))
            printf("Year: %d\n", films[ind[max]].year);
        else
            printf("Genre: %s\n", films[ind[max]].genre);
    }

    free(ind);
}

int check_year(int a)
{
    return a > 1887 && a < 2021? 1 : 0;
}

int get_pos_num()
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

film add_info()
{
    film temp;

    printf("\nEnter the duration of the movie: ");
    temp.duration = get_pos_num();

    printf("Enter the name of the movie: ");
    temp.title = get_str();

    printf("1 - genre, 2 - year: ");
    switch (get_pos_num())
    {
        case 1: {
            printf("Enter the genre of the movie: ");
            get_static_str(temp.genre);
            return temp;
        } case 2: {
            printf("Enter the release year of the movie: ");
            temp.year = get_pos_num();
            if (!check_year(temp.year)) ERROR
            return temp;
        } default: {
            ERROR
        }
    }
}

void display_info(film *films, int *ind)
{
    for (int i = 1; i <= ind[0]; i++)
    {
        printf("\nDuration: %d\nName: %s\n", films[ind[i]].duration, films[ind[i]].title);
        if (check_year(films[ind[i]].year))
            printf("Year: %d\n", films[ind[i]].year);
        else
            printf("Genre: %s\n", films[ind[i]].genre);
    }
    free(ind);
}

void add_index(int a, int *arr)
{
    arr = (int*)realloc(arr, ++arr[0] * sizeof(int));
    arr[arr[0]] = a;
}

void delete_info(film *films, int *n, int *indexes)
{
    if (indexes[0] > 1) {
        int i = indexes[1],
            j = i + 1,
            t = 2;

        while (t <= indexes[0] && j < *n)
            if (j++ != indexes[t])
                films[i++] = films[j];
            else
                t++;
        
        *n = i;
    } else {
        *n = *n - 1;
        for (int i = indexes[1]; i < *n; i++) films[i] = films[i + 1];
    }
    films = (film*)realloc(films, *n * sizeof(film));
    free(indexes);
}

int* search_by_parametr(film *films, int n)
{
    int *indexes;
    indexes = (int*)malloc(sizeof(int));
    indexes[0] = 0;
    printf(parameteres_list);
    switch(get_pos_num())
    {
        case 1: {
            printf("Enter parameter: ");
            int param = get_pos_num();
            for (int i = 0; i < n; i++) if (films[i].duration == param) add_index(i, indexes);
            return indexes;
        } case 2: {
            printf("Enter parameter: ");
            char *param = get_str();
            for (int i = 0; i < n; i++) if (strcmp(films[i].title, param) == 0) add_index(i, indexes);
            free(param);
            return indexes;
        } case 3: {
            printf("Enter parameter: ");
            char param[STR_SIZE];
            get_static_str(param);
            for (int i = 0; i < n; i++) 
                if (!check_year(films[i].year))
                    if (!strcmp(films[i].genre, param))
                        add_index(i, indexes);
            return indexes;
        } case 4: {
            printf("Enter parameter: ");
            int param = get_pos_num();
            for (int i = 0; i < n; i++)
                if (check_year(films[i].year))
                    if (films[i].year == param)
                        add_index(i, indexes);
            return indexes;
        } default: {
            ERROR
        }
    }
}