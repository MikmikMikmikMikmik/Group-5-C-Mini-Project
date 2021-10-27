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
    FILE *fp;
    if((fp = fopen("inventory.txt","r"))!=NULL)
    {
        printf("File Exist\n");
        fp = fopen("inventory.txt", "a"); 
    }
    else
    {
        printf("File doesnt Exist\n");
        fp = fopen("inventory.txt", "w");
    }
    
    if(fp == NULL) {
        printf("Cannot Open");
    }

    printf("Enter Product ID: ");
    scanf("%d", &p1.productID);
    fflush(stdin);
    printf("Enter Product Name: ");
    scanf("%[^\n]s",p1.productName);
    /* gets(p1.productName); */
    printf("Enter Product Quantity: ");
    scanf("%d", &p1.productQuantity);
    fflush(stdin);
    printf("Enter Product Expiration: ");
    scanf("%[^\n]s",p1.productExpiration);
    /* gets(p1.productExpiration); */
    printf("Enter Product Price: ");
    scanf("%f", &p1.productPrice);

    fwrite(&p1, sizeof(product), 1, fp);
    if(fwrite!=0) {
        printf("Contents written in the file");
    }
    else {
        printf("error occured");
    }
    fclose(fp);
    
}

void addItem() {
    product p1;
    FILE *fp;
    if((fp = fopen("inventory.txt","r"))!=NULL)
    {
        printf("File Exist\n");
        fp = fopen("inventory.txt", "a"); 
    }
    else
    {
        printf("File doesnt Exist\n");
        fp = fopen("inventory.txt", "w");
    }
    
    if(fp == NULL) {
        printf("Cannot Open");
    }

    printf("Enter Product ID: ");
    scanf("%d", &p1.productID);
    fflush(stdin);
    printf("Enter Product Name: ");
    scanf("%[^\n]s",p1.productName);
    /* gets(p1.productName); */
    printf("Enter Product Quantity: ");
    scanf("%d", &p1.productQuantity);
    fflush(stdin);
    printf("Enter Product Expiration: ");
    scanf("%[^\n]s",p1.productExpiration);
    /* gets(p1.productExpiration); */
    printf("Enter Product Price: ");
    scanf("%f", &p1.productPrice);

    fwrite(&p1, sizeof(product), 1, fp);
    if(fwrite!=0) {
        printf("Contents written in the file");
    }
    else {
        printf("error occured");
    }
    fclose(fp);
    
}

void viewAllProducts(){
    product p1;
    FILE *fp;
    int j;
    fp = fopen("inventory.txt", "r");
    while(fread(&p1,sizeof(product),1,fp))
    {
        printf("\n%-5d%-20s   %d   %s    %f", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);
    }

    fclose(fp);
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
    else if(choice == 'C') {
        
    }
    
}

void searchByID() {
    system("cls");
    product p1;
    FILE *fp;
    int j, pId, found = 0;
    fp = fopen("inventory.txt", "r");

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
        printf("\nRecord Not Found\n");
        system("pause");
        searchMenu();
    }

    fclose(fp);
}

void searchByName() {
    system("cls");
    product p1;
    FILE *fp;
    int j, found = 0;
    char pName[30];
    fp = fopen("inventory.txt", "r");

    printf("SEARCH FOR AN INVENTORY ITEM > by Item Name\n\n");
    printf("Enter Product Name to Search: ");
    fflush(stdin);
    scanf("%[^\n]s",pName);
    
    while(fread(&p1,sizeof(product),1,fp))
    {
        if(strcmp(p1.productName, pName) == 0 ){
            found = 1;
            printf("Product ID\tDescription\tQuantity\tExp Date\tPrice");
            printf("\n%-5d%-20s   %d   %s    %f", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);
        }
    }
    if(!found) {
        printf("\nRecord Not Found\n\n");
        system("pause");
        searchMenu();
    }

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