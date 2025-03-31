#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//owner
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
        printf("Stock: ");
        scanf("%d", &snack[i].stock);
        printf("Price: ");
        scanf("%d", &snack[i].price);
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
        printf("Quantity: ");
        scanf("%d", &drink[i].stock);
        printf("Price: ");
        scanf("%d", &drink[i].price);
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
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    snack[i].price = newprice;
                } else if (choice == 2) {
                    printf("Input added stock quantity: ");
                    scanf("%d", &newstock);
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
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    drink[i].price = newprice;
                } else if (choice == 2) {
                    printf("Input new stock quantity: ");
                    scanf("%d", &newstock);
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

void buybev(struct cart *buy, struct beverage drink[]) {
    int i, n = 1, id, quan;
    FILE *beverage = fopen("beverage.txt", "r");
    if (beverage == NULL) {
        printf("Error opening beverage file.\n");
        return;
    }

    printf("========================================\n");
    printf("                  Menu                  \n");
    printf("========================================\n");
    while (fscanf(beverage, "%[^#]#%d#%d\n", drink[n].name, &drink[n].stock, &drink[n].price) != EOF) {
        printf("%d.  %-10s : %-20s\n", n, "Drink", drink[n].name);
        printf("    %-10s : %-18d\n", "Price", drink[n].price);
        printf("========================================\n");
        n++;
    }
    fclose(beverage);

    printf("Enter id: ");
    scanf("%d", &id);
    printf("Enter quantity: ");
    scanf("%d", &quan);

    if (buy->carttop == MAX_CART - 1) {
        printf("Cart is full.\n");
        return;
    }

    if (id > 0 && id < n) {
        if (drink[id - 1].stock < quan) {
            printf("Sorry, this beverage is not available.\n");
            return;
        }

        buy->carttop++;
        strcpy(buy->items[buy->carttop].buydrink.name, drink[id - 1].name);
        buy->items[buy->carttop].bquantitiy = quan;
        buy->items[buy->carttop].bprice = quan * drink[id - 1].price;

        FILE *cart = fopen("cartbev.txt", "a");
        if (!cart) {
            printf("Error opening cart file.\n");
            return;
        }
        fprintf(cart, "%s#%d#%d\n", buy->items[buy->carttop].buydrink.name, buy->items[buy->carttop].bquantitiy, buy->items[buy->carttop].bprice);
        fclose(cart);

        drink[id - 1].stock -= quan;

        beverage = fopen("beverage.txt", "w");
        if (!beverage) {
            printf("Error opening beverage file for writing.\n");
            return;
        }
        for (int i = 0; i < n - 1; i++) {
            fprintf(beverage, "%s#%d#%d\n", drink[i].name, drink[i].stock, drink[i].price);
        }
        fclose(beverage);

        printf("Item added to cart successfully.\n");
    } else {
        printf("Invalid item ID.\n");
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
        printf("Error opening file.\n");
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
    printf("Enter quantity: ");
    scanf("%d", &quan);

    if (buy->carttop == MAX_CART - 1) {
        printf("Cart is full.\n");
        return;
    }

    if (id > 0 && id <= n) {
        if (snack[id - 1].stock < quan) {
            printf("Sorry, this food is not available.\n");
            return;
        }

        buy->carttop++;
        strcpy(buy->items[buy->carttop].buyfood.name, snack[id - 1].name);
        buy->items[buy->carttop].fquantitiy = quan;
        buy->items[buy->carttop].fprice = quan * snack[id - 1].price;

        FILE *cart = fopen("cartfood.txt", "a");
        if (!cart) {
            printf("Error opening cart file.\n");
            return;
        }
        fprintf(cart, "%s#%d#%d\n", buy->items[buy->carttop].buyfood.name, buy->items[buy->carttop].fquantitiy, buy->items[buy->carttop].fprice);
        fclose(cart);

        snack[id - 1].stock -= quan;

        pick = fopen(file, "w");
        if (!pick) {
            printf("Error opening file for writing.\n");
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
    int n = 0;
    int m = 0;
    FILE *cart1 = fopen("cartfood.txt", "r");
    if (cart1 == NULL || buy.carttop == -1) {
        printf("\nFood Cart is empty\n");
        return;
    }

    printf("===================================================================\n");
    printf("                               Cart                                \n");
    printf("===================================================================\n");
    printf("                               Food                                \n");
    printf("===================================================================\n");
    while (fscanf(cart1, "%[^#]#%d#%d\n", buy.items[n].buyfood.name, &buy.items[n].fquantitiy, &buy.items[n].fprice) != EOF) {
        printf("Food    : %-15s  Quantity: %-5d  Total: %-5d\n", buy.items[n].buyfood.name, buy.items[n].fquantitiy, buy.items[n].fprice);
        n++;
    }
    fclose(cart1);
    printf("===================================================================\n");

    FILE *cart2 = fopen("cartbev.txt", "r");
    if (cart2 == NULL || buy.carttop == -1) {
        printf("\nDrink cart is empty\n");
        return;
    }

    printf("===================================================================\n");
    printf("                               Drink                               \n");
    printf("===================================================================\n");
    while (fscanf(cart2, "%[^#]#%d#%d\n", buy.items[m].buydrink.name, &buy.items[m].bquantitiy, &buy.items[m].bprice) != EOF) {
        printf("Drink   : %-15s  Quantity: %-5d  Total: %-5d\n", buy.items[m].buydrink.name, buy.items[m].bquantitiy, buy.items[m].bprice);
        m++;
    }
    fclose(cart2);
    printf("===================================================================\n");
}

void emptycart(struct cart buy){
    FILE *cart1 = fopen("cartfood.txt", "w");
    if (cart1 != NULL) {
        fclose(cart1);
    }

    FILE *cart2 = fopen("cartbev.txt", "w");
    if (cart2 != NULL) {
        fclose(cart2);
    }

    buy.carttop = -1;
    printf("Cart has been emptied.\n");
}

void changequantity(struct cart buy) {
    int newquan, choice;
    char merk[100];
    printf("Choice:\n");
    printf("1. Food\n");
    printf("2. Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        FILE *change = fopen("cartfood.txt", "r");
        if (!change) {
            printf("Error opening food cart file.\n");
            return;
        }

        printf("Name: ");
        scanf("%49s", merk);

        int count = 0;
        while (fscanf(change, "%[^#]#%d#%d\n", buy.items[count].buyfood.name, &buy.items[count].fquantitiy, &buy.items[count].fprice) != EOF) {
            count++;
        }
        fclose(change);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(merk, buy.items[i].buyfood.name) == 0) {
                found = 1;
                printf("New quantity: ");
                scanf("%d", &newquan);
                buy.items[i].fquantitiy = newquan;
                buy.items[i].fprice = newquan * buy.items[i].fprice / buy.items[i].fquantitiy; 
                break;
            }
        }

        if (!found) {
            printf("Item not found.\n");
            return;
        }

        change = fopen("cartfood.txt", "w");
        if (!change) {
            printf("Error opening food cart file for writing.\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(change, "%s#%d#%d\n", buy.items[i].buyfood.name, buy.items[i].fquantitiy, buy.items[i].fprice);
        }
        fclose(change);
        printf("Food cart updated successfully.\n");

    } else if (choice == 2) {
        FILE *change = fopen("cartbev.txt", "r");
        if (!change) {
            printf("Error opening beverage cart file.\n");
            return;
        }

        printf("Name: ");
        scanf("%49s", merk);

        int count = 0;
        while (fscanf(change, "%[^#]#%d#%d\n", buy.items[count].buydrink.name, &buy.items[count].bquantitiy, &buy.items[count].bprice) != EOF) {
            count++;
        }
        fclose(change);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(merk, buy.items[i].buydrink.name) == 0) {
                found = 1;
                printf("New quantity: ");
                scanf("%d", &newquan);
                buy.items[i].bquantitiy = newquan;
                buy.items[i].bprice = newquan * buy.items[i].bprice / buy.items[i].bquantitiy; 
                break;
            }
        }

        if (!found) {
            printf("Item not found.\n");
            return;
        }

        change = fopen("cartbev.txt", "w");
        if (!change) {
            printf("Error opening beverage cart file for writing.\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(change, "%s#%d#%d\n", buy.items[i].buydrink.name, buy.items[i].bquantitiy, buy.items[i].bprice);
        }
        fclose(change);
        printf("Beverage cart updated successfully.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

int main() {
    int j, choice;
    struct food snack[100];
    struct beverage drink[100];
    struct cart buy = {.carttop = -1}; 

   
        printf("Select Option: \n");
        printf("1. Owner\n");
        printf("2. User\n");
        printf("Choice: ");
        scanf("%d", &choice);
    
        if (choice == 1) {
            while (1){
            printf("\nChoice : \n");
            printf("1. Add Food\n");
            printf("2. Add Beverage\n");
            printf("3. Print Inventory\n");
            printf("4. Change Stock and Price\n");
            printf("5. Check Inventory\n");
            printf("6. Exit\n"); 
            printf("Choice : ");
            scanf("%d", &choice);

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
        } else if (choice == 2) {
            while (1){
            printf("Choice : \n");
            printf("1. Buy food\n");
            printf("2. Buy drinks\n");
            printf("3. See cart \n");
            printf("4. Change quantity\n");
            printf("5. Empty cart\n");
            printf("6. Exit ");
            printf("Choice: ");
            scanf("%d", &choice);
            switch (choice){
                case 1:
                buyfood(&buy, snack);
                break;

                case 2:
                buybev(&buy, drink);
                break;

                case 3:
                seecart(buy);
                break;

                case 4:
                changequantity(buy);
                break;

                case 5:
                emptycart(buy);
                break;

                case 6:
                printf("Exiting program.\n");
                return 0;
                
                default:
                printf("Invalid choice.\n");

            }
         
        }
    }

    return 0;
}

