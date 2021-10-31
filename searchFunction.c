#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clrscr()
{
    system("@cls||clear");
}

typedef struct date
{
	int year;
	int month;
	int day;
}date;

typedef struct item1{
	unsigned int itemID;
	char itemDesc[10];
	unsigned short quantity;
	char expiDate[10];
	float price;
}item1;

typedef struct item2{
	unsigned int itemID;
	char itemDesc[10];
	unsigned short quantity;
	struct expiDate{
		unsigned char year;
		unsigned char month;
		unsigned char day;
	}expiDate[3];
	float price;
}item2;

typedef struct item
{
	int itemID;
	char itemDesc[20];
	int quantity;
	date expiration;
	float price;
}item;

void viewInventory();
void searchMenu();
void searchItemID();
void searchItemName();
void viewAllProducts();

void viewInventory() {
    clrscr();
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

void searchItemID() {
    clrscr();
    FILE *fp = fopen("Inventory_ST_NoBOM.csv","r");

    int ID, prodID, found = 0;
	char line[225];
    const char delims[5] = "\",\"";
    
    printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\n");
    printf("Enter Product ID to Search: ");
    scanf(" %d", &ID);
	
	printf("Product ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
    if ((ID<=0) || (ID>=100000)) {
        printf("\nError! Invalid Input\n");
        system("pause");
        searchMenu();
    }
    else {
		while(fgets(line,sizeof(line),fp)){
        	char *token;
       	 	token = strtok(line,delims);
			prodID = atoi(token);

			if(ID == prodID) {
				while(token!=NULL) {
					found = 1;
					printf("%-10s\t", token);
					token = strtok(NULL,delims);
				}
			}
		}
		if (found == 0){
			printf("\nItem ID does not exist.\n\n");
			fclose(fp);
			system("pause");
			searchMenu();
		}
		printf("\n");
		fclose(fp);
		system("pause");
		searchMenu();	
    }
}

void searchItemName() {
    clrscr();
    int found = 0;
    FILE* stream = fopen("inventory.csv", "r");

	char line[225];
	const char delims[5] = "\",\"";
	char *token;
	char *token2;
    char pName[100];
    printf("SEARCH FOR AN INVENTORY ITEM > by Item Name\n\n");
    printf("Enter Product Name to Search: ");
    fflush(stdin);
    scanf("%[^\n]s",pName);

	printf("Product ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
	while(fgets(line,sizeof(line),stream)){
		char lineMemory[225]; strcpy(lineMemory, line);
		token = strtok(line, delims);

		token = strtok(NULL, delims);
		if(strcmp(token, pName) == 0 ){
			token2 = strtok(lineMemory, delims);
			while(token2!=NULL) {
				found = 1;
				printf("%-10s\t", token2);
				token2 = strtok(NULL, delims);
			}
		}
	}
	
	if(!found) {
        printf("\nRecord Not Found\n\n");
        system("pause");
        searchMenu();
    }
    
    printf("\n\n");
    system("pause");
    searchMenu();
    fclose(stream);
}

void viewAllProducts(){
    FILE *fp = fopen("Inventory_ST.csv","r");
    if(fp == NULL) {
        perror("Unable to open");
        exit(1);
    }
    char line[200];
    while(fgets(line,sizeof(line),fp)) {
        char *token;
        token = strtok(line, ",");

        while(token!=NULL){
            printf("%-12s", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }
}

void searchMenu() {
    clrscr();
    char choice[2];
    printf("SEARCH FOR AN INVENTORY ITEM\n");
    printf("[A] SEARCH BY PRODUCT ID\n");
    printf("[B] SEARCH BY PRODUCT NAME/DESCRIPTION\n");
    printf("[C] BACK TO VIEW INVENTORY MENU\n");
    printf("\nPlease input choice: ");
    fflush(stdin);
    scanf("%s", choice);
	
	if(strlen(choice) > 1 || strlen(choice) < 1 ) {
     	printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
    if(strcmp(choice, "A") == 0 || strcmp(choice, "a") == 0) {
       searchItemID();
    }
    else if(strcmp(choice, "B") == 0 || strcmp(choice, "b") == 0) {
        searchItemName();
    }
    else if(strcmp(choice, "C") == 0 || strcmp(choice, "c") == 0 ) {
        viewInventory();
    }
    else {
        printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
}


int main(){
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