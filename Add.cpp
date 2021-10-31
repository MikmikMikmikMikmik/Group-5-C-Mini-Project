// C program for the above approach
#include <stdio.h>
#include <stdlib.h>
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


void checkingDate(int day,int month,int year);
// Driver Code

int addProduct()
{
	
	
	item product;
	 int ID, prodID, found = 0;
	char line[225];
    const char delims[5] = "\",\"";
	// Substitute the file_path string
	// with full path of CSV file
	FILE* fp = fopen("Inventory.csv", "a+");
		FILE* fpr = fopen("Inventory.csv", "r");
	fread(&product, sizeof(product), 1, fpr);
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return 0;
}
	printf("\nItem ID:");
	scanf("%d", &product.id);
   if ((product.id<=0) || (product.id>=100000)) {
        printf("\nError! Invalid Input\n");
        return addProduct();
    }
     else {
		while(fgets(line,sizeof(line),fpr)){
        	char *token;
       	 	token = strtok(line,delims);
			prodID = atoi(token);

			if(product.id == prodID) {
				while(token!=NULL) {
					found = 1;
						printf("\nID already taken\n\n");
						
					token = strtok(NULL,delims);
				}
			}
		}
		if (found == 0){
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
 return addProduct();
			
		}
		printf("\n");
		fclose(fp);
			 return addProduct();
    }

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



int main(){
	addProduct();
}
