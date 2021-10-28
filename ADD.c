// C program for the above approach
#include <conio.h>
#include <stdio.h>
#include <string.h>


typedef struct date
{
	int day;
	int month;
	int year;
}date;


typedef struct item
{
	
char description[255];
	int id, quantity;
	date expdate;
	date expiration;
	int price;
}item;

int checkProductNumber(int id, int count);

void checkingDate(int day,int month,int year);
// Driver Code
int main(){
	addProduct();
}
int addProduct()
{
	
	item product;
	// Substitute the file_path string
	// with full path of CSV file
	FILE* fp = fopen("Item.csv", "a+");

	
	
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return 0;
	}

    
	
	
	printf("\nItem ID:");
	scanf("%d", &product.id);

	printf("\nProduct Description:");
	scanf("%s", &product.description);
	printf("\nProduct Quantity:	");
	scanf("%d", &product.quantity);
	printf("\nProduct Exp Date:	");
	scanf("%d/%d/%d",&product.expdate.day,&product.expdate.month,&product.expdate.year);
	printf("\nProduct Price:	");
	scanf("%d", &product.price);
	// Saving data in file
	fprintf(fp, "%d, %s, %d, %d/%d/%d, %d\n", product.id,
			product.description, product.quantity,product.expdate.day,product.expdate.month,product.expdate.year, product.price);
			checkingDate(product.expdate.day,product.expdate.month,product.expdate.year);
	printf("\nNew Account added to record");

	fclose(fp);
	return 0;
}





void checkingDate(int day,int month,int year)
{
	if( (day>30 && month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		addProduct();
	}

	if( (day>31 && month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		addProduct();
	}

	if( (day>29 && month == 2))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		addProduct();
	}

	if (year<0 || year>2500)
	{
		printf("\nInvalid date\nPlease enter details again\n");
		addProduct();
	}

	if (month<1 || month>12)
	{
		printf("\nInvalid date\nPlease enter details again");
		addProduct();
	}
	else
	{
		
	}

}


