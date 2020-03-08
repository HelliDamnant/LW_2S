#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define long_text_1 "\nDuration of the film: %d\nName of film: %s\n"
#define commands_list "Enter commands\n"

typedef struct
{
    char genre[10];
} substruct;

typedef struct
{
    int duration;
    char *title;
    substruct name_genre;
    int year;
} film;

film add_info();
void delete_info(film *films, int *n, int *indexes);
void display_info(film info);
int* search_by_parametr(film *films, int n, int type);
void add(int a, int *arr);
void read_str(char* s);

int main()
{
    // создание массива фильмов
    int n = 0;
    film *films;
    films = (film*)malloc(sizeof(film));

    printf(commands_list);

    int a, fl = 1, i = 0;
    while(fl)
    {
        printf("\nIn database %d films\nEnter command: ", n);
        scanf("%d", &a);
        fflush(stdin);
        
        switch(a)
        {
            // команда exit
            case 0: fl = 0; break;
            // команда add
            case 1:
            {
                films = (film*)realloc(films, (n + 1) * sizeof(film));
                films[n++] = add_info();
                break;
            }
            // команда delete
            case 2:
            {
                int *indexes;
                indexes = search_by_parametr(films, n, 2);

                if (indexes[0] != 0)
                    delete_info(films, &n, indexes);
                else 
                    printf("Nechego udalyat\n");

                free(indexes);
                break;
            }
            // команда вывода
            case 3:
            {
                int i;
                printf("Enter the movie number: ");
                scanf("%d", &i);

                printf(long_text_1, films[i - 1].duration, films[i - 1].title);
                printf("#########################\n");
                break;
            }
            // команда seacrh
            case 4:
            {
                int type = 1, *indexes;
                indexes = search_by_parametr(films, n, type);
                for (int i = 1; i < indexes[0]; i++) printf("tut' %d\n", indexes[i]);
            }
        }
    }

    free(films);
    return 0;
}

film add_info()
{
    film info;

    printf("\nEnter the duration of the movie: "); scanf("%d", &info.duration); getchar();

    info.title = (char*)calloc(100, sizeof(char));
    printf("Enter the name of the movie: "); fgets(info.title, 100, stdin);
    info.title = (char*)realloc(info.title, strlen(info.title) * sizeof(char));

    printf("Enter the genre of the movie: "); fgets(info.name_genre.genre, 10, stdin);
    
    printf("Enter the release year of the movie: "); scanf("%d", &info.year);

    return info;
}

void delete_info(film *films, int *n, int *indexes)
{
    int i = indexes[1], j = i + 1, t = 2;
    if (indexes[0] > 1)
    {
        for (;indexes[t] == j; j++) if (indexes[0] == t++ || j == *n) break;
        while (j < *n)
        {
            films[i++] = films[j++];
            for (;indexes[t] == j; j++) if (indexes[0] == t++ || j == *n) break;
        }
    }
    else
        for (int i = indexes[1]; i < *n - 1; i++) films[i] = films[i + 1];
    
    *n = i;
    films = (film*)realloc(films, *n * sizeof(film));
}

void add_item(int a, int *arr)
{
    arr = (int*)realloc(arr, (arr[0] + 1) * sizeof(int));
    arr[arr[0]++] = a;
}

int* search_by_parametr(film *films , int n, int type)
{
    int *indexes;
    indexes = (int*)malloc(1);
    indexes[0] = 0;

    switch(type)
    {
        case 1:
        {
            int param;
            scanf("%d", &param);
            for (int i = 0; i < n; i++) if (films[i].duration == param) add_item(i, indexes);
            break;
        }
        case 2:
        {
            char param[10];
            scanf("%s", param);
            for (int i = 0; i < n; i++) if (strcmp(films[i].title, param) == 0) add_item(i, indexes);
            break;
        }
        case 3:
        {
            char *param = (char*)malloc(255);
            fgets(param, 255, stdin);
            param = (char*)realloc(param, strlen(param) * sizeof(char));
            for (int i = 0; i < n; i++) if (strcmp(films[i].name_genre.genre, param) == 0) add_item(i, indexes);
            free(param);
            break;
        }
        case 4:
        {
            int param;
            scanf("%d", &param);
            for (int i = 0; i < n; i++) if (films[i].year == param) add_item(i, indexes);
            break;
        }
    }

    return indexes;
}