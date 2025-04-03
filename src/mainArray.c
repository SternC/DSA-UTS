#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fprintf(cinLocFile, "%s#%s#1\n", newLocation);
    printf("\n");

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void addCinemaLocationFromExistingProvince(char provinceAndCode[100][2][101], char locationAndCodeAndNum[100][3][101])
{
    char provinceCode[101];
    char newLocation[51];
    int newNum, counter;

    newNum = counter = 0;

    FILE *cinProvFile = fopen("cinema_province.txt", "r");
    FILE *cinLocFile = fopen("cinema_location.txt", "a+");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%s", provinceCode);
    printf("\n");

    while (1)
    {
        if (strcmp(locationAndCodeAndNum[counter][1], provinceCode) == 0)
        {
            newNum++;
        }
        counter++;
        if (strcmp(locationAndCodeAndNum[counter][0], "") == 0)
        {
            break;
        }
    }

    printf("Please Use Uppercase To Input!\n");
    printf("Input New Location: ");
    scanf(" %[^\n]", newLocation);
    fprintf(cinLocFile, "\n%s#%s#%d", newLocation, provinceCode, newNum + 1);
    printf("\n");

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void deleteCinemaLocation(int *counterLoc, char provinceAndCode[100][2][101], char locationAndCodeAndNum[100][3][101])
{
    char provinceCode[101], cinemaNum[101];
    int counter, counterShift;

    FILE *cinProvFile = fopen("cinema_province.txt", "r");
    FILE *cinLocFile = fopen("cinema_location.txt", "w");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%s", provinceCode);
    printf("\n");

    for (int i = 0; i < *counterLoc; i++)
    {
        if (strcmp(locationAndCodeAndNum[i][1], provinceCode) == 0)
        {
            printf("%d. %s\n", i + 1, locationAndCodeAndNum[i][0]);
        }
    }

    printf("Choose Unwanted Cinema: ");
    scanf("%s", cinemaNum);
    printf("\n");

    counter = 0;
    while (strcmp(locationAndCodeAndNum[counter][1], provinceCode) != 0 || strcmp(locationAndCodeAndNum[counter][2], cinemaNum) != 0)
    {
        counter++;
    }

    (*counterLoc)--;
    counterShift = *counterLoc - counter;

    for (int i = 0; i < counterShift; i++)
    {
        strcpy(locationAndCodeAndNum[counter][0], locationAndCodeAndNum[counter + 1][0]);
        strcpy(locationAndCodeAndNum[counter][1], locationAndCodeAndNum[counter + 1][1]);
        strcpy(locationAndCodeAndNum[counter][2], locationAndCodeAndNum[counter + 1][2]);
        counter++;
    }

    counter = 0;
    for (int i = 0; i < *counterLoc; i++)
    {
        fprintf(cinLocFile, "%s#%s#%s\n", locationAndCodeAndNum[counter][0], locationAndCodeAndNum[counter][1], locationAndCodeAndNum[counter][2]);
        counter++;
    }

    fclose(cinProvFile);
    fclose(cinLocFile);
}

void deleteCinemaProvinceAndLocation(int *counterLoc, int *counterProv, char provinceAndCode[100][2][101], char locationAndCodeAndNum[100][3][101])
{
    char provinceCode[101], cinemaNum[101];
    int counter, counterShiftProv, counterShiftLoc, counterCode;

    FILE *cinProvFile = fopen("cinema_province.txt", "w");
    FILE *cinLocFile = fopen("cinema_location.txt", "w");

    printf("\nPlease Input The Code!\n");
    printf("Choose Province's Code: ");
    scanf("%s", provinceCode);
    printf("\n");

    counter = 0;
    while (strcmp(provinceAndCode[counter][1], provinceCode) != 0)
    {
        counter++;
    }

    (*counterProv)--;
    counterShiftProv = *counterLoc - counter;

    for (int i = 0; i < counterShiftProv; i++)
    {
        strcpy(provinceAndCode[counter][0], provinceAndCode[counter + 1][0]);
        strcpy(provinceAndCode[counter][1], provinceAndCode[counter + 1][1]);
        counter++;
    }

    counter = 0;
    for (int i = 0; i < *counterProv; i++)
    {
        fprintf(cinProvFile, "%s#%s\n", provinceAndCode[counter][0], provinceAndCode[counter][1]);
        counter++;
    }

    fclose(cinProvFile);

    counter = 0;
    counterCode = 0;
    while (1)
    {
        if (strcmp(locationAndCodeAndNum[counter][1], provinceCode) == 0)
        {
            counterCode++;
        }
        counter++;
        if (strcmp(locationAndCodeAndNum[counter][1], "") == 0)
        {
            break;
        }
    }

    for (int i = 0; i < counterCode; i++)
    {
        counter = 0;
        while (strcmp(locationAndCodeAndNum[counter][1], provinceCode) != 0)
        {
            counter++;
        }
        (*counterLoc)--;
        counterShiftLoc = *counterLoc - counter;

        for (int i = 0; i < counterShiftLoc; i++)
        {
            strcpy(locationAndCodeAndNum[counter][0], locationAndCodeAndNum[counter + 1][0]);
            strcpy(locationAndCodeAndNum[counter][1], locationAndCodeAndNum[counter + 1][1]);
            strcpy(locationAndCodeAndNum[counter][2], locationAndCodeAndNum[counter + 1][2]);
            counter++;
        }
    }

    counter = 0;
    for (int i = 0; i < *counterLoc; i++)
    {
        fprintf(cinLocFile, "%s#%s#%s\n", locationAndCodeAndNum[counter][0], locationAndCodeAndNum[counter][1], locationAndCodeAndNum[counter][2]);
        counter++;
    }

    fclose(cinLocFile);
}

void owner(char provinceAndCode[100][2][101], char locationAndCodeAndNum[100][3][101])
{
    int userActivity;
    int counterProv, counterLoc, counter;

    while (1)
    {
        counterProv = counterLoc = 0;

        FILE *cinProvFile = fopen("cinema_province.txt", "r");
        FILE *cinLocFile = fopen("cinema_location.txt", "r");

        while (!feof(cinProvFile))
        {
            fscanf(cinProvFile, " %[^#]#%[^\n]\n", provinceAndCode[counterProv][0], provinceAndCode[counterProv][1]);
            counterProv++;
        }

        while (!feof(cinLocFile))
        {
            fscanf(cinLocFile, " %[^#]#%[^#]#%[^\n]\n", locationAndCodeAndNum[counterLoc][0], locationAndCodeAndNum[counterLoc][1], locationAndCodeAndNum[counterLoc][2]);
            counterLoc++;
        }

        fclose(cinProvFile);
        fclose(cinLocFile);

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
            counter = 0;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%s\n", i + 1, provinceAndCode[counter][0], provinceAndCode[counter][1]);
                counter++;
            }
            addCinemaLocationFromExistingProvince(provinceAndCode, locationAndCodeAndNum);
            break;

        case 3:
            counter = 0;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%s\n", i + 1, provinceAndCode[counter][0], provinceAndCode[counter][1]);
                counter++;
            }
            deleteCinemaLocation(&counterLoc, provinceAndCode, locationAndCodeAndNum);
            break;

        case 4:
            counter = 0;

            for (int i = 0; i < counterProv; i++)
            {
                printf("%d. %s#%s\n", i + 1, provinceAndCode[counter][0], provinceAndCode[counter][1]);
                counter++;
            }
            deleteCinemaProvinceAndLocation(&counterLoc, &counterProv, provinceAndCode, locationAndCodeAndNum);
            break;

        default:
            return;
        }
    }
}

void chooseCinema(char provinceAndCode[100][2][101], char locationAndCodeAndNum[100][3][101])
{
    char userProv[101], userCinema[101];
    int counterProv, counterLoc, counter;

    counterLoc = counterProv = 0;

    FILE *cinProvFile = fopen("cinema_province.txt", "r");
    FILE *cinLocFile = fopen("cinema_location.txt", "r");

    while (!feof(cinProvFile))
    {
        fscanf(cinProvFile, " %[^#]#%[^\n]\n", provinceAndCode[counterProv][0], provinceAndCode[counterProv][1]);
        counterProv++;
    }

    while (!feof(cinLocFile))
    {
        fscanf(cinLocFile, " %[^#]#%[^#]#%[^\n]\n", locationAndCodeAndNum[counterLoc][0], locationAndCodeAndNum[counterLoc][1], locationAndCodeAndNum[counterLoc][2]);
        counterLoc++;
    }

    fclose(cinProvFile);
    fclose(cinLocFile);

    for (int i = 0; i < counterProv; i++)
    {
        printf("%d. %s\n", i + 1, provinceAndCode[i][0]);
    }

    printf("Choose Your Province: ");
    scanf("%s", userProv);
    printf("\n");

    for (int i = 0; i < counterLoc; i++)
    {
        if (strcmp(locationAndCodeAndNum[i][1], userProv) == 0)
        {
            printf("%d. %s\n", i + 1, locationAndCodeAndNum[i][0]);
        }
    }
    printf("Choose Your Cinema: ");
    scanf("%s", userCinema);
    printf("\n");
}

int main()
{
    int login, attempt = 0;
    char correctUsername[] = {"admin"}, inputtedUsername[50];
    char correctPassword[] = {"admin"}, inputtedPassword[50];
    char provinceAndCode[100][2][101];
    char locationAndCodeAndNum[100][3][101];

    printf("1. Customer\n");
    printf("2. Owner\n");
    printf("Choose Your Mode: ");
    scanf("%d", &login);
    printf("\n");

    if (login == 1)
    {
        chooseCinema(provinceAndCode, locationAndCodeAndNum);
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
            owner(provinceAndCode, locationAndCodeAndNum);
        }
    }

    return 0;
}