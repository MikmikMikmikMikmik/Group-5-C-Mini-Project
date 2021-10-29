#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct product
{
	int productID[5];
	char productName[35];
	int productQuantity;
	char productExpiration[20];
	float productPrice;
}


product;

void clrscr()
{
	system("@cls||clear");
}


void viewAll()
{
	clrscr();
	char choice1;
	product p1;
	printf("Inventory Item List\n");
	FILE *fp;
	int j;
	fp = fopen("inventory.csv", "r");
	while(fread(&p1,sizeof(product),1,fp))
	{
		printf("\n%-5d%-20s   %d   %s    %f", p1.productID, p1.productName, p1.productQuantity, p1.productExpiration, p1.productPrice);
	}
	
	fclose(fp);	
	
	printf("\n\n[A] Sort by Product ID\n");
	printf("[B] Return to Main Menu");
	printf("\n\nPlease input choice: ");
	scanf(" %c", &choice1);
	
	if(choice1 == 'A')
	{
		sortInventoryItems();
	}
	
	else if(choice1 == 'B')
	{
		mainMenu();
	}
	
}

void sortInventoryItems()
{
	
}

void mainMenu()
{	
	clrscr();
	char choice;
	printf("MAIN MENU\n");
	printf("[A] Add Inventory Item\n");
	printf("[B] Update Inventory Item\n");
	printf("[C] View Inventory Item\n");
	printf("[D] Delete Inventory Item\n");
	printf("[X] Exit Program\n\n");
	printf("Please input choice: ");
	scanf(" %c", &choice);
	
	if(choice == 'C')
	{
		viewInventory();
	}
}
	

void viewInventory()
{
	clrscr();
	char choice;
	printf("VIEW INVENTORY\n");
	printf("[A] View All\n");
	printf("[B] Search for an Inventory Item\n");	
	printf("[C] Back to Menu\n");	
	printf("\nPlease input choice: ");	
	scanf("%c", &choice);
	
	if (choice == 'A')
	{
		viewAll();
	}
	/*else if(choice == 'B')
	{
		searchMenu();
	}*/
	else if(choice == 'C')
	{
		mainMenu();
	}
	else
	{
		clrscr();
		printf("Please input a valid choice.\n");
		viewInventory();
	}

}

int main()
{
	viewInventory();	
}
