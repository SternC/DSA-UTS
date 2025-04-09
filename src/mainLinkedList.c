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

void checkinventory(struct food *food_head, struct beverage *drink_head) {
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
    

void changepricestock(struct food *food_head, struct beverage *drink_head, int n) {
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

void printinventory(struct food *food_head, struct beverage *drink_head) {
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

// User 
void buybev(struct cart *buy, struct beverage *drink_head) {
    FILE *beverage_file = fopen("beverage.txt", "r");
    if (!beverage_file) {
        printf("Error: Could not open beverage.txt.\n");
        return;
    }

    drink_head = NULL;
    while (!feof(beverage_file)) {
        struct beverage *beverage = (struct beverage *)malloc(sizeof(struct beverage));
        if (fscanf(beverage_file, "%[^#]#%d#%d\n", beverage->name, &beverage->stock, &beverage->price) == 3) {
            beverage->next = drink_head;
            drink_head = beverage;
        } else {
            free(beverage);
        }
    }
    fclose(beverage_file);

    int total = 0;
    struct beverage *counter = drink_head;
    while (counter != NULL) {
        total++;
        counter = counter->next;
    }

    struct beverage *show = drink_head;
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

    int bev_id, quan;
    printf("Enter beverage ID: ");
    scanf("%d", &bev_id); getchar();
    printf("Enter quantity: ");
    if (scanf("%d", &quan) != 1 || quan <= 0) {
        printf("Invalid quantity entered.\n");
        return;
    }
    getchar();

    struct beverage *selected = drink_head;
    int current_id = total;
    while (selected != NULL && current_id != bev_id) {
        selected = selected->next;
        current_id--;
    }

    if (selected == NULL) {
        printf("Invalid beverage ID.\n");
        return;
    }

    if (selected->stock < quan) {
        printf("Sorry, we only have %d in stock.\n", selected->stock);
        return;
    }

    selected->stock -= quan;

    struct item *new_drink = malloc(sizeof(struct item));
    if (!new_drink) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_drink->fquantitiy = 0;
    new_drink->fprice = 0;
    strcpy(new_drink->buyfood.name, "");

    strcpy(new_drink->buydrink.name, selected->name);
    new_drink->bquantitiy = quan;
    new_drink->bprice = quan * selected->price;

    new_drink->next = buy->items;
    buy->items = new_drink;
    buy->carttop++;

    FILE *beverage_write = fopen("beverage.txt", "w");
    if (!beverage_write) {
        printf("Error: Could not write to beverage.txt\n");
        return;
    }

    struct beverage *current = drink_head;
    while (current != NULL) {
        fprintf(beverage_write, "%s#%d#%d\n", current->name, current->stock, current->price);
        current = current->next;
    }
    fclose(beverage_write);

    printf("'%s' added to cart successfully.\n", selected->name);
}


void buyfood(struct cart *buy, struct food *food_head) {
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

    food_head = NULL;
    while (!feof(pick)) {
        struct food *new_food = malloc(sizeof(struct food));
        if (fscanf(pick, "%[^#]#%d#%d\n", new_food->name, &new_food->stock, &new_food->price) == 3) {
            new_food->next = food_head;
            food_head = new_food;
        } else {
            free(new_food);
        }
    }
    fclose(pick);

    int total = 0;
    struct food *counter = food_head;
    while (counter != NULL) {
        total++;
        counter = counter->next;
    }

    struct food *show = food_head;
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

    int food_id, quan;
    printf("Enter food ID: ");
    scanf("%d", &food_id); getchar();
    printf("Enter quantity: ");
    if (scanf("%d", &quan) != 1 || quan <= 0) {
        printf("Invalid quantity entered.\n");
        return;
    }
    getchar();

    struct food *selected = food_head;
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

    selected->stock -= quan;

    struct item *new_food = malloc(sizeof(struct item));
    if (!new_food) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_food->bquantitiy = 0;
    new_food->bprice = 0;
    strcpy(new_food->buydrink.name, "");

    strcpy(new_food->buyfood.name, selected->name);
    new_food->fquantitiy = quan;
    new_food->fprice = quan * selected->price;

    new_food->next = buy->items;
    buy->items = new_food;
    buy->carttop++;

    FILE *food_write = fopen(file, "w");
    if (!food_write) {
        printf("Error writing to file.\n");
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
         
            if (temp->fquantitiy > 0 && strlen(temp->buyfood.name) > 0) {
                printf("Food    : %-15s  Quantity: %-5d  Total: %-5d\n",
                       temp->buyfood.name, temp->fquantitiy, temp->fprice);
            }
    
        
            if (temp->bquantitiy > 0 && strlen(temp->buydrink.name) > 0) {
                printf("Beverage: %-15s  Quantity: %-5d  Total: %-5d\n",
                       temp->buydrink.name, temp->bquantitiy, temp->bprice);
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
                printf("Food item \"%s\" deleted successfully from cart.\n", name);
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
    struct food *food_head = NULL;
    struct beverage *drink_head = NULL;

    printf("Select Option: \n");
    printf("1. Owner\n");
    printf("2. User\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar(); 

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
            getchar(); 

            switch (choice) {
                case 1:
                    printf("Enter number of food: ");
                    scanf("%d", &j);
                    getchar(); 
                    addfood(&food_head, j);
                    break;
                case 2:
                    printf("Enter number of beverage: ");
                    scanf("%d", &j);
                    getchar();
                    addbev(&drink_head, j);
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
            getchar(); 

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