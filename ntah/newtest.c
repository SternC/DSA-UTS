#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char movieName[50];
    char genre[50];
    char director[50];
    int duration;
    char age[10];
} Movie;

void loadMovies(Movie movies[], int *count) {
    FILE *fp = fopen("movie.txt", "r");
    if (fp == NULL) {
        printf("File not found or cannot be opened!\n");
    } else {
        while (*count < 100 && fscanf(fp, " %[^#]#%[^#]#%d#%[^#]#%[^\n]\n", 
                movies[*count].movieName, movies[*count].genre, 
                &movies[*count].duration, movies[*count].director, 
                movies[*count].age) == 5) {
                (*count)++;
        }
        fclose(fp);
    }
}

void saveMovies(Movie movies[], int *count) {
    FILE *fin = fopen("movie.txt", "w");
    if (!fin) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < *count; i++) {
        fprintf(fin, "%s#%s#%d#%s#%s\n", movies[i].movieName, movies[i].genre, 
                movies[i].duration, movies[i].director, movies[i].age);
    }
    fclose(fin);
}

void addMovie(Movie movies[], int *count) {
    if (*count >= 100) {
        printf("Movie list is full!\n");
        return;
    }
    printf("\nMovie Name   : ");
    scanf(" %[^\n]", movies[*count].movieName);
    getchar();
    printf("Genre        : ");
    scanf(" %[^\n]", movies[*count].genre);
    printf("Duration     : ");
    scanf("%d", &movies[*count].duration);
    printf("Director     : ");
    scanf(" %[^\n]", movies[*count].director);
    printf("Age Rating   : ");
    scanf(" %[^\n]", movies[*count].age);
    (*count)++;
    saveMovies(movies, count);
    printf("\nMovie Added Successfully!\n");
}

void removeMovie(Movie movies[], int *count) {
    if (*count == 0) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }

    int removeNum;
    printf("\nInput Movie Number to Remove: ");
    scanf("%d", &removeNum);

    if (removeNum < 1 || removeNum > *count) {
        printf("Invalid movie number!\n");
        return;
    }

    printf("Removing movie: %s\n", movies[removeNum - 1].movieName);

    for (int i = removeNum - 1; i < *count - 1; i++) {
        movies[i] = movies[i + 1];
    }
    (*count)--;
    saveMovies(movies, count);
    printf("Movie removed successfully!\n");
}

void viewMovies(Movie movies[], int *count) {
    if (count == 0) {
        printf("Movie List is Empty! Please add a movie first.");
        return;
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    printf(" No |                  Movie Name                   |        Genre       |  Duration |       Director     |Age Rating|\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < *count; i++) {
        printf("%4d|%-47s|%-20s|%-4d%7s|%-20s|%-10s|\n",
                i+1, movies[i].movieName, movies[i].genre, 
                movies[i].duration,"minutes", movies[i].director, 
                movies[i].age);
    }
}

void searchMovie(Movie movies[], int *count) {
    if (*count == 0) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }

    char searchName[50];
    printf("\nSearch Movie Name: ");
    scanf(" %[^\n]", searchName);

    int found = 0;
    for (int movie = 0; movie < *count; movie++) {
        int match = 1;
        for (int find = 0; searchName[find] != '\0' || movies[movie].movieName[find] != '\0'; find++) {
            if (searchName[find] >= 'a' && searchName[find] <= 'z') {
                searchName[find] -= 32;
            }
            if (movies[movie].movieName[find] >= 'a' && movies[movie].movieName[find] <= 'z') {
                movies[movie].movieName[find] -= 32;
            }
            
            if (searchName[find] != movies[movie].movieName[find]) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("\nMovie Found!\n");
            printf("------------------------------\n");
            printf("Movie Name  : %s\n", movies[movie].movieName);
            printf("Genre       : %s\n", movies[movie].genre);
            printf("Duration    : %d minutes\n", movies[movie].duration);
            printf("Director    : %s\n", movies[movie].director);
            printf("Age Rating  : %s\n", movies[movie].age);
            printf("------------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("\nMovie is not found!\n");
    }
}

int main() {
    Movie movies[100];
    int count = 0;
    int choose, menu, list;
    loadMovies(movies, &count);

    while (choose != 1 && choose != 2) {
        printf("\nOwner (1) or User (2): ");
        scanf("%d", &choose);
        getchar();

        if (choose == 1) {
            while (menu != 3) {
                printf("\n1. Add Movie\n2. Remove Movie\n3. Exit\nChoose: ");
                scanf("%d", &menu);
                getchar();

                if (menu == 1) {
                    addMovie(movies, &count);
                } else if (menu == 2) {
                    viewMovies(movies, &count);
                    removeMovie(movies, &count);
                }
            }
            printf("Thank you! We appreciate your choice.\n");
        } else if (choose == 2) {
            while (list != 3) {
                printf("\n1. View All Movies\n2. Search Movie\n3. Exit\nChoose: ");
                scanf("%d", &list);
                getchar();

                if (list == 1) {
                    viewMovies(movies, &count);
                } else if (list == 2) {
                    searchMovie(movies, &count);
                }
            }
            printf("Thank you! We appreciate your choice.\n");
        }
    }
    printf("\nThank you for using our feature. Have a good day!\n");
    return 0;
}