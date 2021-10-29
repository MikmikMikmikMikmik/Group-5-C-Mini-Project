#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test1.h"


typedef struct product{
    int productID;
    char productName[30];
    int productQuantity;
    char productExpiration[20];
    float productPrice;
}product;


void addItem() {
    product p1;
    FILE *fp, *fp2;
    
    if((fp = fopen("inventory.csv","r"))!=NULL)
    {
        printf("File Exist\n");
        fp = fopen("inventory.csv", "a"); 
        fp2 = fopen("inventoryBinary.csv", "ab"); 
    }
    else
    {
        printf("File doesnt Exist\n");
        fp = fopen("inventory.csv", "w");
        fp2 = fopen("inventoryBinary.csv", "wb");
    }
    
    if(fp == NULL) {
        printf("Cannot Open");
    }

    printf("Enter Product ID: ");
    scanf("%d", &p1.productID);
    fflush(stdin);

    printf("Enter Product Name: ");
    /* scanf("%[^\n]s",p1.productName); */
    gets(p1.productName);

    printf("Enter Product Quantity: ");
    scanf("%d", &p1.productQuantity);
    fflush(stdin);

    printf("Enter Product Expiration: ");
    /* scanf("%[^\n]s",p1.productExpiration); */
    gets(p1.productExpiration);

    printf("Enter Product Price: ");
    scanf("%f", &p1.productPrice);

    fwrite(&p1, sizeof(product), 1, fp2);
    if(fwrite!=0) {
        printf("Contents written in the file");
    }
    else {
        printf("error occured");
    }

    fprintf(fp, "%d,  %s,  %d,  %s,  %f\n", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);

    
    fclose(fp);
    fclose(fp2);
    
    return;
}

void viewAllProducts(){
    product p1;
    FILE *fp2;
    int j;
    char line[200];
    fp2 = fopen("inventoryBinary.csv", "rb");
    printf("Product ID\tDescription\tQuantity\tExp Date\tPrice");
    while(fread(&p1,sizeof(product),1,fp2))
    {
        printf("\n%-5d       %-20s      %d      %s      %f", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);
    }

    printf("\n\n");
    system("pause");

    fclose(fp2);
}

void viewInventory() {
    system("cls");
    char choice;
    printf("VIEW INVENTORY\n");
    printf("[A] View All\n");
    printf("[B] Search for an Inventory Item\n");
    printf("[C] Back to Menu\n");
    printf("Choice: ");
    
    fflush(stdin);
    scanf("%c", &choice);

    printf("%c", &choice);
    if(choice == 'A') {
       viewAllProducts();
    }
    else if(choice == 'B') {
        searchMenu();
    }   
    else if(choice == 'C')   {
        
    }
    
}

void searchByID() {
    system("cls");
    product p1;
    FILE *fp;
    int j, pId, found = 0;
    fp = fopen("inventoryBinary.csv", "rb");

    printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\n");
    printf("Enter Product ID to Search: ");
    scanf("%5d", &pId);
    
    while(fread(&p1,sizeof(product),1,fp))
    {
        if(p1.productID == pId){
            found = 1;
            printf("\nProduct ID\tDescription\tQuantity\tExp Date\tPrice");
            printf("\n%d\t%s\t%d\t%s\t%f", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);
        }
    }
    if(!found) {
        printf("\nItem ID does not exist!\n\n");
        system("pause");
        searchMenu();
    }

    
    printf("\n\n");
    system("pause");

    fclose(fp);
}

void searchByName() {
    system("cls");
    product p1;
    FILE *fp;
    int j, found = 0;
    char pName[30];
    fp = fopen("inventoryBinary.csv", "rb");

    printf("SEARCH FOR AN INVENTORY ITEM > by Item Name\n\n");
    printf("Enter Product Name to Search: ");
    fflush(stdin);
    scanf("%[^\n]s",pName);
    
    
    printf("Product ID\tDescription\tQuantity\tExp Date\tPrice");
    while(fread(&p1,sizeof(product),1,fp))
    {
        printf("%s", p1.productName);
        if(strcmp(p1.productName, pName) == 0 ){
            found = 1;
            printf("\n%-5d%-20s   %d   %s    %f", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);
        }
    }
    if(!found) {
        printf("\nItem ID does not exist!\n\n");
        system("pause");
        searchMenu();
    }

    printf("\n\n");
    system("pause");
    fclose(fp);
}

void searchMenu() {
    system("cls");
    char choice;
    printf("SEARCH FOR AN INVENTORY ITEM\n");
    printf("[A] SEARCH BY PRODUCT ID\n");
    printf("[B] SEARCH BY PRODUCT NAME/DESCRIPTION\n");
    printf("[C] BACK TO VIEW INVENTORY MENU\n");
    printf("\nPlease input choice: ");
    fflush(stdin);
    scanf("%c", &choice);

    printf("%c", &choice);
    if(choice == 'A') {
       searchByID();
    }
    else if(choice == 'B') {
        searchByName();
    }
    else if(choice == 'C') {
        viewInventory();
    }
    else {
        printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
}

int main() {
    char choice;

    printf("Inventory\n");
    printf("[A] Add Item to Inventory\n");
    printf("[B] Update Item to Inventory\n");
    printf("[C] View Item to Inventory\n");
    printf("[D] Delete Item to Inventory\n");
    printf("Choice: ");
    scanf("%c", &choice);

    printf("%c", &choice);
    if(choice == 'A') {
       addItem();
    }
    else if(choice == 'B') {
        
    }
    else if(choice == 'C') {
        viewInventory();
    }
    else if(choice == 'D') {
        
    }

    return 0;
}