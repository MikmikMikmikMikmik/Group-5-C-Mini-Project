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


void viewAllItems()
{
	product p1;
	FILE *p;
	int j;
	fp = fopen("inventory.txt", "r");
	while(fread(&p1,sizeof(product),1,fp))
	{
		printf("\n%-5d%-20s	%d	%s	%f", p1.productID, p1.productQuantity, p1.productExpiration, p1.productPrice);
	}
	
	fclose(fp);
}

void viewInventory()
{
	clrscr();
	char choice;
	printf("VIEW INVENTORY\n");
	printf("[A] View All\n");
	printf("[B] Search for an Inventory Item\n");	
	printf("[C] Back to Menu\n");	
	printf("Please input choice: ");	
	scanf("%c", &choice);
	
	if (choice == 'A')
	{
		viewAllItems();
	}
	else if(choice == 'B')
	{
		searchMenu();
	}
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

