#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct cinemaProvince
{
    char province[50];
    int code;
    struct cinemaProvince *prev, *next;
}cinProv;

typedef struct cinemaLocation
{
    char cinema[50];
    int code;
    int num;
    struct cinemaLocation *prev, *next;
}cinLoc;

typedef struct Movie {
    char movieName[50];
    char genre[50];
    char director[50];
    int duration;
    char age[10];
    struct Movie *prev, *next;
}Movie;

struct food{
    char name[50];
    int stock;
    int price;
    struct food *next;
};

struct beverage{
    char name[50];
    int stock;
    int price;
    struct beverage *next;
};

struct item {
    struct food buyFood;
    struct beverage buyDrink;
    int fQuantity;
    int bQuantity;
    int fPrice;
    int bPrice;
    struct item *next;
};

struct cart {
    struct item *items;
    int cartTop;
};

void deleteLocationNodes(cinLoc **cin_head, cinLoc **cin_tail)
{
    cinLoc *tempNode, *tempNextNode;

    tempNode = *cin_head;

    while (tempNode != NULL)
    {
        tempNextNode = tempNode->next;

        if (tempNode == *cin_tail)
        {
            free(tempNode);
            break;
        }

        free(tempNode);
        tempNode = tempNextNode;
    }

    *cin_head = NULL;
    *cin_tail = NULL;
}

void deleteProvinceNodes(cinProv **cin_front, cinProv **cin_back)
{
    cinProv *tempNode, *tempNextNode;

    tempNode = *cin_front;

    while (tempNode != NULL)
    {
        tempNextNode = tempNode->next;

        if (tempNode == *cin_back)
        {
            free(tempNode);
            break;
        }

        free(tempNode);
        tempNode = tempNextNode;
    }

    *cin_front = NULL;
    *cin_back = NULL;
}

void addCinemaLocationAndNewProvince(int counterProv)
{
    char newProvince[51], newLocation[51];

    FILE *cinProvFile = fopen("cinema_province.txt", "a");
    FILE *cinLocFile = fopen("cinema_location.txt", "a");

    printf("Please Use Uppercase To Input!\n");
    printf("Input New Province: ");
    scanf(" %[^\n]", newProvince);
    fprintf(cinProvFile, "%s#%d\n", newProvince, counterProv + 1);

    printf("Input New Location: ");
    scanf(" %[^\n]", newLocation);
    fprintf(cinLocFile, "%s#%d#1\n", newLocation, counterProv + 1);
    printf("\n");

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void addCinemaLocationFromExistingProvince(cinLoc **cin_head)
{
    cinLoc *tempLoc;
    int provinceCode;
    char newLocation[51];
    int newNum = 0;

    tempLoc = *cin_head;

    FILE *cinProvFile = fopen("cinema_province.txt", "r");
    FILE *cinLocFile = fopen("cinema_location.txt", "a+");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%d", &provinceCode);
    printf("\n");

    while (1)
    {
        if (tempLoc->code == provinceCode)
        {
            newNum++;
        }
        tempLoc = tempLoc->next;
        if (tempLoc == *cin_head)
        {
            break;
        }
    }

    printf("Please Use Uppercase To Input!\n");
    printf("Input New Location: ");
    scanf(" %[^\n]", newLocation);
    fprintf(cinLocFile, "\n%s#%d#%d", newLocation, provinceCode, newNum + 1);
    printf("\n");

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void deleteCinemaLocation(cinLoc **cin_head, cinLoc **cin_tail, int *counterLoc)
{
    int provinceCode, cinemaNum;
    cinLoc *tempLoc = *cin_head;

    FILE *cinProvFile = fopen("cinema_province.txt", "r");
    FILE *cinLocFile = fopen("cinema_location.txt", "w");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%d", &provinceCode);
    printf("\n");

    for (int i = 0; i < *counterLoc; i++)
    {
        if (tempLoc->code == provinceCode)
        {
            printf("%d. %s\n", tempLoc->num, tempLoc->cinema);
        }
        tempLoc = tempLoc->next;
    }

    printf("Choose Unwanted Cinema: ");
    scanf("%d", &cinemaNum);
    printf("\n");

    while (provinceCode != tempLoc->code || cinemaNum != tempLoc->num)
    {
        tempLoc = tempLoc->next;
    }

    if (tempLoc == *cin_head)
    {
        *cin_head = tempLoc->next;
        (*cin_head)->prev = *cin_tail;
    }
    else if (tempLoc == *cin_tail)
    {
        *cin_tail = tempLoc->prev;
        (*cin_tail)->next = *cin_head;
    }
    else
    {
        tempLoc->prev->next = tempLoc->next;
        tempLoc->next->prev = tempLoc->prev;
    }
    free(tempLoc);
    (*counterLoc)--;

    tempLoc = *cin_head;
    for (int i = 0; i < *counterLoc; i++)
    {
        fprintf(cinLocFile, "%s#%d#%d\n", tempLoc->cinema, tempLoc->code, tempLoc->num);
        tempLoc = tempLoc->next;
    }

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void deleteCinemaProvinceAndLocation(cinLoc **cin_head, cinLoc **cin_tail, cinProv **cin_front, cinProv **cin_back, int *counterLoc, int *counterProv)
{
    cinLoc *tempLoc = *cin_head;
    cinProv *tempProv = *cin_front;
    int provinceCode, counterCode = 0;

    FILE *cinProvFile = fopen("cinema_province.txt", "w");
    FILE *cinLocFile = fopen("cinema_location.txt", "w");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%d", &provinceCode);
    printf("\n");

    while (provinceCode != tempProv->code)
    {
        tempProv = tempProv->next;
    }

    if (tempProv == *cin_front)
    {
        *cin_front = (*cin_front)->next;
        (*cin_back)->next = *cin_front;
        (*cin_front)->prev = *cin_back;
    }
    else if (tempProv == *cin_back)
    {
        *cin_back = (*cin_back)->prev;
        (*cin_front)->prev = *cin_back;
        (*cin_back)->next = *cin_front;
    }
    else
    {
        tempProv->next->prev = tempProv->prev;
        tempProv->prev->next = tempProv->next;
    }
    free(tempProv);
    (*counterProv)--;

    tempProv = *cin_front;
    for (int i = 0; i < *counterProv; i++)
    {
        fprintf(cinProvFile, "%s#%d\n", tempProv->province, tempProv->code);
        tempProv = tempProv->next;
    }

    fclose(cinProvFile);

    while (1)
    {
        if (tempLoc->code == provinceCode)
        {
            counterCode++;
        }
        tempLoc = tempLoc->next;
        if (tempLoc == *cin_head)
        {
            break;
        }
    }

    for (int i = 0; i < counterCode; i++)
    {
        while (tempLoc->code != provinceCode)
        {
            tempLoc = tempLoc->next;
        }

        if (tempLoc == *cin_head)
        {
            *cin_head = (*cin_head)->next;
            (*cin_tail)->next = *cin_head;
            (*cin_head)->prev = *cin_tail;
        }
        else if (tempLoc == *cin_tail)
        {
            *cin_tail = (*cin_tail)->prev;
            (*cin_head)->prev = *cin_tail;
            (*cin_tail)->next = *cin_head;
        }
        else
        {
            tempLoc->next->prev = tempLoc->prev;
            tempLoc->prev->next = tempLoc->next;
        }
        free(tempLoc);
        (*counterLoc)--;

        tempLoc = tempLoc->next;
    }

    tempLoc = *cin_head;
    for (int i = 0; i < *counterLoc; i++)
    {
        fprintf(cinLocFile, "%s#%d#%d\n", tempLoc->cinema, tempLoc->code, tempLoc->num);
        tempLoc = tempLoc->next;
    }

    fclose(cinLocFile);
}

void chooseCinema(cinLoc **cin_head, cinLoc **cin_tail, cinProv **cin_front, cinProv **cin_back, char *province, char *location)
{
    cinProv *nodeProv, *tempProv;
    cinLoc *nodeLoc, *tempLoc;
    int userProv, userCinema;
    int counterProv, counterLoc;

    counterLoc = counterProv = 0;

    FILE *cinProvFile = fopen("cinema_province.txt", "r");
    FILE *cinLocFile = fopen("cinema_location.txt", "r");

    while (!feof(cinProvFile))
    {
        nodeProv = (cinProv *)malloc(sizeof(cinProv));
        fscanf(cinProvFile, " %[^#]#%d\n", nodeProv->province, &nodeProv->code);

        if (*cin_front == NULL)
        {
            *cin_front = *cin_back = nodeProv;
        }
        else
        {
            nodeProv->prev = *cin_back;
            (*cin_back)->next = nodeProv;
            *cin_back = nodeProv;
        }
        (*cin_back)->next = *cin_front;
        (*cin_front)->prev = *cin_back;
        counterProv++;
    }

    while (!feof(cinLocFile))
    {
        nodeLoc = (cinLoc *)malloc(sizeof(cinLoc));
        fscanf(cinLocFile, " %[^#]#%d#%d\n", nodeLoc->cinema, &nodeLoc->code, &nodeLoc->num);

        if (*cin_head == NULL)
        {
            *cin_head = *cin_tail = nodeLoc;
        }
        else
        {
            nodeLoc->prev = *cin_tail;
            (*cin_tail)->next = nodeLoc;
            *cin_tail = nodeLoc;
        }
        (*cin_tail)->next = *cin_head;
        (*cin_head)->prev = *(cin_tail);
        counterLoc++;
    }

    fclose(cinProvFile);
    fclose(cinLocFile);

    tempProv = *cin_front;
    tempLoc = *cin_head;

    for (int i = 0; i < counterProv; i++)
    {
        printf("%d. %s\n", i + 1, tempProv->province);
        tempProv = tempProv->next;
    }

    printf("\nPlease Input The Code!\n");
    printf("Choose Your Province: ");
    scanf("%d", &userProv);
    printf("\n");
    strcpy(province, tempProv->province);
    for (int i = 0; i < counterLoc; i++)
    {
        if (tempLoc->code == userProv)
        {
            printf("%d. %s\n", i + 1, tempLoc->cinema);
        }
        tempLoc = tempLoc->next;
    }

    printf("\nPlease Input The Code!\n");
    printf("Choose Your Cinema: ");
    scanf("%d", &userCinema);
    printf("\n");

    tempLoc = *cin_head;
    while (tempLoc->code != userProv || tempLoc->num != userCinema)
    {
        tempLoc = tempLoc->next;
    }

    strcpy(location, tempLoc->cinema);
}

void owner(cinLoc **cin_head, cinLoc **cin_tail, cinProv **cin_front, cinProv **cin_back)
{
    cinProv *nodeProv, *tempProv;
    cinLoc *nodeLoc, *tempLoc;
    int userCity, userCinema;
    int counterProv, counterLoc;
    int userActivity;

    while (1)
    {
        counterLoc = counterProv = 0;

        FILE *cinProvFile = fopen("cinema_province.txt", "r");
        FILE *cinLocFile = fopen("cinema_location.txt", "r");

        while (!feof(cinProvFile))
        {
            nodeProv = (cinProv *)malloc(sizeof(cinProv));
            fscanf(cinProvFile, " %[^#]#%d\n", nodeProv->province, &nodeProv->code);

            if (*cin_front == NULL)
            {
                *cin_front = *cin_back = nodeProv;
            }
            else
            {
                nodeProv->prev = *cin_back;
                (*cin_back)->next = nodeProv;
                *cin_back = nodeProv;
            }
            (*cin_back)->next = *cin_front;
            (*cin_front)->prev = *cin_back;
            counterProv++;
        }

        while (!feof(cinLocFile))
        {
            nodeLoc = (cinLoc *)malloc(sizeof(cinLoc));
            fscanf(cinLocFile, " %[^#]#%d#%d\n", nodeLoc->cinema, &nodeLoc->code, &nodeLoc->num);

            if (*cin_head == NULL)
            {
                *cin_head = *cin_tail = nodeLoc;
            }
            else
            {
                nodeLoc->prev = *cin_tail;
                (*cin_tail)->next = nodeLoc;
                *cin_tail = nodeLoc;
            }
            (*cin_tail)->next = *cin_head;
            (*cin_head)->prev = *(cin_tail);
            counterLoc++;
        }

        fclose(cinLocFile);
        fclose(cinProvFile);

        printf("1. Add New Cinema's Location and New Province\n");
        printf("2. Add New Cinema's Location From Existing Province\n");
        printf("3. Delete Cinema's Location From a Province\n");
        printf("4. Delete Cinema's Province\n");
        printf("5. Exit Owner Mode\n");
        printf("What Do You Want To Do? ");
        scanf("%d", &userActivity);
        printf("\n");

        switch (userActivity)
        {
        case 1:
            addCinemaLocationAndNewProvince(counterProv);
            break;

        case 2:
            tempProv = *cin_front;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%d\n", i + 1, tempProv->province, tempProv->code);
                tempProv = tempProv->next;
            }
            addCinemaLocationFromExistingProvince(cin_head);
            break;

        case 3:
            tempProv = *cin_front;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%d\n", i + 1, tempProv->province, tempProv->code);
                tempProv = tempProv->next;
            }
            deleteCinemaLocation(cin_head, cin_tail, &counterLoc);
            break;

        case 4:
            tempProv = *cin_front;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%d\n", i + 1, tempProv->province, tempProv->code);
                tempProv = tempProv->next;
            }
            deleteCinemaProvinceAndLocation(cin_head, cin_tail, cin_front, cin_back, &counterLoc, &counterProv);
            break;

        default:
            return;
        }
    }
}

void loadMovies(Movie **mov_head, Movie **mov_tail) {
    FILE *fp = fopen("movie.txt", "r");
    if (!fp) {
        printf("Failed to open movie.txt\n");
        return;
    }

    Movie *temp;
    *mov_head = *mov_tail = NULL;

    while (!feof(fp)) {
        temp = (Movie *)malloc(sizeof(Movie));
        fscanf(fp, "%[^#]#%[^#]#%d#%[^#]#%[^\n]\n", temp->movieName, temp->genre, &temp->duration, temp->director, temp->age);
        temp->next = temp->prev = NULL;

        if (*mov_head == NULL) {
            *mov_head = temp;
            *mov_tail = temp;
            temp->next = temp;
            temp->prev = temp;
        } else {
            temp->prev = *mov_tail;
            (*mov_tail)->next = temp;
            temp->next = *mov_head;
            (*mov_head)->prev = temp;
            *mov_tail = temp;
        }
    }
    fclose(fp);
}


void addMovie(Movie *mov_head, Movie **mov_tail) {
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

    if (mov_head == NULL)
    {
        newMovie->prev = NULL;
        mov_head = newMovie;
        *mov_tail = newMovie;
    }
    else
    {
        newMovie->prev = *mov_tail;
        (*mov_tail)->next = newMovie;
        newMovie->next = mov_head;
        *mov_tail = newMovie;
        mov_head->prev = *mov_tail;
    }

    FILE *fp = fopen("movie.txt", "a");
        fprintf(fp, "\n%s#%s#%d#%s#%s\n", newMovie->movieName, newMovie->genre, newMovie->duration, newMovie->director, newMovie->age);  
    fclose(fp);
}

void removeMovie(Movie **mov_head, Movie **mov_tail, int *index) {
    int removeNum;
    Movie *temp = *mov_head;
    if (*mov_head == NULL) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }
    printf("\nInput Number Movie: ");
    scanf("%d", &removeNum);
    int currentIndex = 1;

    while (currentIndex < removeNum && temp->next != *mov_head) {
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
    if (temp == *mov_head) {
        *mov_head = temp->next;
    }
    if (temp == *mov_tail) {
        *mov_tail = temp->prev;
    }
    free(temp);

    FILE *fp = fopen("movie.txt", "w");
    if (*mov_head != NULL && fp != NULL) {
        Movie *curr = *mov_head;
        while (1) {
            fprintf(fp, "%s#%s#%d#%s#%s\n", curr->movieName, curr->genre, curr->duration, curr->director, curr->age);
            curr = curr->next;
            if (curr == *mov_head) {
                break;
            }
        }
        fclose(fp);
    }
    return;
}



void viewMovies(Movie *mov_head,int index) {
    index = 1;
    Movie *temp;
    temp = mov_head;

    if (temp == NULL)
    {
        printf("Movie is empty\n");
        return;
    }

    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    printf(" No |                  Movie Name                   |        Genre       |  Duration |       Director     |Age Rating|\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    if(temp != NULL){
        while(temp != NULL){
            printf("%4d|%-47s|%-20s|%-4d%7s|%-20s|%-10s|\n", index++, temp->movieName, temp->genre, temp->duration, "minutes",  temp->director, temp->age);
    
            temp = temp->next;
    
            if(temp == mov_head){
                break;
            }
        }
    }
}

void searchMovie(Movie *mov_head) {
    char searchName[50];
    Movie *temp = mov_head;
    if (temp == NULL) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }
    printf("\nSearch Movie Name: ");
    scanf(" %[^\n]", searchName);

    int found = 0;
    do {
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
            return;
        }
        temp = temp->next;
    } while (temp != mov_head);

    printf("\nMovie is not found!\n");
}

void deleteNodes(Movie *mov_head){
    if(mov_head == NULL){
        return;
    }

    Movie *ptr = mov_head->next;
    while (ptr != mov_head){
        Movie *trash = ptr;
        ptr = ptr->next;
        free(trash);
    }
    free(mov_head);
}

void selectMovie(Movie *mov_head, Movie **mov_tail, char *selectedMovie) {
    int movieNum;
    Movie *temp = mov_head;
    if (temp == NULL) {
        printf("Movie List is Empty! Please add a movie first.\n");
        return;
    }
    printf("\nInput Number Movie: ");
    scanf("%d", &movieNum);
    int currentIndex = 1;

    while (currentIndex < movieNum && temp->next != mov_head) {
        temp = temp->next;
        currentIndex++;
    }
    if (currentIndex != movieNum) {
        printf("Movie not found at that index!\n");
        return;
    }

    strcpy(selectedMovie, temp->movieName);
    printf("You have selected: %s\n\n\n", temp->movieName);
}

void ownerMovie(Movie **mov_head, Movie **mov_tail) {
    int menu = 0, index = 0;

    while (menu != 3) {
        printf("\n1. Add Movie\n2. Remove Movie\n3. Exit\nChoose: ");
        scanf(" %d", &menu);

        if (menu == 1) {
            addMovie(*mov_head, mov_tail);
        } else if (menu == 2) {
            viewMovies(*mov_head, index);
            removeMovie(mov_head, mov_tail, &index);
        }
    }
}

void userMovie(Movie **mov_head, Movie **mov_tail, char *selectedMovie){
    int menu = 0, index = 0;

    while (menu != 3) {
        printf("\n1. View Movie\n2. Search Movie\n3. Select Movie\n4.Exit\nChoose: ");
        scanf(" %d", &menu);

        if (menu == 1) {
            viewMovies(*mov_head, index);
        } else if (menu == 2) {
            searchMovie(*mov_head);
        } else if (menu == 3) {
            viewMovies(*mov_head, index);
            selectMovie(*mov_head, mov_tail, selectedMovie);
        } else if (menu == 4) {
            printf("Thank you! We appreciate your choice.\n");
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }
}

// OWNER FOOD FUNCTION

void addfood(struct food **food_head, int n) {
    int choice;
    FILE *pick = NULL;
    printf("Category:\n");
    printf("1. Popcorn\n");
    printf("2. Fritters\n");
    printf("3. Light meal\n");
    printf("4. Bakery\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            pick = fopen("popcorn.txt", "a");
            break;
        case 2:
            pick = fopen("fritters.txt", "a");
            break;
        case 3:
            pick = fopen("lightmeal.txt", "a");
            break;
        case 4:
            pick = fopen("bakery.txt", "a");
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    if (pick == NULL) {
        printf("Error.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        struct food *new_food = (struct food*)malloc(sizeof(struct food));
        printf("Name: ");
        scanf("%49s", new_food->name);
        getchar(); 
        printf("Stock: ");
        scanf("%d", &new_food->stock);
        getchar();
        printf("Price: ");
        scanf("%d", &new_food->price);
        getchar(); 
        
        new_food->next = *food_head;
        *food_head = new_food;
        
        fprintf(pick, "%s#%d#%d\n", new_food->name, new_food->stock, new_food->price);
    }
    fclose(pick);
}

void addbev(struct beverage **drink_head, int n) {
    FILE *beverage = fopen("beverage.txt", "a");
    if (beverage == NULL) {
        printf("Error.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        struct beverage *new_drink = (struct beverage*)malloc(sizeof(struct beverage));
        printf("Drink: ");
        scanf("%49s", new_drink->name);
        getchar(); 
        printf("Quantity: ");
        scanf("%d", &new_drink->stock);
        getchar(); 
        printf("Price: ");
        scanf("%d", &new_drink->price);
        getchar(); 
        
        new_drink->next = *drink_head;
        *drink_head = new_drink;
        
        fprintf(beverage, "%s#%d#%d\n", new_drink->name, new_drink->stock, new_drink->price);
    }
    fclose(beverage);
}

void checkInventory(struct food *food_head, struct beverage *drink_head) {
    char merk[100];
    int choice;
    printf("Choice:\n");
    printf("1. Food\n");
    printf("2. Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar(); 

    if (choice == 1) {
        FILE *pick = NULL;
        printf("Category:\n");
        printf("1. Popcorn\n");
        printf("2. Fritters\n");
        printf("3. Light meal\n");
        printf("4. Bakery\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); 

        char *file = NULL;
        switch (choice) {
            case 1: 
                file = "popcorn.txt"; 
                break;
            case 2: 
                file = "fritters.txt"; 
                break;
            case 3: 
                file = "lightmeal.txt"; 
                break;
            case 4: 
                file = "bakery.txt"; 
                break;
            default: 
                printf("Invalid choice.\n"); 
                return;
        }

        pick = fopen(file, "r");
        if (!pick) {
            printf("Error: Could not open %s.\n", file);
            return;
        }

        struct food *head = NULL;
        while (!feof(pick)) {
            struct food *food = (struct food *)malloc(sizeof(struct food));
            if (fscanf(pick, "%[^#]#%d#%d\n", food->name, &food->stock, &food->price) == 3) {
                food->next = head;
                head = food;
            } 
        }
        fclose(pick);

        printf("Enter food name : ");
        scanf("%49s", merk);
        getchar();

        struct food *temp = head;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->name, merk) == 0) {
                printf("================================\n");
                printf("Food    : %s\n", temp->name);
                printf("Stock   : %d\n", temp->stock);
                printf("Price   : %d\n", temp->price);
                printf("================================\n");
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Item not found in %s.\n", file);
        }

         } else if (choice == 2) {
        FILE *beverage_file = fopen("beverage.txt", "r");
        if (!beverage_file) {
            printf("Error: Could not open beverage.txt.\n");
            return;
        }

        struct beverage *head = NULL;
        while (!feof(beverage_file)) {
            struct beverage *beverage = (struct beverage *)malloc(sizeof(struct beverage));
            if (fscanf(beverage_file, "%[^#]#%d#%d\n", beverage->name, &beverage->stock, &beverage->price) == 3) {
                beverage->next = head;
                head = beverage;
            } 
        }
        fclose(beverage_file);

        printf("Enter beverage name to search: ");
        scanf("%49s", merk);
        getchar(); 

        struct beverage *temp = head;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->name, merk) == 0) {
                printf("================================\n");
                printf("Beverage: %s\n", temp->name);
                printf("Stock   : %d\n", temp->stock);
                printf("Price   : %d\n", temp->price);
                printf("================================\n");
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Item not found in beverage.txt.\n");
        }
    }
    }
    

void changePriceStock(struct food *food_head, struct beverage *drink_head, int n) {
    int newprice, newstock, choice;
    char merk[100];
    printf("Choice:\n");
    printf("1. Food\n");
    printf("2. Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar(); 

    if (choice == 1) {
        FILE *pick = NULL;
        printf("Category:\n");
        printf("1. Popcorn\n");
        printf("2. Fritters\n");
        printf("3. Light meal\n");
        printf("4. Bakery\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); 

        char *file = NULL;
        switch (choice) {
            case 1: 
            file = "popcorn.txt"; 
            break;
            case 2: 
            file = "fritters.txt"; 
            break;
            case 3: 
            file = "lightmeal.txt"; 
            break;
            case 4: 
            file = "bakery.txt"; 
            break;
            default: 
            printf("Invalid choice.\n"); 
            return;
        }

        printf("Name: ");
        scanf("%49s", merk);
        getchar(); 

        struct food *snack = food_head;
        while (snack != NULL) {
            if (strcmp(merk, snack->name) == 0) {
                printf("What do you want to change?\n");
                printf("1. Change Price\n");
                printf("2. Add Stock\n");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    getchar(); 
                    snack->price = newprice;
                } else if (choice == 2) {
                    printf("Input added stock quantity: ");
                    scanf("%d", &newstock);
                    getchar(); 
                    snack->stock += newstock;
                }

                pick = fopen(file, "w");
                if (!pick) {
                    printf("Error.\n");
                    return;
                }

                struct food *current = food_head;
                while (current != NULL) {
                    fprintf(pick, "%s#%d#%d\n", current->name, current->stock, current->price);
                    current = current->next;
                }
                fclose(pick);
                printf("Data updated successfully.\n");
                return;
            }
            snack = snack->next;
        }
        printf("Item not found.\n");
    } else if (choice == 2) {
        printf("Beverage: ");
        scanf("%99s", merk);
        getchar(); 
        
        struct beverage *drink = drink_head;
        while (drink != NULL) {
            if (strcmp(merk, drink->name) == 0) {
                printf("What do you want to change?\n");
                printf("1. Change Price\n");
                printf("2. Add Stock\n");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    getchar();
                    drink->price = newprice;
                } else if (choice == 2) {
                    printf("Input new stock quantity: ");
                    scanf("%d", &newstock);
                    getchar(); 
                    drink->stock += newstock;
                }

                FILE *beverage = fopen("beverage.txt", "w");
                if (!beverage) {
                    printf("Error.\n");
                    return;
                }
                struct beverage *current = drink_head;
                while (current != NULL) {
                    fprintf(beverage, "%s#%d#%d\n", current->name, current->stock, current->price);
                    current = current->next;
                }
                fclose(beverage);
                printf("Data updated successfully.\n");
                return;
            }
            drink = drink->next;
        }
        printf("Item not found.\n");
    }
}

void printInventory(struct food *food_head, struct beverage *drink_head) {
    int choice;
    printf("Choice:\n");
    printf("1. Food inventory\n");
    printf("2. Beverage inventory\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        FILE *pick = NULL;
        printf("Category:\n");
        printf("1. Popcorn\n");
        printf("2. Fritters\n");
        printf("3. Light meal\n");
        printf("4. Bakery\n");
        printf("Choice: ");
        scanf("%d", &choice);

        char *file = NULL;
        switch (choice) {
            case 1: 
                file = "popcorn.txt"; 
                break;
            case 2: 
                file = "fritters.txt"; 
                break;
            case 3: 
                file = "lightmeal.txt"; 
                break;
            case 4: 
                file = "bakery.txt"; 
                break;
            default: 
                printf("Invalid choice.\n"); 
                return;
        }

        pick = fopen(file, "r");
        if (!pick) {
            printf("Error: Could not open %s.\n", file);
            return;
        }

        while (!feof(pick)) {
            struct food *food = (struct food *)malloc(sizeof(struct food));
            if (fscanf(pick, "%[^#]#%d#%d\n", food->name, &food->stock, &food->price) == 3) {
                food->next = food_head;
                food_head = food;
            } 
        }
        fclose(pick);

        printf("================================\n");
        printf("            Inventory           \n");
        printf("================================\n");
        struct food *temp = food_head;
        while (temp != NULL) {
            printf("Food    : %s\n", temp->name);
            printf("Stock   : %d\n", temp->stock);
            printf("Price   : %d\n", temp->price);
            printf("================================\n");
            temp = temp->next;
        }
    } else if (choice == 2) {
    FILE *beverage_file = fopen("beverage.txt", "r");
    if (!beverage_file) {
        printf("Error.\n");
        return;
    }

    struct beverage *head = NULL;
    while (!feof(beverage_file)) {
        struct beverage *beverage = (struct beverage *)malloc(sizeof(struct beverage));
        if (fscanf(beverage_file, "%[^#]#%d#%d\n", beverage->name, &beverage->stock, &beverage->price) == 3) {
            beverage->next = head;
            head = beverage;
        } else {
            free(beverage);
        }
    }
    fclose(beverage_file);

    printf("================================\n");
    printf("            Inventory           \n");
    printf("================================\n");
    struct beverage *temp = head;
    while (temp != NULL) {
        printf("Beverage: %s\n", temp->name);
        printf("Stock   : %d\n", temp->stock);
        printf("Price   : %d\n", temp->price);
        printf("================================\n");
        temp = temp->next;
    }
    }
}

// USER FOOD & BEV FUNCTIONS
void buyBev(struct cart **buy, struct beverage *drink_head) {
    FILE *beverage_file = fopen("beverage.txt", "r");
    if (!beverage_file) {
        printf("Error: Could not open beverage.txt.\n");
        return;
    }

    struct beverage *head = NULL;
    while (!feof(beverage_file)) {
        struct beverage *beverage = (struct beverage *)malloc(sizeof(struct beverage));
        if (fscanf(beverage_file, "%[^#]#%d#%d\n", beverage->name, &beverage->stock, &beverage->price) == 3) {
            beverage->next = head;
            head = beverage;
        } else {
            free(beverage);
        }
    }
    fclose(beverage_file);

    struct beverage *show = head;
    int id = 1;

    printf("========================================\n");
    printf("                  Menu                  \n");
    printf("========================================\n");

    while (show != NULL) {
        printf("%d. Name    : %-20s\n", id, show->name);
        printf("   Price   : %-18d\n", show->price);
        printf("========================================\n");
        show = show->next;
        id++;
    }

    while (head != NULL) {
        struct beverage *trash = head;
        head = head->next;
        free(trash);
    }

    int bev_id;
    int quan;
    printf("Enter beverage ID: ");
    scanf("%d", &bev_id);
    getchar(); 
    printf("Enter quantity: ");
    if (scanf("%d", &quan) != 1 || quan <= 0) {
        printf("Invalid quantity entered.\n");
        return;
    }
    getchar(); 

    FILE *beverage = fopen("beverage.txt", "r");
    if (beverage == NULL) {
        printf("Error.\n");
        return;
    }

    char drink_name[50];
    int drink_stock, drink_price;
    int drink_id = 1, found = 0;

    while (fscanf(beverage, "%[^#]#%d#%d\n", drink_name, &drink_stock, &drink_price) == 3) {
        if (drink_id == bev_id) {
            found = 1;
            if (drink_stock < quan) {
                printf("Sorry, we only have %d in stock.\n", drink_stock);
                fclose(beverage);
                return;
            }
            break;
        }
        drink_id++;
    }
    fclose(beverage);

    if (!found) {
        printf("Invalid beverage ID.\n");
        return;
    }

    struct beverage *temp = drink_head;
    while (temp != NULL) {
        if (strcmp(temp->name, drink_name) == 0) {
            temp->stock -= quan;
            break;
        }
        temp = temp->next;
    }

    struct item *new_drink = malloc(sizeof(struct item));
    if (!new_drink) {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(new_drink->buyDrink.name, drink_name);
    new_drink->bQuantity = quan;
    new_drink->bPrice = quan * drink_price;
    new_drink->next = (*buy)->items; 
    (*buy)->items = new_drink;
    (*buy)->cartTop++;

    FILE *beverage_write = fopen("beverage.txt", "w");
    if (!beverage_write) {
        printf("Error.\n");
        return;
    }

    struct beverage *current = drink_head;
    while (current != NULL) {
        fprintf(beverage_write, "%s#%d#%d\n", current->name, current->stock, current->price);
        current = current->next;
    }
    fclose(beverage_write);

    printf("'%s' added to cart successfully.\n", drink_name);
}

void buyFood(struct cart **buy, struct food *food_head) {

    int choice;
        FILE *pick = NULL;
        printf("Category:\n");
        printf("1. Popcorn\n");
        printf("2. Fritters\n");
        printf("3. Light meal\n");
        printf("4. Bakery\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); 

        char *file = NULL;
        switch (choice) {
            case 1: file = "popcorn.txt"; break;
            case 2: file = "fritters.txt"; break;
            case 3: file = "lightmeal.txt"; break;
            case 4: file = "bakery.txt"; break;
            default: printf("Invalid choice.\n"); return;
        }

        pick = fopen(file, "r");
        if (!pick) {
            printf("Error: Could not open %s.\n", file);
            return;
        }

        struct food *head = NULL;
        while (!feof(pick)) {
            struct food *new_food = malloc(sizeof(struct food));
            if (fscanf(pick, "%[^#]#%d#%d\n", new_food->name, &new_food->stock, &new_food->price) == 3) {
                new_food->next = head;
                head = new_food;
            } else {
                free(new_food);
            }
        }
        fclose(pick);

        int total = 0;
        struct food *counter = head;
        while (counter != NULL) {
            total++;
            counter = counter->next;
        }

       
        struct food *show = head;
        int id = total;

        printf("========================================\n");
        printf("                  Menu                  \n");
        printf("========================================\n");

        while (show != NULL) {
            printf("%d. Name    : %-20s\n", id, show->name);
            printf("   Price   : %-18d\n", show->price);
            printf("========================================\n");
            show = show->next;
            id--;
        }

        int quan, food_id;
        printf("Enter food ID: ");
        scanf("%d", &food_id);
        getchar(); 
        printf("Enter quantity: ");
        if (scanf("%d", &quan) != 1 || quan <= 0) {
            printf("Invalid quantity entered.\n");
            return;
        }
        getchar(); 

      
        struct food *selected = head;
        int current_id = total;
        while (selected != NULL && current_id != food_id) {
            selected = selected->next;
            current_id--;
        }

        if (selected == NULL) {
            printf("Invalid food ID.\n");
            return;
        }

        if (selected->stock < quan) {
            printf("Sorry, we only have %d in stock.\n", selected->stock);
            return;
        }

      
        struct food *temp_food = food_head;
        while (temp_food != NULL) {
            if (strcmp(temp_food->name, selected->name) == 0) {
                temp_food->stock -= quan;
                break;
            }
            temp_food = temp_food->next;
        }

     
        struct item *new_food = malloc(sizeof(struct item));
        if (!new_food) {
            printf("Memory allocation failed.\n");
            return;
        }

        strcpy(new_food->buyFood.name, selected->name);
        new_food->fQuantity = quan;
        new_food->fPrice = quan * selected->price;
        new_food->next = (*buy)->items;
        (*buy)->items = new_food;
        (*buy)->cartTop++;

       
        FILE *food_write = fopen(file, "w");
        if (!food_write) {
            printf("Error.\n");
            return;
        }

        struct food *current = food_head;
        while (current != NULL) {
            fprintf(food_write, "%s#%d#%d\n", current->name, current->stock, current->price);
            current = current->next;
        }
        fclose(food_write);

        printf("'%s' added to cart successfully.\n", selected->name);
    }

    void seeCart(struct cart *buy) {
        if (buy->cartTop == -1 || buy->items == NULL) {
            printf("\nCart is empty\n");
            return;
        }
    
        printf("===================================================================\n");
        printf("                               Cart                                \n");
        printf("===================================================================\n");
    
        struct item *temp = buy->items;
        while (temp != NULL) {
            if (temp->fQuantity > 0) {
                printf("Food    : %-15s  Quantity: %-5d  Total: %-5d\n", temp->buyFood.name, temp->fQuantity, temp->fPrice);
            }
            if (temp->bQuantity > 0) {
                printf("Beverage: %-15s  Quantity: %-5d  Total: %-5d\n", temp->buyDrink.name, temp->bQuantity, temp->bPrice);
            }
            temp = temp->next;
        }
        printf("===================================================================\n");
    }
    

void changeQuantity(struct cart **buy) {
    int newquan, choice;
    char name[50];
    printf("Choice:\n");
    printf("1. Food\n");
    printf("2. Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter food name to change quantity: ");
        scanf("%49s", name);

        struct item *temp = (*buy)->items;
        while (temp != NULL) {
            if (strcmp(temp->buyFood.name, name) == 0 && temp->fQuantity > 0) {
                printf("Current quantity: %d\n", temp->fQuantity);
                printf("Enter new quantity: ");
                scanf("%d", &newquan);

                if (newquan <= 0) {
                    printf("Invalid quantity. Quantity must be greater than zero.\n");
                    return;
                }

                temp->fPrice = (temp->fPrice / temp->fQuantity) * newquan;
                temp->fQuantity = newquan; 
                printf("Food quantity updated successfully.\n");
                return;
            }
            temp = temp->next;
        }

        printf("Food item '%s' not found in cart.\n", name);

    } else if (choice == 2) {
        printf("Enter beverage name to change quantity: ");
        scanf("%49s", name);

        struct item *temp = (*buy)->items;
        while (temp != NULL) {
            if (strcmp(temp->buyDrink.name, name) == 0 && temp->bQuantity > 0) {
                printf("Current quantity: %d\n", temp->bQuantity);
                printf("Enter new quantity: ");
                scanf("%d", &newquan);

                if (newquan <= 0) {
                    printf("Invalid quantity. Quantity must be greater than zero.\n");
                    return;
                }

                temp->bPrice = (temp->bPrice / temp->bQuantity) * newquan;
                temp->bQuantity = newquan; 
                printf("Beverage quantity updated successfully.\n");
                return;
            }
            temp = temp->next;
        }

        printf("Beverage item '%s' not found in cart.\n", name);

    } else {
        printf("Invalid choice.\n");
    }
}

void deleteByName(struct cart **buy) {
    int choice;
    char name[50];
    printf("Choice:\n");
    printf("1. Delete Food\n");
    printf("2. Delete Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter food name to delete: ");
        scanf("%49s", name);

        struct item *temp = (*buy)->items, *prev = NULL;

        while (temp != NULL) {
            if (strcmp(temp->buyFood.name, name) == 0 && temp->fQuantity > 0) {
                if (prev == NULL) {
                    (*buy)->items = temp->next; 
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                (*buy)->cartTop--;
                printf("Food item '%s' deleted successfully from cart.\n", name);
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        printf("Food item '%s' not found in cart.\n", name);

    } else if (choice == 2) {
        printf("Enter beverage name to delete: ");
        scanf("%49s", name);

        struct item *temp = (*buy)->items, *prev = NULL;

        while (temp != NULL) {
            if (strcmp(temp->buyDrink.name, name) == 0 && temp->bQuantity > 0) {
                if (prev == NULL) {
                    (*buy)->items = temp->next; 
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                (*buy)->cartTop--;
                printf("Beverage item '%s' deleted successfully from cart.\n", name);
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        printf("Beverage item '%s' not found in cart.\n", name);

    } else {
        printf("Invalid choice.\n");
    }
}

void ownerFood(struct food **food_head, struct beverage **drink_head, struct cart *buy) {
    int choice, j;
    
    while (1) {
        printf("\nChoice : \n");
        printf("1. Add Food\n");
        printf("2. Add Beverage\n");
        printf("3. Print Inventory\n");
        printf("4. Change Stock and Price\n");
        printf("5. Check Inventory\n");
        printf("6. Exit\n");
        printf("Choice : ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter number of food: ");
                scanf("%d", &j);
                getchar(); 
                addfood(food_head, j);
                break;
            case 2:
                printf("Enter number of beverage: ");
                scanf("%d", &j);
                getchar();
                addbev(drink_head, j);
                break;
            case 3:
                printInventory(*food_head, *drink_head);
                break;
            case 4:
                changePriceStock(*food_head, *drink_head, 0);
                break;
            case 5:
                checkInventory(*food_head, *drink_head);
                break;
            case 6:
                printf("Exiting program.\n");

                while (*food_head != NULL) {
                    struct food *trash = *food_head;
                    *food_head = (*food_head)->next;
                    free(trash);
                }

                while (drink_head != NULL) {
                    struct beverage *trash = *drink_head;
                    *drink_head = (*drink_head)->next;
                    free(trash);
                }

                while ((*buy).items != NULL) {
                    struct item *trash = (*buy).items;
                    (*buy).items = (*buy).items->next;
                    free(trash);
                }
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void userFood(struct food **food_head, struct beverage **drink_head, struct cart *buy, struct food *snack, struct beverage *drink) {
    int choice, j;

    while (1){
        printf("Choice : \n");
        printf("1. Buy food\n");
        printf("2. Buy drinks\n");
        printf("3. See cart \n");
        printf("4. Change quantity\n");
        printf("5. Delete item\n");
        printf("6. Exit \n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice){
            case 1:
            buyFood(&buy, snack);
            break;

            case 2:
            buyBev(&buy, drink);
            break;

            case 3:
            seeCart(buy);
            break;

            case 4:
            changeQuantity(&buy);
            break;

            case 5:
            deleteByName(&buy);
            break;

            case 6:
            printf("Exiting program.\n");
            return;
            
            default:
            printf("Invalid choice.\n");

        }
     
    }
    
}

void invoice(struct cart *buy, char *selectedMovie, char *cinProvChoice, char *cinLocChoice, int totalFoodPrice) {
    FILE *invoice = fopen("invoice.txt", "w");
    if (invoice == NULL) {
        printf("Error opening invoice file.\n");
        return;
    }

    fprintf(invoice, "========================================\n");
    fprintf(invoice, "               INVOICE                  \n");
    fprintf(invoice, "========================================\n");
    fprintf(invoice, "Movie: %s\n", selectedMovie);
    fprintf(invoice, "Location: %s, %s\n", cinProvChoice, cinLocChoice);
    fprintf(invoice, "Ticket Price: Rp70000\n");
    fprintf(invoice, "Food & Beverage Price: Rp%d\n", totalFoodPrice);
    fprintf(invoice, "Total Price: Rp%d\n", totalFoodPrice + 70000);
    fprintf(invoice, "========================================\n");
    fprintf(invoice, "DISCLAIMER: Any movie ticket / food you bought cannot be returned or refunded.\nTicket should be claimed at the cinema cashier.\n");
    fprintf(invoice, "Food should be claimed at the food cashier.\n");
    fprintf(invoice, "How to claim your ticket & food: \n1. Go to the Cinema that you selected\n2. Go to the ticket cashier to select your movie schedule and seating then claim your ticket\n3. Go to the food cashier to claim your food\n");
    fclose(invoice);
}

int main(){

    int login, attempt = 0;
    int choice = 0;
    int ownerSelection = 0;
    int choice2 = 0;

    // MOVIE
    Movie *mov_head, *mov_tail;
    mov_head = mov_tail = NULL;
    int choose, menu, list, index;
    char selectedMovie[50] = {"None"};
    loadMovies(&mov_head, &mov_tail);

    // LOCATION
    char correctUsername[] = {"admin"}, inputtedUsername[51];
    char correctPassword[] = {"admin"}, inputtedPassword[51];
    char cinProvChoice[100], cinLocChoice[100];
    cinLoc *cin_head, *cin_tail;
    cinProv *cin_front, *cin_back;

    cin_head = cin_tail = NULL;
    cin_front = cin_back = NULL;

    //FOOD & BEV
    struct cart buy = {.items = NULL, .cartTop = -1};
    struct food *food_head = NULL;
    struct beverage *drink_head = NULL;

    while(choice != 3){
        printf("Select Option: \n");
        printf("1. Owner\n");
        printf("2. User\n");
        printf("3. Exit\n");
        printf("Selection: ");

        scanf(" %d", &choice);
        
        if(choice == 1){
            while (attempt < 3)
            {
                printf("Username: ");
                scanf(" %[^\n]", inputtedUsername);
                printf("Password: ");
                scanf(" %[^\n]", inputtedPassword);
                if (strcmp(correctUsername, inputtedUsername) == 0 && strcmp(correctPassword, inputtedPassword) == 0)
                {
                    printf("\n");
                    break;
                }
                attempt++;
                if (attempt < 3)
                {
                    printf("\nUsername or Password Incorrect (Remaining Attempt: %d)\n\n", 3 - attempt);
                }
                else
                {
                    printf("\nTry Again Next Time");
                }
            }
    
            if (attempt != 3)
            {
                ownerSelection = 0;
                while (ownerSelection != 4){

                    printf("Select your categories: \n");
                    printf("1. Location modification\n");
                    printf("2. Movie list modification\n");
                    printf("3. Food list modification\n");
                    printf("4. Exit\n");
                    printf("Selection: ");
                    scanf(" %d", &ownerSelection);

                    if (ownerSelection == 1){
                        owner(&cin_head, &cin_tail, &cin_front, &cin_back);
                    }
                    else if (ownerSelection == 2){
                        ownerMovie(&mov_head, &mov_tail);
                    }
                    else if (ownerSelection == 3){
                        ownerFood(&food_head, &drink_head, &buy);
                    }
                    else if (ownerSelection == 4){
                        break;
                    }
                    else{
                        continue;
                    }
                }

            }
            
        }
        else if (choice == 2){
            printf("Please select your location\n");
            chooseCinema(&cin_head, &cin_tail, &cin_front, &cin_back, cinProvChoice, cinLocChoice);

            choice2 = 0;

            while (choice2 != 3){
                printf("Province: %s | Location: %s\n", cinProvChoice, cinLocChoice);
                printf("Selected Movie: %s\n", selectedMovie);
                printf("Select your category: \n");
                printf("1. Select movie\n");
                printf("2. Order food\n");
                printf("3. Check out\n");
                printf("4. Exit\n");
                printf("Selection: ");
                scanf(" %d", &choice2);

                if (choice2 == 1){
                    userMovie(&mov_head, &mov_tail, selectedMovie);
                }

                else if (choice2 == 2){
                    userFood(&food_head, &drink_head, &buy, food_head, drink_head);
                }
                else if (choice2 == 3){
                    printf("Thank you for your order!\n");
                    printf("Selected movie: %s\n", selectedMovie);
                    printf("Selected food: \n");
                    seeCart(&buy);
                    printf("Ticket Price: Rp70000\n");

                    int totalFoodPrice = 0;
                    struct item *currentItem = buy.items;
                    while (currentItem != NULL) {
                        totalFoodPrice += currentItem->fPrice + currentItem->bPrice;
                        currentItem = currentItem->next;
                    }

                    printf("Food Price: Rp%d\n", totalFoodPrice);
                    printf("Total Price: Rp%d\n", totalFoodPrice + 70000);
                    printf("Invoice will be printed. Please check invoice.txt\n");
                    invoice(&buy, selectedMovie, cinProvChoice, cinLocChoice, totalFoodPrice);
                    printf("Enjoy your movie!\n");
                }
                else if (choice2 == 4){
                    break;
                }
            }
        }
        else if (choice == 3){
            printf("Thank you for using our service!\n");
            deleteLocationNodes(&cin_head, &cin_tail);
            deleteProvinceNodes(&cin_front, &cin_back);
            deleteNodes(mov_head);
            while (food_head != NULL) {
                struct food *trash = food_head;
                food_head = food_head->next;
                free(trash);
            }

            while (drink_head != NULL) {
                struct beverage *trash = drink_head;
                drink_head = drink_head->next;
                free(trash);
            }

            while (buy.items != NULL) {
                struct item *trash = buy.items;
                buy.items = buy.items->next;
                free(trash);
            }
            break;
        }
        else{
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}