#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Unix/Linux/Mac
    #endif
}

struct food {
    char name[50];
    int stock;
    int price;
};

struct beverage {
    char name[50];
    int stock;
    int price;
};

void deleteAllLocationAndProvince(int *counterProv, int *counterLoc, char provinceAndCode[100][2][101], char locationAndCodeAndNum[100][3][101])
{
    for (int i = 0; i < 100; i++)
    {
        strcpy(provinceAndCode[i][0], "");
        strcpy(provinceAndCode[i][1], "");
    }

    for (int i = 0; i < 100; i++)
    {
        strcpy(locationAndCodeAndNum[i][0], "");
        strcpy(locationAndCodeAndNum[i][1], "");
        strcpy(locationAndCodeAndNum[i][2], "");
    }

    *counterProv = 0;
    *counterLoc = 0;
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
    fprintf(cinLocFile, "%s#%s#%d\n", newLocation, provinceCode, newNum + 1);
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
            printf("%s. %s\n", locationAndCodeAndNum[i][2], locationAndCodeAndNum[i][0]);
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

void owner()
{
    int userActivity;
    int counterProv, counterLoc, counter;

    char provinceAndCode[100][2][101];
    char locationAndCodeAndNum[100][3][101];

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
            deleteAllLocationAndProvince(&counterProv, &counterLoc, provinceAndCode, locationAndCodeAndNum);
            return;
        }
        deleteAllLocationAndProvince(&counterProv, &counterLoc, provinceAndCode, locationAndCodeAndNum);
    }
}

void chooseCinema()
{
    char userProv[101], userCinema[101];
    int counterProv, counterLoc, counter;

    char provinceAndCode[100][2][101];
    char locationAndCodeAndNum[100][3][101];

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

void addfood(struct food snack[], int n) {
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
        printf("Name: ");
        scanf("%49s", snack[i].name); 
        getchar(); 
        printf("Stock: ");
        scanf("%d", &snack[i].stock);
        getchar(); 
        printf("Price: ");
        scanf("%d", &snack[i].price);
        getchar();
        fprintf(pick, "%s#%d#%d\n", snack[i].name, snack[i].stock, snack[i].price);
    }
    fclose(pick);
}

void addbev(struct beverage drink[], int n) {
    FILE *beverage = fopen("beverage.txt", "a");
    if (beverage == NULL) {
        printf("Error.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("Drink: ");
        scanf("%49s", drink[i].name); 
        getchar(); 
        printf("Quantity: ");
        scanf("%d", &drink[i].stock);
        getchar();
        printf("Price: ");
        scanf("%d", &drink[i].price);
        getchar(); 
        fprintf(beverage, "%s#%d#%d\n", drink[i].name, drink[i].stock, drink[i].price); 
    }
    fclose(beverage);
}

void checkinventory(struct food snack[], struct beverage drink[]) {
    char merk[100];
    int n = 0;
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
                file= "popcorn.txt";
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
            printf("Error.\n");
            return;
        }

        printf("Name: ");
        scanf("%49s", merk);
        getchar();

        while (fscanf(pick, "%[^#]#%d#%d\n", snack[n].name, &snack[n].stock, &snack[n].price) != EOF) {
            if (strcmp(merk, snack[n].name) == 0) {
                printf("================================\n");
                printf("Food    : %s\n", snack[n].name);
                printf("Stock   : %d\n", snack[n].stock);
                printf("Price   : %d\n", snack[n].price);
                printf("================================\n");
            }
            n++;
        }
        fclose(pick);

    } else if (choice == 2) {
        printf("Beverage: ");
        scanf("%99s", merk); 
        getchar(); 
        FILE *beverage = fopen("beverage.txt", "r");
        if (!beverage) {
            printf("Error.\n");
            return;
        }

        while (fscanf(beverage, "%[^#]#%d#%d\n", drink[n].name, &drink[n].stock, &drink[n].price) != EOF) {
            if (strcmp(merk, drink[n].name) == 0) {
                printf("================================\n");
                printf("Beverage: %s\n", drink[n].name);
                printf("Stock   : %d\n", drink[n].stock);
                printf("Price   : %d\n", drink[n].price);
                printf("================================\n");
            }
            n++;
        }
        fclose(beverage);
    }
}

void changepricestock(struct food snack[], struct beverage drink[], int n) {
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
                file= "popcorn.txt";
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
            printf("Error.\n");
            return;
        }

        printf("Name: ");
        scanf("%49s", merk);
        getchar(); 

        int count = 0;
        while (fscanf(pick, "%[^#]#%d#%d\n", snack[count].name, &snack[count].stock, &snack[count].price) != EOF) {
            count++;
        }
        fclose(pick);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(merk, snack[i].name) == 0) {
                found = 1;
                printf("What do you want to change?\n");
                printf("1. Change Price\n");
                printf("2. Add Stock\n");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    getchar(); 
                    snack[i].price = newprice;
                } else if (choice == 2) {
                    printf("Input added stock quantity: ");
                    scanf("%d", &newstock);
                    getchar(); 
                    snack[i].stock += newstock;
                }
                break;
            }
        }

        if (!found) {
            printf("Item not found.\n");
            return;
        }

        pick = fopen(file, "w");
        if (!pick) {
            printf("Error.\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(pick, "%s#%d#%d\n", snack[i].name, snack[i].stock, snack[i].price);
        }
        fclose(pick);
        printf("Data updated successfully.\n");

        


    } else if (choice == 2) {
        printf("Beverage: ");
        scanf("%99s", merk); 
        getchar(); 
        FILE *beverage = fopen("beverage.txt", "r");
        if (!beverage) {
            printf("Error.\n");
            return;
        }

        int count = 0;
        while (fscanf(beverage, "%[^#]#%d#%d\n", drink[count].name, &drink[count].stock, &drink[count].price) != EOF) {
            count++;
        }
        fclose(beverage);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(merk, drink[i].name) == 0) {
                found = 1;
                printf("What do you want to change?\n");
                printf("1. Change Price\n");
                printf("2. Add Stock\n");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    getchar(); 
                    drink[i].price = newprice;
                } else if (choice == 2) {
                    printf("Input new stock quantity: ");
                    scanf("%d", &newstock);
                    getchar();
                    drink[i].stock += newstock;
                }
                break; 
            }
        }

        if (!found) {
            printf("Item not found.\n");
            return;
        }

        beverage = fopen("beverage.txt", "w");
        if (!beverage) {
            printf("Error.\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(beverage, "%s#%d#%d\n", drink[i].name, drink[i].stock, drink[i].price);
        }
        fclose(beverage);
        printf("Data updated successfully.\n");
    }
}

void printinventory(struct food snack[], struct beverage drink[]) {
    int i, n = 0; 
    printf("Choice:\n");
    printf("1. Food inventory\n");
    printf("2. Beverage inventory\n");
    printf("Choice: ");
    scanf("%d", &i);

    if (i == 1) {
        FILE *pick = NULL;
        printf("Category:\n");
        printf("1. Popcorn\n");
        printf("2. Fritters\n");
        printf("3. Light meal\n");
        printf("4. Bakery\n");
        printf("Choice: ");
        scanf("%d", &i);

        char *file = NULL;
        switch (i) {
            case 1:
                file= "popcorn.txt";
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
            printf("Error.\n");
            return;
        }

        printf("================================\n");
        printf("            Inventory           \n");
        printf("================================\n");
        while (fscanf(pick, "%[^#]#%d#%d\n", snack[n].name, &snack[n].stock, &snack[n].price) != EOF) {
            printf("Food    : %s\n", snack[n].name);
            printf("Stock   : %d\n", snack[n].stock);
            printf("Price   : %d\n", snack[n].price);
            printf("================================\n");
            n++;
        }
        fclose(pick);
        
    } else if (i == 2) {
        FILE *beverage = fopen("beverage.txt", "r");
        if (beverage == NULL) {
            printf("Error.\n");
            return;
        }
        printf("================================\n");
        printf("            Inventory           \n");
        printf("================================\n");
        while (fscanf(beverage, "%[^#]#%d#%d\n", drink[n].name, &drink[n].stock, &drink[n].price) != EOF) {
            printf("Beverage: %s\n", drink[n].name); 
            printf("Stock   : %d\n", drink[n].stock);
            printf("Price   : %d\n", drink[n].price);
            printf("================================\n");
            n++;
        }
        fclose(beverage);
    }
}

//User
#define MAX_CART 100

struct item{
   struct food buyfood;
   struct beverage buydrink;
   int fquantitiy;
   int bquantitiy;
   int fprice;
   int bprice;
};

struct cart{
    struct item items[MAX_CART];
    int carttop;
};

    void buybev(struct cart *buy, struct beverage drink[] ) {
        int i, n = 0, id, quan;  // Start with n=0
        FILE *beverage = fopen("beverage.txt", "r");
        if (beverage == NULL) {
            printf("Error opening beverage file.\n");
            return;
        }
    
        printf("========================================\n");
        printf("                  Menu                  \n");
        printf("========================================\n");
        
        
        while (fscanf(beverage, "%49[^#]#%d#%d\n", 
               drink[n].name, &drink[n].stock, &drink[n].price) == 3) {
            printf("%d.  %-10s : %-20s\n", n+1, "Drink", drink[n].name);
            printf("    %-10s : %-18d\n", "Price", drink[n].price);
            printf("========================================\n");
            n++;
        }
        fclose(beverage);
    
        printf("Enter id: ");
        scanf("%d", &id);
        getchar(); 
        printf("Enter quantity: ");
        scanf("%d", &quan);
        getchar(); 
    
        if (buy->carttop == MAX_CART - 1) {
            printf("Cart is full.\n");
            return;
        }
    
        
        if (id > 0 && id <= n) { 
            if (drink[id-1].stock < quan) {
                printf("Sorry, we only have %d in stock.\n", drink[id-1].stock);
                return;
            }
    
            buy->carttop++;
            strcpy(buy->items[buy->carttop].buydrink.name, drink[id-1].name);
            buy->items[buy->carttop].bquantitiy = quan;
            buy->items[buy->carttop].bprice = quan * drink[id-1].price;
    
        
            drink[id-1].stock -= quan;
    
            beverage = fopen("beverage.txt", "w");
            if (!beverage) {
                printf("Error saving changes.\n");
                return;
            }
            for (i = 0; i < n; i++) {  
                fprintf(beverage, "%s#%d#%d\n", drink[i].name, drink[i].stock, drink[i].price);
            }
            fclose(beverage);
    
            printf("'%s' added to cart successfully.\n", drink[id-1].name);
        } else {
            printf("Invalid item ID. Please choose 1-%d.\n", n);
        }
    }

void buyfood(struct cart *buy, struct food snack[]) {
    int i, n = 0, id, quan;
    FILE *pick = NULL;
    printf("Category:\n");
    printf("1. Popcorn\n");
    printf("2. Fritters\n");
    printf("3. Light meal\n");
    printf("4. Bakery\n");
    printf("Choice: ");
    scanf("%d", &i);
    getchar(); 

    const char *file = NULL;
    switch (i) {
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
        printf("Error.\n");
        return;
    }

    printf("========================================\n");
    printf("                  Menu                  \n");
    printf("========================================\n");
    while (fscanf(pick, "%[^#]#%d#%d\n", snack[n].name, &snack[n].stock, &snack[n].price) != EOF) {
        printf("%d.  %-10s : %-20s\n", n + 1, "Food", snack[n].name);
        printf("    %-10s : %-18d\n", "Price", snack[n].price);
        printf("========================================\n");
        n++;
    }
    fclose(pick);

    printf("Enter id: ");
    scanf("%d", &id);
    getchar(); 
    printf("Enter quantity: ");
    scanf("%d", &quan);
    getchar();

    if (buy->carttop == MAX_CART - 1) {
        printf("Cart is full.\n");
        return;
    }

    if (id > 0 && id <= n) {
        if (snack[id - 1].stock < quan) {
            printf("Sorry, we only have %d in stock.\n", snack[id - 1].stock);
            return;
        }

        buy->carttop++;
        strcpy(buy->items[buy->carttop].buyfood.name, snack[id - 1].name);
        buy->items[buy->carttop].fquantitiy = quan;
        buy->items[buy->carttop].fprice = quan * snack[id - 1].price;

        snack[id - 1].stock -= quan;

        pick = fopen(file, "w");
        if (!pick) {
            printf("Error.\n");
            return;
        }
        for (int i = 0; i < n; i++) {
            fprintf(pick, "%s#%d#%d\n", snack[i].name, snack[i].stock, snack[i].price);
        }
        fclose(pick);

        printf("Item added to cart successfully.\n");
    } else {
        printf("Invalid item ID.\n");
    }
}

void seecart(struct cart buy) {
    if (buy.carttop == -1) {
        printf("\nCart is empty\n");
        return;
    }

    printf("===================================================================\n");
    printf("                               Cart                                \n");
    printf("===================================================================\n");
    for (int i = 0; i <= buy.carttop; i++) {
        if (buy.items[i].fquantitiy > 0) {
            printf("Food    : %-15s  Quantity: %-5d  Total: %-5d\n", buy.items[i].buyfood.name, buy.items[i].fquantitiy, buy.items[i].fprice);
        }
        if (buy.items[i].bquantitiy > 0) {
            printf("Drink   : %-15s  Quantity: %-5d  Total: %-5d\n", buy.items[i].buydrink.name, buy.items[i].bquantitiy, buy.items[i].bprice);
        }
    }
    printf("===================================================================\n");
}


void changequantity(struct cart *buy) {
    int newquan, choice;
    char merk[100];
    printf("Choice:\n");
    printf("1. Food\n");
    printf("2. Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);

    printf("Name: ");
    scanf("%49s", merk);

    int found = 0;
    for (int i = 0; i <= buy->carttop; i++) {
        if (choice == 1 && strcmp(merk, buy->items[i].buyfood.name) == 0) {
            printf("New quantity: ");
            scanf("%d", &newquan);
            buy->items[i].fprice = (buy->items[i].fprice / buy->items[i].fquantitiy) * newquan;
            buy->items[i].fquantitiy = newquan;
            found = 1;
            break;
        } else if (choice == 2 && strcmp(merk, buy->items[i].buydrink.name) == 0) {
            printf("New quantity: ");
            scanf("%d", &newquan);
            buy->items[i].bprice = (buy->items[i].bprice / buy->items[i].bquantitiy) * newquan;
            buy->items[i].bquantitiy = newquan;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found in cart.\n");
    } else {
        printf("Cart updated successfully.\n");
    }
}

void deletebyname(struct cart *buy) {
    int choice;
    char name[50];
    printf("Choice:\n");
    printf("1. Delete Food\n");
    printf("2. Delete Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);

    printf("Enter name to delete: ");
    scanf("%49s", name);

    int found = 0;
    for (int i = 0; i <= buy->carttop; i++) {
        if (choice == 1 && strcmp(buy->items[i].buyfood.name, name) == 0 && buy->items[i].fquantitiy > 0) {
            for (int j = i; j < buy->carttop; j++) {
                buy->items[j] = buy->items[j + 1];
            }
            buy->carttop--;
            found = 1;
            printf("Food item '%s' deleted successfully from cart.\n", name);
            break;
        } else if (choice == 2 && strcmp(buy->items[i].buydrink.name, name) == 0 && buy->items[i].bquantitiy > 0) {
            for (int j = i; j < buy->carttop; j++) {
                buy->items[j] = buy->items[j + 1];
            }
            buy->carttop--;
            found = 1;
            printf("Beverage item '%s' deleted successfully from cart.\n", name);
            break;
        }
    }

    if (!found) {
        printf("Item '%s' not found in cart.\n", name);
    }
}

void foodModification(){

    int choice = 0;
    int j;
    struct food snack[100];
    struct beverage drink[100];
    struct cart buy = {.carttop = -1};

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
            addfood(snack, j);
            break;

        case 2:
            printf("Enter number of beverage: ");
            scanf("%d", &j);
            addbev(drink, j);
            break;

        case 3:
            printinventory(snack, drink);
            break;

        case 4:
            changepricestock(snack, drink, 100);
            break;

        case 5:
            checkinventory(snack, drink);
            break; 

        case 6:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
    }
}


int main(){

    int choice = 0;
    int choice2 = 0;
    int attempt = 0;
    int ownerSelection = 0;
    char correctUsername[] = {"admin"}, inputtedUsername[50];
    char correctPassword[] = {"admin"}, inputtedPassword[50];

    while(choice != 3){
        printf("Select Option: \n");
        printf("1. Owner\n");
        printf("2. User\n");
        printf("3. Exit");
        printf("Selection: ");

        scanf("%d", &choice);
        
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
                while (ownerSelection != 4){

                    printf("Select your categories: \n");
                    printf("1. Location modification\n");
                    printf("2. Movie list modification\n");
                    printf("3. Food list modification\n");
                    printf("4. Exit");
                    printf("Selection: ");
                    scanf("%d", &ownerSelection);

                    if (ownerSelection == 1){
                        owner();
                    }
                    else if (ownerSelection == 2){
                        //Punya feli
                    }
                    else if (ownerSelection == 3){
                        foodModification();
                    }
                }

            }
            
        }
        else if (choice == 2){
            printf("Please select your location\n");
            chooseCinema();

            while (choice2 != 3){
                // Reserved for Cinema Location Printing
                printf("Select your category: \n");
                printf("1. Select movie\n");
                printf("2. Order food\n");
                printf("3. Exit");

                if (choice2 == 1){
                    //Buat punya feli
                }

                else if (choice2 == 2){
                    // Buat michi
                }
                else if (choice2 == 3){
                    break;
                }
            }


        }
        
    }

    return 0;
}