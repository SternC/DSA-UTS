#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct cinemaProvince
{
    char province[50];
    int code;
    struct cinemaProvince *prev, *next;
} cinProv;

typedef struct cinemaLocation
{
    char cinema[50];
    int code;
    int num;
    struct cinemaLocation *prev, *next;
} cinLoc;

void deleteLocationNodes(cinLoc **head, cinLoc **tail)
{
    cinLoc *tempNode, *tempNextNode;

    tempNode = *head;

    while (tempNode != NULL)
    {
        tempNextNode = tempNode->next;

        if (tempNode == *tail)
        {
            free(tempNode);
            break;
        }

        free(tempNode);
        tempNode = tempNextNode;
    }

    *head = NULL;
    *tail = NULL;
}

void deleteProvinceNodes(cinProv **front, cinProv **back)
{
    cinProv *tempNode, *tempNextNode;

    tempNode = *front;

    while (tempNode != NULL)
    {
        tempNextNode = tempNode->next;

        if (tempNode == *back)
        {
            free(tempNode);
            break;
        }

        free(tempNode);
        tempNode = tempNextNode;
    }

    *front = NULL;
    *back = NULL;
}

void addCinemaLocationAndNewProvince(int counterProv)
{
    char newProvince[50], newLocation[50];

    FILE *cinProvFile = fopen("cinema_province.txt", "a");
    FILE *cinLocFile = fopen("cinema_location.txt", "a");

    printf("Please Use Uppercase To Input!\n");
    printf("Input New Province: ");
    scanf(" %[^\n]", newProvince);
    fprintf(cinProvFile, "\n%s#%d", newProvince, counterProv + 1);

    printf("Input New Location: ");
    scanf(" %[^\n]", newLocation);
    fprintf(cinLocFile, "\n%s#%d#1", newLocation);
    printf("\n");

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void addCinemaLocationFromExistingProvince(cinLoc **head)
{
    cinLoc *tempLoc;
    int provinceCode;
    char newLocation[50];
    int newNum = 0;

    tempLoc = *head;

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
        if (tempLoc == *head)
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

void deleteCinemaLocation(cinLoc **head, cinLoc **tail, int *counterLoc)
{
    int provinceCode, cinemaNum;
    cinLoc *tempLoc = *head;

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

    if (tempLoc == *head)
    {
        *head = tempLoc->next;
        (*head)->prev = *tail;
    }
    else if (tempLoc == *tail)
    {
        *tail = tempLoc->prev;
        (*tail)->next = *head;
    }
    else
    {
        tempLoc->prev->next = tempLoc->next;
        tempLoc->next->prev = tempLoc->prev;
    }
    free(tempLoc);
    (*counterLoc)--;

    tempLoc = *head;
    for (int i = 0; i < *counterLoc; i++)
    {
        fprintf(cinLocFile, "%s#%d#%d\n", tempLoc->cinema, tempLoc->code, tempLoc->num);
        tempLoc = tempLoc->next;
    }

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void deleteCinemaProvinceAndLocation(cinLoc **head, cinLoc **tail, cinProv **front, cinProv **back, int *counterLoc, int *counterProv)
{
    cinLoc *tempLoc = *head;
    cinProv *tempProv = *front;
    int provinceCode, counterCode = 0;

    FILE *cinProvFile = fopen("cinema_province.txt", "w");
    FILE *cinLocFile = fopen("cinema_location.txt", "w");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%d", &provinceCode);
    printf("\n");

    if (tempProv == *front)
    {
        *front = (*front)->next;
        (*back)->next = *front;
        (*front)->prev = *back;
    }
    else if (tempProv == *back)
    {
        *back = (*back)->prev;
        (*front)->prev = *back;
        (*back)->next = *front;
    }
    else
    {
        tempProv->next->prev = tempProv->prev;
        tempProv->prev->next = tempProv->next;
    }
    free(tempProv);
    (*counterProv)--;

    tempProv = *front;
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
        if (tempLoc == *head)
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

        if (tempLoc == *head)
        {
            *head = (*head)->next;
            (*tail)->next = *head;
            (*head)->prev = *tail;
        }
        else if (tempLoc == *tail)
        {
            *tail = (*tail)->prev;
            (*head)->prev = *tail;
            (*tail)->next = *head;
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

    tempLoc = *head;
    for (int i = 0; i < *counterLoc; i++)
    {
        fprintf(cinLocFile, "%s#%d#%d\n", tempLoc->cinema, tempLoc->code, tempLoc->num);
        tempLoc = tempLoc->next;
    }

    fclose(cinLocFile);
}

void chooseCinema(cinLoc **head, cinLoc **tail, cinProv **front, cinProv **back)
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

        if (*front == NULL)
        {
            *front = *back = nodeProv;
        }
        else
        {
            nodeProv->prev = *back;
            (*back)->next = nodeProv;
            *back = nodeProv;
        }
        (*back)->next = *front;
        (*front)->prev = *back;
        counterProv++;
    }

    while (!feof(cinLocFile))
    {
        nodeLoc = (cinLoc *)malloc(sizeof(cinLoc));
        fscanf(cinLocFile, " %[^#]#%d#%d\n", nodeLoc->cinema, &nodeLoc->code, &nodeLoc->num);

        if (*head == NULL)
        {
            *head = *tail = nodeLoc;
        }
        else
        {
            nodeLoc->prev = *tail;
            (*tail)->next = nodeLoc;
            *tail = nodeLoc;
        }
        (*tail)->next = *head;
        (*head)->prev = *(tail);
        counterLoc++;
    }

    fclose(cinLocFile);
    fclose(cinProvFile);

    tempProv = *front;
    tempLoc = *head;

    for (int i = 0; i < counterProv; i++)
    {
        printf("%d. %s\n", i + 1, tempProv->province);
        tempProv = tempProv->next;
    }

    printf("Choose Your Province: ");
    scanf("%d", &userProv);
    printf("\n");

    for (int j = 0; j < counterLoc; j++)
    {
        if (tempLoc->code == userProv)
        {
            printf("%d. %s\n", j + 1, tempLoc->cinema);
        }
        tempLoc = tempLoc->next;
    }
    printf("Choose Your Cinema: ");
    scanf("%d", &userCinema);
    printf("\n");
}

void owner(cinLoc **head, cinLoc **tail, cinProv **front, cinProv **back)
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

            if (*front == NULL)
            {
                *front = *back = nodeProv;
            }
            else
            {
                nodeProv->prev = *back;
                (*back)->next = nodeProv;
                *back = nodeProv;
            }
            (*back)->next = *front;
            (*front)->prev = *back;
            counterProv++;
        }

        while (!feof(cinLocFile))
        {
            nodeLoc = (cinLoc *)malloc(sizeof(cinLoc));
            fscanf(cinLocFile, " %[^#]#%d#%d\n", nodeLoc->cinema, &nodeLoc->code, &nodeLoc->num);

            if (*head == NULL)
            {
                *head = *tail = nodeLoc;
            }
            else
            {
                nodeLoc->prev = *tail;
                (*tail)->next = nodeLoc;
                *tail = nodeLoc;
            }
            (*tail)->next = *head;
            (*head)->prev = *(tail);
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
            tempProv = *front;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%d\n", i + 1, tempProv->province, tempProv->code);
                tempProv = tempProv->next;
            }
            addCinemaLocationFromExistingProvince(head);
            break;

        case 3:
            tempProv = *front;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%d\n", i + 1, tempProv->province, tempProv->code);
                tempProv = tempProv->next;
            }
            deleteCinemaLocation(head, tail, &counterLoc);
            break;

        case 4:
            tempProv = *front;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%d\n", i + 1, tempProv->province, tempProv->code);
                tempProv = tempProv->next;
            }
            deleteCinemaProvinceAndLocation(head, tail, front, back, &counterLoc, &counterProv);
            break;

        default:
            deleteLocationNodes(head, tail);
            deleteProvinceNodes(front, back);
            return;
        }

        deleteLocationNodes(head, tail);
        deleteProvinceNodes(front, back);
    }
}

int main()
{
    int login, attempt = 0;
    char correctUsername[] = {"admin"}, inputtedUsername[50], correctPassword[] = {"admin"}, inputtedPassword[50];
    cinLoc *head, *tail;
    cinProv *front, *back;

    head = tail = NULL;
    front = back = NULL;

    printf("1. Customer\n");
    printf("2. Owner\n");
    printf("Choose Your Mode: ");
    scanf("%d", &login);
    printf("\n");

    if (login == 1)
    {
        chooseCinema(&head, &tail, &front, &back);
    }
    else if (login == 2)
    {
        while (attempt < 3)
        {
            printf("Username: ");
            scanf(" %[^\n]", inputtedUsername);
            printf("Password: ");
            scanf(" %[^\n]", inputtedPassword);
            if (strcmp(correctUsername, inputtedUsername) == 0 && strcmp(correctPassword, inputtedPassword) == 0)
            {
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
            owner(&head, &tail, &front, &back);
        }
    }

    return 0;
}