#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Movie {
    char movieName[50];
    char genre[50];
    char director[50];
    int duration;
    char age[10];
    struct Movie *prev, *next;
}Movie;

void loadMovies(Movie **head, Movie **tail) {
    FILE *fp = fopen("movie.txt", "r");
    if (!fp) {
        printf("Failed to open movie.txt\n");
        return;
    }

    Movie *temp;
    *head = *tail = NULL;

    while (!feof(fp)) {
        temp = (Movie *)malloc(sizeof(Movie));
        fscanf(fp, "%[^#]#%[^#]#%d#%[^#]#%[^\n]\n", temp->movieName, temp->genre, &temp->duration, temp->director, temp->age);
        temp->next = temp->prev = NULL;

        if (*head == NULL) {
            *head = temp;
            *tail = temp;
            temp->next = temp;
            temp->prev = temp;
        } else {
            temp->prev = *tail;
            (*tail)->next = temp;
            temp->next = *head;
            (*head)->prev = temp;
            *tail = temp;
        }
    }
    fclose(fp);
}


void addMovie(Movie *head, Movie **tail) {
    Movie *newMovie = (Movie *)malloc(sizeof(Movie));
    printf("\nMovie Name   : ");
    scanf(" %[^\n]", newMovie->movieName);
    printf("Genre        : ");
    scanf(" %[^\n]", newMovie->genre);
    printf("Duration     : ");
    scanf("%d", &newMovie->duration);
    printf("Director     : ");
    scanf(" %[^\n]", newMovie->director);
    printf("Age Rating   : ");
    scanf(" %[^\n]", newMovie->age);
    newMovie->next = NULL;

    if (head == NULL)
    {
        newMovie->prev = NULL;
        head = newMovie;
        *tail = newMovie;
    }
    else
    {
        newMovie->prev = *tail;
        (*tail)->next = newMovie;
        newMovie->next = head;
        *tail = newMovie;
        head->prev = *tail;
    }

    FILE *fp = fopen("movie.txt", "a");
        fprintf(fp, "\n%s#%s#%d#%s#%s\n", newMovie->movieName, newMovie->genre, newMovie->duration, newMovie->director, newMovie->age);  
    fclose(fp);
}

void removeMovie(Movie **head, Movie **tail, int *index) {
    int removeNum;
    Movie *temp = *head;
    if (*head == NULL) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }
    printf("\nInput Number Movie: ");
    scanf("%d", &removeNum);
    int currentIndex = 1;

    while (currentIndex < removeNum && temp->next != *head) {
        temp = temp->next;
        currentIndex++;
    }
    if (currentIndex != removeNum) {
        printf("Movie not found at that index!\n");
        return;
    }

    printf("Removing movie: %s\n", temp->movieName);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    if (temp == *head) {
        *head = temp->next;
    }
    if (temp == *tail) {
        *tail = temp->prev;
    }
    free(temp);

    FILE *fp = fopen("movie.txt", "w");
    if (*head != NULL && fp != NULL) {
        Movie *curr = *head;
        while (1) {
            fprintf(fp, "%s#%s#%d#%s#%s\n", curr->movieName, curr->genre, curr->duration, curr->director, curr->age);
            curr = curr->next;
            if (curr == *head) {
                break;
            }
        }
        fclose(fp);
    }
    return;
}



void viewMovies(Movie *head,int index) {
    index = 1;
    Movie *temp;
    temp = head;

    if (temp == NULL)
    {
        printf("Movie is empty\n");
        return;
    }

    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    printf(" No |                  Movie Name                   |        Genre       |  Duration |       Director     |Age Rating|\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    while (temp->next != head) {
        printf("%4d|%-47s|%-20s|%-4d%7s|%-20s|%-10s|\n",
                index++, temp->movieName, temp->genre, 
                temp->duration,"minutes", temp->director, 
                temp->age);
        temp = temp->next;
    }
}

void searchMovie(Movie *head) {
    char searchName[50];
    Movie *temp = head;
    if (temp == NULL) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }
    printf("\nSearch Movie Name: ");
    scanf(" %[^\n]", searchName);

    int found = 0;
    while (temp->next != head) {
        for (int find = 0; searchName[find] != '\0' || temp->movieName[find] != '\0'; find++) {
            if (searchName[find] >= 'a' && searchName[find] <= 'z') {
                searchName[find] -= 32;
            }
            if (searchName[find] != temp->movieName[find]) {
                found = 0;
                break;
            } else {
                found = 1;
            }
        }
        if (found == 1) {
            printf("\nMovie Found!\n");
            printf("------------------------------\n");
            printf("Movie Name  : %s\n", temp->movieName);
            printf("Genre       : %s\n", temp->genre);
            printf("Duration    : %d minutes\n", temp->duration);
            printf("Director    : %s\n", temp->director);
            printf("Age Rating  : %s\n", temp->age);
            printf("------------------------------\n");
            break;
        }
        else{
            temp = temp->next;
        }
    }
        printf("\nMovie is not found!\n");
}

void deleteNodes(Movie *head){
    if(head == NULL){
        return;
    }

    Movie *ptr = head->next;
    while (ptr != head){
        Movie *trash = ptr;
        ptr = ptr->next;
        free(trash);
    }
    free(head);
}

int main() {
    Movie *head, *tail;
    head = tail = NULL;
    int choose, menu, list, index;
    loadMovies(&head, &tail);

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
                    addMovie(head, &tail);
                } else if (menu == 2) {
                    viewMovies(head, index);
                    removeMovie(&head, &tail, &index);
                }
            }
            deleteNodes(head);
            printf("Thank you! We appreciate your choice.\n");
        } else if (choose == 2) {
            while (list != 3) {
                printf("\n1. View All Movies\n2. Search Movie\n3. Exit\nChoose: ");
                scanf("%d", &list);
                getchar();

                if (list == 1) {
                    viewMovies(head, index);
                } else if (list == 2) {
                    searchMovie(head);
                }
            }
            deleteNodes(head);
            printf("Thank you! We appreciate your choice.\n");
        }
    }
    deleteNodes(head);
    printf("\nThank you for using our feature. Have a good day!\n");
    return 0;
}