void seeCart(struct cart *buy)
{
    if (buy->cartTop == -1 || buy->items == NULL)
    {
        printf("\nCart is empty\n");
        return;
    }

    printf("===================================================================\n");
    printf("                               Cart                                \n");
    printf("===================================================================\n");

    struct item *temp = buy->items;
    while (temp != NULL)
    {
        if (temp->fQuantity > 0)
        {
            printf("Food    : %-15s  Quantity: %-5d  Total: %-5d\n", temp->buyFood.name, temp->fQuantity, temp->fPrice);
        }
        if (temp->bQuantity > 0)
        {
            printf("Beverage: %-15s  Quantity: %-5d  Total: %-5d\n", temp->buyDrink.name, temp->bQuantity, temp->bPrice);
        }
        temp = temp->next;
    }
    printf("===================================================================\n");
}