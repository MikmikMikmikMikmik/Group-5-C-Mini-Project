#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>

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
	float price;
}item;

void checkID(int theID);

int addProduct();

int checkProductNumber(int id, int count);

void checkingDate(int day,int month,int year);
// Driver Code
int main(){
	addProduct();
}

int addProduct()
{
    char again[50];
	item product;
    int valid = 1;
    char theString[100];
	
	
    printf("\nItem ID:  ");
	scanf(" %s", &theString);
    for(int i=0; i < strlen(theString)+1; i++)
        {
            if(isalpha(theString[i]) || strlen(theString) > 5)//CHECKING IF MAY LETRA SA ID
            {
                 valid = 0;
                 
            }
            
        }
    if(valid == 1)
    {
        product.id = atoi(theString);
        checkID(product.id);

    
	// Substitute the file_path string
	// with full path of CSV file
	FILE* fp = fopen("Inventory_ST_NoBOM.csv", "a");
    FILE* fp2 = fopen("Inventory_ST_NoBOM.csv", "r");
	
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return 0;
	}
		
	printf("\nProduct Description:   ");
	scanf(" %s", &product.description);

    char checkQuant[50];
    int passQuant = 0;
    while (passQuant != 1)
    {
        passQuant = 1;
        printf("\nProduct Quantity:  	");
	    scanf(" %s", &checkQuant);
        for(int i=0; i < strlen(checkQuant); i++)
        {
            if(isalpha(checkQuant[i]))//CHECKING IF MAY LETRA SA Quantity
            {
                 passQuant = 0;
            }
        }
        if (passQuant == 0)
        {
            printf("\nInvalid Quantity!\n");
        }
    }
    product.quantity = atoi(checkQuant);

    int passExp = 0;
    char noExp[50];
    while (passExp != 1)
    {
        product.expdate.year = 0;
        printf("\nProduct Exp Date (YEAR/MONTH/DAY):	  ");
	    scanf(" %d/%d/%d",&product.expdate.year, &product.expdate.month, &product.expdate.day);
        //printf("\n%d\n%d\n%d",product.expdate.day, product.expdate.month, product.expdate.year);
        passExp = 1;
        
       
        if(product.expdate.day<1)
	    {
            passExp = 0;
	    }
        if( (product.expdate.day>30 && (product.expdate.month ==  2 || product.expdate.month == 4 
        ||product.expdate.month == 6 ||product.expdate.month == 9 ||product.expdate.month ==  11 )))
	    {
            passExp = 0;
	    }

	    if( product.expdate.day>31 && (product.expdate.month ==   1 ||product.expdate.month == 2 ||
        product.expdate.month == 3 ||product.expdate.month == 5 ||product.expdate.month == 7 ||
        product.expdate.month ==  8 ||product.expdate.month ==  10 ||product.expdate.month ==  12 ))
	    {
            passExp = 0;
	    }

        if( (product.expdate.day>29 && product.expdate.month == 2))
        {
            passExp = 0;
        }

        if (product.expdate.year<0 || product.expdate.year>2500)
        {
            passExp = 0;
        }

        if (product.expdate.month<1 || product.expdate.month>12)
        {
            passExp = 0;
        }
        /*if(strcmp (noExp, "-") == 0)
        {
            passExp = 1;
        }*/
        if(product.expdate.year == 0) //NO EXPIRATION
        {
            passExp = 1;
        }
        if (passExp == 0)
        {
            printf("\nInvalid date, Please enter details again");
        }
        //printf("%d",passExp);
        
    }
    //printf("\n%d", product.expdate.year);
    char checkPrice[50];
    int passPrice = 0;
    while (passPrice != 1)
    {
        passPrice = 1;
        printf("\nProduct Price:  	");
	    scanf(" %s", &checkPrice);
        for(int i=0; i < strlen(checkPrice); i++)
        {
            if(isalpha(checkPrice[i]))//CHECKING IF MAY LETRA SA PRICE
            {
                 passPrice = 0;
            }
            
        }
        if (passPrice == 0)
        {
            printf("\nInvalid Price!\n");
        }
    }

	product.price = atoi(checkPrice);
	// Saving data in file
    if(product.expdate.year == 0) //NO EXPIRATION
    {
	fprintf(fp,"\"%d\",\"%s\",\"%d\",\"-\",\"%.2f\"\n", product.id,
			product.description, product.quantity, 
            product.expdate.day, product.price);
			//checkingDate(product.expdate.day,product.expdate.month,product.expdate.year);
    }
    else
    {
        fprintf(fp,"\"%d\",\"%s\",\"%d\",\"%d/%d/%d\",\"%.2f\"\n", product.id,
			product.description, product.quantity, 
            product.expdate.day, product.expdate.month,product.expdate.year, product.price);
			//checkingDate(product.expdate.day,product.expdate.month,product.expdate.year);
    }
	printf("\nNew Account added to record");

	fclose(fp);
    printf("\nAdd A Product Again? [Y][N]:   ");
	scanf(" %s", &again);
    if (strcmp (again, "Y") == 0 || strcmp (again, "y") == 0)
        {
            addProduct();
        }
    if (strcmp (again, "N") == 0 || strcmp (again, "n") == 0)
        {
            //MAIN MENU DITO
        }
	//return 0;
    }

    if(valid == 0)
    {
    printf("\nInvalid ID\n");
    addProduct();
    }
    
}


void checkID(int theID)
{
    FILE* fp = fopen("Inventory_ST_NoBOM.csv", "r");
    char buff[500];
    int row_count = 0;
    int field_count = 0;
    item products[999];
    int i = 0;
    while(fgets(buff, sizeof(buff),fp))
     {
                int field_count = 0;
                row_count++;
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0)
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int realResult = atoi(result);
                        products[i].id = realResult;
                        if(products[i].id == theID)  //KUNG EXIST ANG ID NILAGAY
                        {
                            printf("\nPRODUCT ITEM ID ALREADY EXIST PLEASE TRY AGAIN\n");
                            addProduct();
                        }
                        else
                        {
                            //fprintf(fpl, "%s", complete);
                        }
                    }
                    field = strtok(NULL, ",");
                    field_count++;
                }
                i++;
            }
            fclose(fp);
            //fclose(fp2);
}