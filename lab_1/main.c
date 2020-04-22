#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define long_text_1 "\nDuration of the film: %d\nName of film: %s\n"
#define long_text_2 "Enter:\n1 to search by duration.\n2 to search by name.\n3 to search by genre.\n4 to search by year of release.\nType: "
#define commands_list "Enter:\n0 to end the program execution\n1 to add an element to the array\n2 to delete movies from the array using the specified parameter\n3 to delete movies that are longer than the specified duration\n4 to find movies by parameter\n"

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

int get_command();
film add_info();
void delete_info(film *films, int *n, int *indexes);
void add_item(int a, int *arr);
int get_type();
int* search_by_parametr(film *films, int n);

int main()
{
    // создание массива фильмов
    int n = 0;
    film *films = NULL;
    films = (film*)malloc(sizeof(film));
    if (films == NULL)
    {
        printf("Error!\n");
        exit(1);
    }

    // вывод списка команд
    printf(commands_list);
    
    while(1)
    {
        printf("\nIn the list %d films\nEnter command: ", n);
        switch(get_command())
        {
            case 0: {
                free(films);
                return 0;
            }
            case 1: {
                films = (film*)realloc(films, (n + 1) * sizeof(film));
                films[n++] = add_info();
                break;
            }
            case 2: {
                int *indexes;

                indexes = search_by_parametr(films, n);

                if (indexes[0] != 0)
                    delete_info(films, &n, indexes);
                else
                    printf("Nechego udalyat\n");

                free(indexes);
                break;
            }
            case 3: {
                int *indexes, param;
                indexes = (int*)malloc(1);
                indexes[0] = 0;
                scanf("%d", &param);
                
                for (int i = 0; i < n; i++) if (films[i].duration > param) add_item(i, indexes);
                
                if (indexes[0] != 0)
                    delete_info(films, &n, indexes);
                else
                    printf("Nechego udalyat\n");
                
                free(indexes);
                break;
            }
            case 5: {
                int *indexes;
                indexes = search_by_parametr(films, n);

                printf("Movies found on request: ");
                for (int i = 1; i != indexes[0]; i++) printf("%d. %s\n", i , films[indexes[i]].title);

                free(indexes);
            }
        }
    }
}

int get_command()
{
    int a;
    while (scanf("%d", &a) == 0 || a < 0 || a > 5)
    {
        printf("Incorrect! Repeat input.\n");
        fflush(stdin);
    }
    getchar();
    return a;
}

film add_info()
{
    film info;

    printf("\nEnter the duration of the movie: ");
    scanf("%d", &info.duration);
    getchar();

    info.title = (char*)calloc(100, sizeof(char));
    printf("Enter the name of the movie: ");
    fgets(info.title, 100, stdin);
    info.title[strlen(info.title) - 1] = 0;
    info.title = (char*)realloc(info.title, strlen(info.title) * sizeof(char));

    printf("Enter the genre of the movie: ");
    fgets(info.name_genre.genre, 10, stdin);
    info.name_genre.genre[strlen(info.name_genre.genre) - 1] = 0;
    
    printf("Enter the release year of the movie: ");
    scanf("%d", &info.year);

    return info;
}

void delete_info(film *films, int *n, int *indexes)
{
    if (indexes[0] > 1)
    {
        int i = indexes[1],
            j = i + 1,
            t = 2;

        while (t <= indexes[0] && j < *n)
            if (j++ != indexes[t])
                films[i++] = films[j];
            else
                t++;
        
        *n = i;
    }
    else
    {
        *n = *n - 1;
        for (int i = indexes[1]; i < *n; i++) films[i] = films[i + 1];
    }

    films = (film*)realloc(films, *n * sizeof(film));
}

int* search_by_parametr(film *films, int n)
{
    int *indexes;
    indexes = (int*)malloc(1);
    indexes[0] = 0;

    switch(get_type())
    {
        case 1:
        {
            printf("Enter parameter: ");
            int param;
            scanf("%d", &param);

            for (int i = 0; i < n; i++) if (films[i].duration == param) add_item(i, indexes);
            
            return indexes;
        }
        case 2:
        {
            printf("Enter parameter: ");
            char *param = (char*)calloc(100, sizeof(char));
            fgets(param, 100, stdin);
            param[strlen(param) - 1] = 0;
            param = (char*)realloc(param, strlen(param) * sizeof(char));

            for (int i = 0; i < n; i++) if (strcmp(films[i].title, param) == 0) add_item(i, indexes);

            free(param);
            return indexes;
        }
        case 3:
        {
            printf("Enter parameter: ");
            char param[10];
            fgets(param, 10, stdin);
            param[strlen(param) - 1] = 0;

            for (int i = 0; i < n; i++) if (strcmp(films[i].name_genre.genre, param) == 0) add_item(i, indexes);

            return indexes;
        }
        case 4:
        {
            printf("Enter parameter: ");
            int param;
            scanf("%d", &param);
            for (int i = 0; i < n; i++) if (films[i].year == param) add_item(i, indexes);
            return indexes;
        }
    }
}

void add_item(int a, int *arr)
{
    arr = (int*)realloc(arr, ++arr[0] * sizeof(int));
    arr[arr[0]] = a;
}

int get_type()
{
    printf(long_text_2);
    int a;
    while (scanf("%d", &a) == 0 || a < 1 || a > 4)
    {
        printf("Incorrect! Repeat input.\n");
        fflush(stdin);
    }
    getchar();
    return a;
}