#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Owner
struct food {
    char name[50];
    int stock;
    int price;
    struct food *next;
};

struct beverage {
    char name[50];
    int stock;
    int price;
    struct beverage *next;
};

struct food *food_head = NULL;
struct beverage *drink_head = NULL;

void addfood(struct food *snack, int n) {
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
        struct food *new_food = (struct food*)malloc(sizeof(struct food));
        printf("Name: ");
        scanf("%49s", new_food->name);
        printf("Stock: ");
        scanf("%d", &new_food->stock);
        printf("Price: ");
        scanf("%d", &new_food->price);
        
        new_food->next = food_head;
        food_head = new_food;
        
        fprintf(pick, "%s#%d#%d\n", new_food->name, new_food->stock, new_food->price);
    }
    fclose(pick);
}

void addbev(struct beverage *drink, int n) {
    FILE *beverage = fopen("beverage.txt", "a");
    if (beverage == NULL) {
        printf("Error.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        struct beverage *new_drink = (struct beverage*)malloc(sizeof(struct beverage));
        printf("Drink: ");
        scanf("%49s", new_drink->name);
        printf("Quantity: ");
        scanf("%d", &new_drink->stock);
        printf("Price: ");
        scanf("%d", &new_drink->price);
        
        new_drink->next = drink_head;
        drink_head = new_drink;
        
        fprintf(beverage, "%s#%d#%d\n", new_drink->name, new_drink->stock, new_drink->price);
    }
    fclose(beverage);
}

void checkinventory(struct food *snack, struct beverage *drink) {
    char merk[100];
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
    

void changepricestock(struct food *snack, struct beverage *drink, int n) {
    int newprice, newstock, choice;
    char merk[100];
    printf("Choice:\n");
    printf("1. Food\n");
    printf("2. Beverage\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
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

        FILE *pick = fopen(file, "r");
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
            } else {
                free(food);
            }
        }
        fclose(pick);

        printf("Name: ");
        scanf("%49s", merk);

        struct food *temp = head;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->name, merk) == 0) {
                printf("What do you want to change?\n");
                printf("1. Change Price\n");
                printf("2. Add Stock\n");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    temp->price = newprice;
                } else if (choice == 2) {
                    printf("Input added stock quantity: ");
                    scanf("%d", &newstock);
                    temp->stock += newstock;
                }
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Item not found in %s.\n", file);
        } else {
            pick = fopen(file, "w");
            if (!pick) {
                printf("Error.\n");
                return;
            }

            struct food *current = head;
            while (current != NULL) {
                fprintf(pick, "%s#%d#%d\n", current->name, current->stock, current->price);
                current = current->next;
            }
            fclose(pick);
            printf("Data updated successfully.\n");
        }

        while (head != NULL) {
            struct food *trash = head;
            head = head->next;
            free(trash);
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

        printf("Beverage: ");
        scanf("%49s", merk);

        struct beverage *temp = head;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->name, merk) == 0) {
                printf("What do you want to change?\n");
                printf("1. Change Price\n");
                printf("2. Add Stock\n");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("Input the new price: ");
                    scanf("%d", &newprice);
                    temp->price = newprice;
                } else if (choice == 2) {
                    printf("Input new stock quantity: ");
                    scanf("%d", &newstock);
                    temp->stock += newstock;
                }
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Item not found in beverage.txt.\n");
        } else {
            FILE *beverage_write = fopen("beverage.txt", "w");
            if (!beverage_write) {
                printf("Error: Could not open beverage.txt for writing.\n");
                return;
            }

            struct beverage *current = head;
            while (current != NULL) {
                fprintf(beverage_write, "%s#%d#%d\n", current->name, current->stock, current->price);
                current = current->next;
            }
            fclose(beverage_write);
            printf("Data updated successfully.\n");
        }

        while (head != NULL) {
            struct beverage *trash = head;
            head = head->next;
            free(trash);
        }
    }
}

void printinventory(struct food *snack, struct beverage *drink) {
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

        printf("================================\n");
        printf("               Menu             \n");
        printf("================================\n");

        while (!feof(pick)) {
            struct food *food = (struct food *)malloc(sizeof(struct food));
            if (fscanf(pick, "%[^#]#%d#%d\n", food->name, &food->stock, &food->price) == 3) {
                printf("Food    : %s\n", food->name);
                printf("Stock   : %d\n", food->stock);
                printf("Price   : %d\n", food->price);
                printf("================================\n");
            }
            free(food);
        }
        fclose(pick);
    } else if (choice == 2) {
        FILE *beverage_file = fopen("beverage.txt", "r");
        if (!beverage_file) {
            printf("Error: Could not open beverage.txt.\n");
            return;
        }

        printf("================================\n");
        printf("               Menu             \n");
        printf("================================\n");

        while (!feof(beverage_file)) {
            struct beverage *beverage = (struct beverage *)malloc(sizeof(struct beverage));
            if (fscanf(beverage_file, "%[^#]#%d#%d\n", beverage->name, &beverage->stock, &beverage->price) == 3) {
                printf("Beverage: %s\n", beverage->name);
                printf("Stock   : %d\n", beverage->stock);
                printf("Price   : %d\n", beverage->price);
                printf("================================\n");
            }
            free(beverage);
        }
        fclose(beverage_file);
    } else {
        printf("Invalid choice.\n");
    }
}
// User 
struct item {
    struct food buyfood;
    struct beverage buydrink;
    int fquantitiy;
    int bquantitiy;
    int fprice;
    int bprice;
    struct item *next;
};

struct cart {
    struct item *items;
    int carttop;
};


void buybev(struct cart *buy, struct beverage *drink) {
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

    int bev_id, quan;
    printf("Enter beverage ID: ");
    scanf("%d", &bev_id);
    printf("Enter quantity: ");
    if (scanf("%d", &quan) != 1 || quan <= 0) {
        printf("Invalid quantity entered.\n");
        return;
    }

    struct beverage *temp = head;
    int drink_id = 1, found = 0;
    while (temp != NULL) {
        if (drink_id == bev_id) {
            found = 1;
            if (temp->stock < quan) {
                printf("Sorry, we only have %d in stock.\n", temp->stock);
                return;
            }
            temp->stock -= quan;

            struct item *new_drink = malloc(sizeof(struct item));
            if (!new_drink) {
                printf("Memory allocation failed.\n");
                return;
            }

            strcpy(new_drink->buydrink.name, temp->name);
            new_drink->bquantitiy = quan;
            new_drink->bprice = quan * temp->price;
            new_drink->next = buy->items;
            buy->items = new_drink;
            buy->carttop++;
            break;
        }
        temp = temp->next;
        drink_id++;
    }

    if (!found) {
        printf("Invalid beverage ID.\n");
        return;
    }

    FILE *beverage_write = fopen("beverage.txt", "w");
    if (!beverage_write) {
        printf("Error.\n");
        return;
    }

    temp = head;
    while (temp != NULL) {
        fprintf(beverage_write, "%s#%d#%d\n", temp->name, temp->stock, temp->price);
        temp = temp->next;
    }
    fclose(beverage_write);

    printf("'%s' added to cart successfully.\n", head->name);

    while (head != NULL) {
        struct beverage *trash = head;
        head = head->next;
        free(trash);
    }
}

void buyfood(struct cart *buy, struct food *snack) {
    FILE *pick = NULL;
    printf("Category:\n");
    printf("1. Popcorn\n");
    printf("2. Fritters\n");
    printf("3. Light meal\n");
    printf("4. Bakery\n");
    printf("Choice: ");
    int choice;
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

    struct food *head = NULL;
    while (!feof(pick)) {
        struct food *food = (struct food *)malloc(sizeof(struct food));
        if (fscanf(pick, "%[^#]#%d#%d\n", food->name, &food->stock, &food->price) == 3) {
            food->next = head;
            head = food;
        } else {
            free(food);
        }
    }
    fclose(pick);

    struct food *show = head;
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

    int food_id, quan;
    printf("Enter food ID: ");
    scanf("%d", &food_id);
    printf("Enter quantity: ");
    if (scanf("%d", &quan) != 1 || quan <= 0) {
        printf("Invalid quantity entered.\n");
        return;
    }

    struct food *temp = head;
    int found = 0;
    id = 1;
    while (temp != NULL) {
        if (id == food_id) {
            found = 1;
            if (temp->stock < quan) {
                printf("Sorry, we only have %d in stock.\n", temp->stock);
                return;
            }
            temp->stock -= quan;

            struct item *new_food = malloc(sizeof(struct item));
            if (!new_food) {
                printf("Memory allocation failed.\n");
                return;
            }

            strcpy(new_food->buyfood.name, temp->name);
            new_food->fquantitiy = quan;
            new_food->fprice = quan * temp->price;
            new_food->next = buy->items;
            buy->items = new_food;
            buy->carttop++;
            break;
        }
        temp = temp->next;
        id++;
    }

    if (!found) {
        printf("Invalid food ID.\n");
        return;
    }

    FILE *food_write = fopen(file, "w");
    if (!food_write) {
        printf("Error.");
        return;
    }

    temp = head;
    while (temp != NULL) {
        fprintf(food_write, "%s#%d#%d\n", temp->name, temp->stock, temp->price);
        temp = temp->next;
    }
    fclose(food_write);

    printf("'%s' added to cart successfully.\n", head->name);

    while (head != NULL) {
        struct food *trash = head;
        head = head->next;
        free(trash);
    }
}

void seecart(struct cart buy) {
    if (buy.carttop == -1 || buy.items == NULL) {
        printf("\nCart is empty\n");
        return;
    }

    printf("===================================================================\n");
    printf("                               Cart                                \n");
    printf("===================================================================\n");

    struct item *temp = buy.items;
    while (temp != NULL) {
        if (temp->fquantitiy > 0) {
            printf("Food    : %-15s  Quantity: %-5d  Total: %-5d\n", temp->buyfood.name, temp->fquantitiy, temp->fprice);
        }
        if (temp->bquantitiy > 0) {
            printf("Beverage: %-15s  Quantity: %-5d  Total: %-5d\n", temp->buydrink.name, temp->bquantitiy, temp->bprice);
        }
        temp = temp->next;
    }
    printf("===================================================================\n");
}

void changequantity(struct cart *buy) {
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

        struct item *temp = buy->items;
        while (temp != NULL) {
            if (strcmp(temp->buyfood.name, name) == 0 && temp->fquantitiy > 0) {
                printf("Current quantity: %d\n", temp->fquantitiy);
                printf("Enter new quantity: ");
                scanf("%d", &newquan);

                if (newquan <= 0) {
                    printf("Invalid quantity. Quantity must be greater than zero.\n");
                    return;
                }

                temp->fprice = (temp->fprice / temp->fquantitiy) * newquan;
                temp->fquantitiy = newquan; 
                printf("Food quantity updated successfully.\n");
                return;
            }
            temp = temp->next;
        }

        printf("Food item '%s' not found in cart.\n", name);

    } else if (choice == 2) {
        printf("Enter beverage name to change quantity: ");
        scanf("%49s", name);

        struct item *temp = buy->items;
        while (temp != NULL) {
            if (strcmp(temp->buydrink.name, name) == 0 && temp->bquantitiy > 0) {
                printf("Current quantity: %d\n", temp->bquantitiy);
                printf("Enter new quantity: ");
                scanf("%d", &newquan);

                if (newquan <= 0) {
                    printf("Invalid quantity. Quantity must be greater than zero.\n");
                    return;
                }

                temp->bprice = (temp->bprice / temp->bquantitiy) * newquan;
                temp->bquantitiy = newquan; 
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

void deletebyname(struct cart *buy) {
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

        struct item *temp = buy->items, *prev = NULL;

        while (temp != NULL) {
            if (strcmp(temp->buyfood.name, name) == 0 && temp->fquantitiy > 0) {
                if (prev == NULL) {
                    buy->items = temp->next; 
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                buy->carttop--;
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

        struct item *temp = buy->items, *prev = NULL;

        while (temp != NULL) {
            if (strcmp(temp->buydrink.name, name) == 0 && temp->bquantitiy > 0) {
                if (prev == NULL) {
                    buy->items = temp->next; 
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                buy->carttop--;
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

int main() {
    int j, choice;
    struct cart buy = {.items = NULL, .carttop = -1};

    printf("Select Option: \n");
    printf("1. Owner\n");
    printf("2. User\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
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

            switch (choice) {
                case 1:
                    printf("Enter number of food: ");
                    scanf("%d", &j);
                    addfood(food_head, j);
                    break;
                case 2:
                    printf("Enter number of beverage: ");
                    scanf("%d", &j);
                    addbev(drink_head, j);
                    break;
                case 3:
                    printinventory(food_head, drink_head);
                    break;
                case 4:
                    changepricestock(food_head, drink_head, 0);
                    break;
                case 5:
                    checkinventory(food_head, drink_head);
                    break;
                case 6:
                    printf("Exiting program.\n");

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

                    return 0;
                default:
                    printf("Invalid choice.\n");
            }
        }
    } else if (choice == 2) {
        while (1) {
            printf("Choice : \n");
            printf("1. Buy food\n");
            printf("2. Buy drinks\n");
            printf("3. See cart \n");
            printf("4. Change quantity\n");
            printf("5. Delete item\n");
            printf("6. Exit \n");
            printf("Choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    buyfood(&buy, food_head);
                    break;
                case 2:
                    buybev(&buy, drink_head);
                    break;
                case 3:
                    seecart(buy);
                    break;
                case 4:
                    changequantity(&buy);
                    break;
                case 5:
                    deletebyname(&buy);
                    break;
                case 6:
                    printf("Exiting program.\n");

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

                    buy.items = NULL;
                    buy.carttop = -1;
                    return 0;
                default:
                    printf("Invalid choice.\n");
            }
        }
    }

    return 0;
}