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

void deleteNodes(Movie **tail, Movie *head)
{
    Movie *trash = *tail;
    while (trash != NULL)
    {
        *tail = trash->prev;
        head->prev = *tail;
        trash->prev = trash->next = NULL;
        free(trash);
        trash = *tail;
    }
}