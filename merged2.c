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
void mainMenu();

void deleteItem();
void deleteChoice();
void deleteMenu();

void searchMenu();
void searchItemID();
void searchItemName();

void clrscr()
{
    system("@cls||clear");
}

int main()
{
    //int sysInit = 0;
		mainMenu();
	
	return 0;    
}



void updateInventory(){
	FILE * fpointer = fopen("Inventory.txt", "a");
	
	fprintf(fpointer, "\"11101\",\"Nat. Spring (500mL)\",\"200\",\"-\",\"10.50\"\n\"11201\",\"Nat. Spring (1L)\",\"100\",\"-\",\"16.00\"\n\"11202\",\"Nat. Spring (1L)\",\"300\",\"-\",\"16.50\"\n\"12101\",\"Datu Puti Vinegar (1L)\",\"100\",\"2022-03-22\",\"38.25\"\n\"51101\",\"Nivea Silver Protect (50mL)\",\"50\",\"2023-08-31\",\"45.00\"\n");
	
	printf("Hi Hello!");
	fclose(fpointer);
	return;
}

void mainMenu(){
    int sysInit = 0;
    char userCommand;
	printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[X] Exit Program\n\n");
	printf("\nPlease input Choice: ");
    scanf(" %c", &userCommand);
	    
	    switch(userCommand){
	    	case 'A':
			case 'a':{
				addProduct();
				sysInit = 1;
	    		break;}
	    	case 'B':
			case 'b':{
				printf("Your input is %c", userCommand);
				updateInventory();
				sysInit = 1;
	    		break;}
	    	case 'C':
			case 'c':{
				printf("Your input is %c", userCommand);
                //pa try lng lods mark, lagay mo nlng function mo d2
                searchMenu();
				sysInit = 1;
	    		break;}
	    	case 'D':
			case 'd':{
				deleteMenu();
				sysInit = 1;
	    		break;}
	    	case 'X':
			case 'x':{
				printf("Your input is %c", userCommand);
				sysInit = 1;
	    		break;}
	    	default:{
				printf("Your input is %c", userCommand);
				sysInit = 1;
	    		break;
			}
		}
}


/////////////////////////////////////// ADD PART ///////////////////////////////////////////////////

int addProduct()
{
    printf("\nADD ITEM MENU\n");
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
	FILE* fp = fopen("Inventory.csv", "a");
    //FILE* fp2 = fopen("Inventory_ST_NoBOM.csv", "r");
	
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return 0;
	}
		
	printf("\nProduct Description:   ");
	scanf(" %100[^\n]", &product.description);

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

	product.price = atof(checkPrice);
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
    FILE* fp = fopen("Inventory.csv", "r");
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

/////////////////////////////////////// DELETE PART ///////////////////////////////////////////////////

void deleteItem() //DELETE ITEM MENU
{
    int valid = 0;
    int deleteSuccess = 0;
    int i = 0;
    char deleteItemID[20];
    while(strcmp (deleteItemID, "B") != 0 || strcmp(deleteItemID, "b") != 0|| deleteSuccess != 1){
        printf("\nDELETE ITEM MENU");
        printf("\n [B] BACK");
        printf("\n\n PLEASE INPUT ITEM ID: ");
        scanf("%s", &deleteItemID);

        if (strcmp (deleteItemID, "B") == 0 || strcmp (deleteItemID, "b") == 0)
        {
            deleteChoice();
        }
        
        valid = 1;
        for(i=0; i < strlen(deleteItemID); i++)
        {
            if(isalpha(deleteItemID[i]) || strlen(deleteItemID) > 5)//CHECKING IF MAY LETRA SA ID
            {
                valid = 0;
            }
           
        }
        if (valid == 0)  //INVALID ID
        {
            printf("\nInvalid ID\n");
        }

        else if (valid == 1) // VALID ID
        {
            
            int itemID = atoi(deleteItemID);
            
            item s1;
            FILE *fp, *fpl;
            int j, rno, found=0;
            char details[100];
            
            fp = fopen("Inventory.csv","r");
            fpl = fopen("temp.txt","w");

            char buff[500];
            int row_count = 0;
            int field_count = 0;
            item products[999];
            int i = 0;
            while(fgets(buff, sizeof(buff),fp))
            {
                
                int field_count = 0;
                row_count++;
                char complete[100];
                strcpy(complete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0)
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int realResult = atoi(result);
                        products[i].id = realResult;
                        if(products[i].id == itemID)  //KUNG EXIST ANG ID NILAGAY
                        {
                            found = 1;
                            printf("\n\nDO YOU WANT TO DELETE THIS ITEM  \n");
                            printf("%s",complete);
                            printf("\n[Y][N] :");
                        }
                        else
                        {
                            fprintf(fpl, "%s", complete);
                        }
                    }
                    field = strtok(NULL, ",");
                    field_count++;
                }
                i++;
            }
            fclose(fp);
            fclose(fpl);
            if (found == 1) // EXIST ANG ID
            {
                printf(" ");
                char choke[10];
                scanf(" %s",&choke);
                if(strcmp (choke, "Y") == 0 || strcmp (choke, "y") == 0)
                {
                     fpl = fopen("temp.txt","r");
                     fp = fopen("Inventory.csv","w");
                     char ch = fgetc(fpl);
                     while (ch != EOF)
                     {
                        fputc(ch, fp);
                        ch = fgetc(fpl);
                     }
                     printf("\nDELETE SUCCESSFUL!!!!!!!\n\n");
                     fclose(fp);
                     fclose(fpl);
                     deleteSuccess = 1;
                }
                else
                {
                    deleteSuccess = 1;
                    deleteItem();
                }
               
            }
            if (found == 0)
            {
                printf("\nItem Does Not Exist\n\n");
            }
         }
    }
}

void deleteChoice() //DELETE CHOICE MENU
{
    char choice[20];
    while(strcmp (choice, "D") != 0 || strcmp (choice, "S")  != 0 || strcmp (choice, "M") != 0 ||
    strcmp (choice, "d") != 0 || strcmp (choice, "s")  != 0 || strcmp (choice, "M") != 0){
    
    printf("\nDELETE MENU");
    printf("\n [D] DELETE INVENTORY ITEM");
    printf("\n [S] SEARCH INVENTORY ITEM");
    printf("\n [M] MAIN MENU");
    printf("\n\n PLEASE INPUT CHOICE: ");
    scanf("%s", &choice);
    if (strcmp (choice, "D") == 0 || strcmp (choice, "d") == 0){
        deleteItem();
    }
    else if (strcmp (choice, "S") == 0 || strcmp (choice, "s") == 0){
        //addProduct();
        //SEARCH FUNCTION THEN RETURN TO DELETE FUNCTION
        //dummy code young add product
    }
    else if (strcmp (choice, "M") == 0 || strcmp (choice, "m") == 0){
       // display();
        //MAIN MENU FUNCTION
        //dummy code yung display
        mainMenu();
    }

    }
}

void deleteMenu()
{
    deleteChoice();
}


/////////////////////////////////////// SEARCH PART ///////////////////////////////////////////////////
void searchItemID() {
    clrscr();
    FILE *fp = fopen("Inventory.csv","r");

    int prodID, found = 0;
	char line[225];
    const char delims[5] = "\",\"";

    char stringID[6];
    int ID;
    
    printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\n");
    printf("Enter Product ID to Search: ");
    fflush(stdin);
    scanf("%[^\n]s", stringID);

    ID = atoi(stringID);
	
	printf("\n\tProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n\n");
    if ((ID<=0) || (ID>=100000) || strlen(stringID) > 5) {
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
					printf("\t%-10s", token);
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
    FILE* stream = fopen("Inventory.csv", "r");

	char line[225];
	const char delims[5] = "\",\"";
	char *token;
	char *token2;
    char pName[100];
    printf("SEARCH FOR AN INVENTORY ITEM > by Item Name\n\n");
    printf("Enter Product Name to Search: ");
    fflush(stdin);
    scanf("%[^\n]s",pName);

	printf("\n\tProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n\n");
	while(fgets(line,sizeof(line),stream)){
		char lineMemory[225]; strcpy(lineMemory, line);
		token = strtok(line, delims);

		token = strtok(NULL, delims);
		if(strcmp(token, pName) == 0 ){
			token2 = strtok(lineMemory, delims);
			while(token2!=NULL) {
				found = 1;
				printf("\t%-10s", token2);
				token2 = strtok(NULL, delims);
			}
		}
	}
	
	if(!found) {
        printf("\nItem Name does not exists.\n\n");
        system("pause");
        searchMenu();
    }
    
    printf("\n\n");
    system("pause");
    searchMenu();
    fclose(stream);
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
        //function ni mark
    }
    else {
        printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
}
