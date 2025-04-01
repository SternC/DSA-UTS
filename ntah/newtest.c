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

Movie movies[100];
int count = 0;


void loadMovies() {
    FILE *fp = fopen("movie.txt", "r");
    if (fp == NULL) {
        printf("File not found or cannot be opened!\n");
    } else {
        while (count < 100 && fscanf(fp, " %[^#]#%[^#]#%d#%[^#]#%[^\n]\n", 
                movies[count].movieName, movies[count].genre, 
                &movies[count].duration, movies[count].director, 
                movies[count].age) == 5) {
            count++;
        }
        fclose(fp);
    }
}

void saveMovies() {
    FILE *fin = fopen("movie.txt", "a");
    if (!fin) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fin, "%s#%s#%d#%s#%s\n", movies[i].movieName, movies[i].genre, 
                movies[i].duration, movies[i].director, movies[i].age);
    }
    fclose(fin);
}

void addMovie() {
    if (count >= 100) {
        printf("Movie list is full!\n");
        return;
    }
    printf("\nMovie Name   : ");
    scanf(" %[^\n]", movies[count].movieName);
    printf("Genre        : ");
    scanf(" %[^\n]", movies[count].genre);
    printf("Duration     : ");
    scanf("%d", &movies[count].duration);
    printf("Director     : ");
    scanf(" %[^\n]", movies[count].director);
    printf("Age Rating   : ");
    scanf(" %[^\n]", movies[count].age);
    count++;
    saveMovies();
    printf("\nMovie Added Successfully!\n");
}

void removeMovie() {
    if (count == 0) {
        printf("No movies to remove! Please add a movie first.\n");
        return;
    }
    char removeName[50];
    printf("\nSearch Movie Name to Remove: ");
    scanf(" %[^\n]", removeName);
    
    int found = -1;
    for (int i = 0; i < count; i++) {
        int match = 1;
        for (int j = 0; removeName[j] != '\0' || movies[i].movieName[j] != '\0'; j++) {
            if ((removeName[j] | 32) != (movies[i].movieName[j] | 32)) {
                match = 0;
                break;
            }
        }
        if (match) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("\nMovie not found!\n");
        return;
    }
    for (int i = found; i < count - 1; i++) {
        movies[i] = movies[i + 1];
    }
    count--;
    saveMovies();
    printf("\nMovie '%s' removed successfully!\n", removeName);
}

void viewMovies() {
    if (count == 0) {
        printf("Movie List is Empty! Please add a movie first.");
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    printf(" No |                  Movie Name                   |        Genre       |  Duration |       Director     |Age Rating|\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%4d|%-47s|%-20s|%-11d|%-20s|%-10s|\n",
                i+1, movies[i].movieName, movies[i].genre, 
                movies[i].duration, movies[i].director, 
                movies[i].age);
    }
}

void searchMovie() {
    if (count == 0) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }

    char searchName[50];
    printf("\nSearch Movie Name: ");
    scanf(" %[^\n]", searchName);

    int found = 0;
    for (int movie = 0; movie < count; movie++) {
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
    int choose, menu, list;
    loadMovies();

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
                    addMovie();
                } else if (menu == 2) {
                    removeMovie();
                }
            }
            printf("Thank you! We appreciate your choice.\n");
        } else if (choose == 2) {
            while (list != 3) {
                printf("\n1. View All Movies\n2. Search Movie\n3. Exit\nChoose: ");
                scanf("%d", &list);
                getchar();

                if (list == 1) {
                    viewMovies();
                } else if (list == 2) {
                    searchMovie();
                }
            }
            printf("Thank you! We appreciate your choice.\n");
        }
    }
    printf("\nThank you for using our feature. Have a good day!\n");
    return 0;
}