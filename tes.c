#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

// Struktur untuk provinsi dan lokasi bioskop
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

void addCinemaLocationAndNewProvince(int *counterProv)
{
    char newProvince[50], newLocation[50];
    FILE *cinProvFile = fopen("cinema_province.txt", "a");
    FILE *cinLocFile = fopen("cinema_location.txt", "a");

    printf("Please Use Uppercase To Input!\n");
    printf("Input New Province: ");
    scanf(" %[^\n", newProvince);
    (*counterProv)++;
    fprintf(cinProvFile, "%s#%d\n", newProvince, *counterProv);

    printf("Input New Location: ");
    scanf(" %[^\n]", newLocation);
    fprintf(cinLocFile, "%s#%d\n", newLocation, *counterProv);

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void deleteCinemaProvinceAndLocation(cinLoc **head, cinLoc **tail, cinProv **front, cinProv **back, int *counterLoc, int *counterProv)
{
    int provinceCode;
    cinLoc *tempLoc = *head, *trashLoc;
    cinProv *tempProv = *front, *trashProv;

    printf("\nPlease Input The Code!\n");
    printf("Choose a Code For an Unwanted Province: ");
    scanf("%d", &provinceCode);
    printf("\n");

    // Hapus semua lokasi yang berkaitan dengan provinceCode
    while (tempLoc && tempLoc->code == provinceCode)
    {
        trashLoc = tempLoc;
        tempLoc = tempLoc->next;
        free(trashLoc);
        (*counterLoc)--;
    }

    // Hapus provinsi
    while (tempProv && tempProv->code == provinceCode)
    {
        trashProv = tempProv;
        tempProv = tempProv->next;
        free(trashProv);
        (*counterProv)--;
    }

    printf("Province and its cinemas deleted successfully!\n\n");
}

void ownerMode(cinLoc **head, cinLoc **tail, cinProv **front, cinProv **back)
{
    int userActivity;
    int counterProv = 0, counterLoc = 0;

    while (1)
    {
        printf("1. Add New Cinema's Location and New Province\n");
        printf("2. Delete Cinema's Province\n");
        printf("3. Exit Owner Mode\n");
        printf("What Do You Want To Do? ");
        scanf("%d", &userActivity);
        printf("\n");

        switch (userActivity)
        {
        case 1:
            addCinemaLocationAndNewProvince(&counterProv);
            break;
        case 2:
            deleteCinemaProvinceAndLocation(head, tail, front, back, &counterLoc, &counterProv);
            break;
        case 3:
            printf("Exiting Owner Mode...\n");
            return;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }
}

int main()
{
    int login;
    cinLoc *head = NULL, *tail = NULL;
    cinProv *front = NULL, *back = NULL;

    printf("1. Customer\n");
    printf("2. Owner\n");
    printf("Choose Your Mode: ");
    scanf("%d", &login);
    printf("\n");

    if (login == 2)
    {
        ownerMode(&head, &tail, &front, &back);
    }
    else
    {
        printf("Customer mode not implemented yet.\n");
    }
    return 0;
}
