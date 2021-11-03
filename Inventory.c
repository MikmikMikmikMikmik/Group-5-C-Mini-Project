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


typedef struct item1{
	unsigned int itemID;
	char itemDesc;
	unsigned short quantity;
	char expiDate;
	float price;
}item1;


void checkID(int theID);
int addProduct();
void mainMenu();

void updateByDesc();
void updateAgain();
void updateInvalidInput(int invType);
void updateInventoryMenu();
char* updateCheckingDate(int day,int month,int year);
int updateCheckItemID(int itemID, int count);
int updateProcess(int ID);
int updateSearch();


void deleteItem();
void deleteChoice();
void deleteMenu();

void viewMenu();
void sortOption();
void idsortascend();
void idsortdescend();
void postsortScreen();

void searchMenu();
void searchItemID();
void searchItemName();



void clrscr()
{
    system("@cls||clear");
}

int main()
{
	FILE *fpointer = fopen("Inventory.csv", "r");
	if(!fpointer){
		printf("\nInventory file does not exist!");
		return 0;
	}
	else{
		fclose(fpointer);
		mainMenu();
	}
	return 0;    
}



void mainMenu(){
	clrscr();
    int sysInit = 0;
    char userCommand[50];
	printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[X] Exit Program\n\n");
	printf("\nPlease input Choice: ");
    scanf(" %s", &userCommand);
	    

		if (strcmp (userCommand, "A") == 0 ||strcmp (userCommand, "a") == 0)
		{
				clrscr();
			addProduct();
		}
		if (strcmp (userCommand, "B") == 0 ||strcmp (userCommand, "b") == 0)
		{
			updateInventoryMenu();
		}
		if (strcmp (userCommand, "C") == 0 ||strcmp (userCommand, "c") == 0)
		{
			viewMenu();
		}
		if (strcmp (userCommand, "D") == 0 ||strcmp (userCommand, "d") == 0)
		{
			deleteMenu();
		}
		if (strcmp (userCommand, "X") == 0 ||strcmp (userCommand, "x") == 0)
		{
			printf("Program Terminated Successfully");
                exit(0);
		}
		else
		{
			printf("\nError! Invalid Input\n");
				system("pause");
				mainMenu();
		}
	    /*switch(userCommand){
	    	case 'A':
			case 'a':{
				addProduct();
				sysInit = 1;
	    		break;}
	    	case 'B':
			case 'b':{
				printf("Your input is %c", userCommand);
				updateInventoryMenu();
				sysInit = 1;
	    		break;}
	    	case 'C':
			case 'c':{
				printf("Your input is %c", userCommand);
                viewMenu();
				sysInit = 1;
	    		break;}
	    	case 'D':
			case 'd':{
				deleteMenu();
				sysInit = 1;
	    		break;}
	    	case 'X':
			case 'x':{
				printf("Program Terminated Successfully");
                exit;
				sysInit = 1;
	    		break;}
	    	default:{
				printf("\nError! Invalid Input\n");
				system("pause");
				mainMenu();
				sysInit = 1;
	    		break;
			}
		}*/
}


/////////////////////////////////////// ADD PART ///////////////////////////////////////////////////

int addProduct()
{

    printf("ADD INVENTORY ITEM");
    printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
    char again[50];
	char confirm[50];
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
	FILE* fp = fopen("Inventory.csv", "a+");
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
            if(isalpha(checkQuant[i]) || atoi(checkQuant) <=0)//CHECKING IF MAY LETRA SA Quantity and less than zero
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
    char zxc[50];
    while (passExp != 1)
    {
        product.expdate.year = 0;
        printf("\nProduct Exp Date (YYYY-MM-DD):	  ");
	    scanf(" %s",&zxc);
		if(strcmp(zxc,"-")==0)
		{
			passExp = 1;
			
		}
        //printf("\n%d\n%d\n%d",product.expdate.day, product.expdate.month, product.expdate.year);
		if(strcmp(zxc,"-")!=0)
		{
			
			char *field = strtok(zxc,"-");
			int field_count=0;

                while (field != NULL)
                {
                    if (field_count == 0)
                    {
                        product.expdate.year = atoi(field);
                    }
					 if (field_count == 1)
                    {
                        product.expdate.month = atoi(field);
                    }
					 if (field_count == 2)
                    {
                        product.expdate.day = atoi(field);
                    }
                    field = strtok(NULL, "-");
                    field_count++;
                }
				//printf("\n%d\n%d\n%d",product.expdate.year,product.expdate.month,product.expdate.day);
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
			/*if(product.expdate.year == 0) //NO EXPIRATION
			{
				passExp = 1;
			}*/
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
            if(isalpha(checkPrice[i]) || atof(checkPrice) <= 0)//CHECKING IF MAY LETRA SA PRICE AND CHECK IF LESS THAN ZERO
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
	clrscr();
    printf("ADD INVENTORY ITEM");
        printf("\nYou will be adding:");
		printf("\n\tProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n\n");
	printf("\n\t\"%d\",\t\t\"%s\",\t\t\"%d\",\t\t\"-\"\,\t\t\"%.2f\"\n\n", product.id,
			product.description, product.quantity,  product.price);
			printf("\nAdd this item?");
	printf("\n[Y] Yes  ");
		printf("\n[N] No   ");
	printf("\nPlease input choice:");
	scanf(" %s", &again);
    if (strcmp (again, "N") == 0 || strcmp (again, "n") == 0)
        {
            addProduct();
        }
    }
    else
    {
    clrscr();
    printf("ADD INVENTORY ITEM");
        printf("\nYou will be adding:");
        	printf("\n\tProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n\n");
	printf("\n\t \"%d\",\t\t\"%s\",\t\t\"%d\",\t\t\"%d-%d-%d\",\t\t\"%.2f\"\n\n",product.id,
			product.description, product.quantity, 
            product.expdate.year, product.expdate.month,product.expdate.day, product.price);
	printf("\nAdd this item?");
	printf("\n[Y] Yes  ");
		printf("\n[N] No   ");
	printf("\nPlease input choice:");	
	scanf(" %s", &again);
    if (strcmp (again, "N") == 0 || strcmp (again, "n") == 0)
        {
            addProduct();
        }
    }



    if(product.expdate.year == 0) //NO EXPIRATION
    {
	fprintf(fp,"\"%d\",\"%s\",\"%d\",\"-\",\"%.2f\"\n", product.id,
			product.description, product.quantity, product.price);
			//checkingDate(product.expdate.day,product.expdate.month,product.expdate.year);
    }
    else
    {
        fprintf(fp,"\"%d\",\"%s\",\"%d\",\"%d-%d-%d\",\"%.2f\"\n", product.id,
			product.description, product.quantity, 
            product.expdate.year, product.expdate.month,product.expdate.day, product.price);
			//checkingDate(product.expdate.day,product.expdate.month,product.expdate.year);
    }
    clrscr();
    	printf("ADD INVENTORY ITEM");
	printf("\nItem Added!");
printf("\n");
	fclose(fp);
	
    printf("\nDo you want to add an item again?   ");
    printf("\n[Y] Yes  ");
		printf("\n[N] No   ");
		printf("\n");
		printf("\nPlease input choice:   ");
	scanf(" %s", &again);
    if (strcmp (again, "Y") == 0 || strcmp (again, "y") == 0)
        {
            addProduct();
        }
    if (strcmp (again, "N") == 0 || strcmp (again, "n") == 0)
        {
            mainMenu();
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




/////////////////////////////////////// UPDATE PART ///////////////////////////////////////////////////



void updateInventoryMenu(){
	clrscr();
	printf("MAIN MENU > ADD INVENTORY ITEM\nSEARCH BY?\n[A]PRODUCT ID\n[B]PRODUCT NAME/DESCRIPTION\n[X]CANCEL UPDATE\n\nPlease input choice: ");
	char choice;
	scanf("%s",&choice);
	switch (choice){
		case 'X':case 'x':{ 
			mainMenu(); break;
		}
		case 'A':case 'a':{ 
			updateSearch(1); break;
		}
		case 'B':case 'b':{ 
			updateSearch(2); break;
		}
		default:{
			choice = '\0';
			updateInventoryMenu();
			break;
		}
	}

}

void updateAgain(){
	char ch;
	printf("Do you want to try updating an item again?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	ch = getchar();
	scanf("%c", &ch);
	if(ch=='y'|| ch=='Y'){
		updateInventoryMenu();
	}
	else{
		mainMenu();
	}
}

void updateInvalidInput(int invType){
	int invalid = invType;
	
	/*
		Invalid types:
		1 = itemID already taken;
		2 = no match found
		3 = cancelled
		default = invalid input;
	*/
	
	switch(invalid){
		case 1:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nProduct ID currently in use! Item NOT updated!\n\n");
			updateAgain();
			break;
		}
		case 2:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nNo Items Matched.\n\n");
			break;
		}
		case 3:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nUpdate cancelled! Item NOT updated!\n\n");
			updateAgain();
			break;
		}
		default:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nInvalid Input\n\n");
			updateAgain();
			break;
		}
	}
	return;
}

void updateSuccessful(){
	clrscr();
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nUpdate Successful!\n\n");
	updateAgain();
}

char* updateCheckingDate(int day,int month,int year)
{
	if( (day>30 && month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		char *inputDate = "-";
		return inputDate;
	}
	if( (day>31 && month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		char *inputDate = "-";
		return inputDate;
	}
	if( (day>29 && month == 2))
	{
		char *inputDate = "-";
		return inputDate;
	}
	if (year<0 || year>2500)
	{
		char *inputDate = "-";
		return inputDate;
	}
	if (month<1 || month>12)
	{
		char *inputDate = "-";
		return inputDate;
	}
	char *inputDate = "";
	inputDate = "%d/%d/%d", year, month, day;
	char *otherString = inputDate;
	return otherString;
}


void updateSelectedID(int ID){
	
	FILE *fp = fopen("Inventory.csv","r");
	
	int z, found;
	const char s1[5] = "\",\"";
    char line[225];
	while(fgets(line,sizeof(line),fp)){
		while (ID != z) {
			char *token;
			token = strtok(line, s1);
			z = atoi(token);
			if (ID == z){
				clrscr();
				printf("MAIN MENU > UPDATE INVENTORY ITEM\nYou will be updating:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
				while (token!=NULL){
	            	found = 1;
					printf("%-10s\t", token);
					token = strtok(NULL, s1);
				}
				ID = '\0';
	    		fclose(fp);
				updateProcess(z);
				//abort();
			}
			token = strtok(NULL, s1);
			break;
		}
	}
	fclose(fp);
	if (found == 0){
	    fclose(fp);
		updateInvalidInput(0);
		updateAgain();
		//abort();
	}
}


int updateSearchDesc() {
    int found = 0;
	FILE *stream = fopen("Inventory.csv", "r");
    
	char line[225];
	const char delims[5] = "\",\"";
	char *token;
	char *token2;
    char pName[100];
    printf("\nPlease input Item Desc/Name (Enter / to cancel):  ");
    fflush(stdin);
    scanf("%[^\n]s",pName);
    
	if(strcmp(pName, "/") == 0){
		updateInventoryMenu();
	}
	clrscr();
	printf("MAIN MENU > UPDATE INVENTORY ITEM\nItems with \"%s\" on Description:\n\tProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n\n", &pName);
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
  		 	fclose(stream);
		return 0;
  		}
  		else{
   		fclose(stream);
   		return 1;
	}
}


int updateSearch(int searchChoice){
	
	int sChoice = searchChoice;
	char itemDesc[20];
	char *x;
	int ID, found, z;
	int counter = 1;
	item1 item;
	int valid = 1;
    char theString[100];
	do{
		FILE *fp = fopen("Inventory.csv","r");
		const char s1[5] = "\",\"";
				
		if (sChoice == 1){
			printf("\nPlease input Item ID (Enter / to cancel):  ");
			scanf("%s", theString);
			if(strcmp(theString, "/") == 0){
				updateInventoryMenu();
			}
			for(int i=0; i < strlen(theString)+1; i++)
			{
				if(isalpha(theString[i]) || strlen(theString) > 5){ //CHECKING IF MAY LETRA SA ID
            	valid = 0;
				}
			}
			if(valid == 1){
				ID = atoi(theString);
				//scanf("%d", &ID);
				if ((ID<=0) || (ID>=100000)){
				updateInvalidInput(0);
				updateAgain();
				}
				else{
					updateSelectedID(ID);
				}
			}
		    else if(valid == 0)
		    {
		    printf("\nInvalid ID\n");
		    updateSearch(sChoice);
		    }
		}
		else if (sChoice == 2){
			fclose(fp);
			int result = updateSearchDesc();
			if(result == 0){
	        	printf("\nItem Name does not exists.\n\n");
	        	updateAgain();
			}
			else{
				
				printf("\nPlease Enter Item ID from the list(Enter / to cancel):  ");
				scanf("%s", theString);
				if(strcmp(theString, "/") == 0){
					updateInventoryMenu();
				}
				for(int i=0; i < strlen(theString)+1; i++)
				{
					if(isalpha(theString[i]) || strlen(theString) > 5){ //CHECKING IF MAY LETRA SA ID
            		valid = 0;
					}
				}
				if(valid == 1){
					ID = atoi(theString);
					if ((ID<=0) || (ID>=100000)){
						updateInvalidInput(0);
						updateAgain();
					}
					else{
						fclose(fp);
						updateSelectedID(ID);
					}
				}
		    	else if(valid == 0)
		    	{
		    		updateInvalidInput(0);
		    	}
				
			}
		}
	}while(sChoice!=0);
}


int updateCheckItemID(int ID, int newID){
	
	int tempID = ID; 
	int newitemID = newID;
	
	int existingID_itemID;                     
	int existingID_quantity;
	float existingID_price;
	char existingID_itemDesc[30];
	char existingID_expiDate[11];
	
	int z;
	int found = 0;
	int counter = 0;
	int tokenCount = 0;
	const char s1[5] = "\",\"";
	char line[225];
	
	FILE *fp = fopen("Inventory.csv", "r");
	
	if(fp == NULL){
		printf("MAIN MENU > UPDATE INVENTORY ITEM\n The File is empty\n");
		updateAgain();
    }
    
	
	while(fgets(line,sizeof(line),fp)){
		while (tempID != z) {
			
			char *token;
			token = strtok(line, s1);
			z = atoi(token);
			if ((counter == 0 ) && (token == NULL)){
				updateInvalidInput(9);
			}
			counter++;
			if ((newitemID != tempID)){
					//printf("I'm inside updateCheckItemID funtion");
				if (newitemID == z){
					found = 1;
					clrscr();
					//printf("I'm inside updateCheckItemID funtion");
					printf("MAIN MENU > UPDATE INVENTORY ITEM\nThis Item ID is already taken by:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
					while (token!=NULL){
						switch(tokenCount){
							case 0: {
								int otherInt = token;
								strcpy(existingID_itemID, otherInt);
								printf("%-10d\t", existingID_itemID);
								break;
							}
							case 1:{
								strcpy(existingID_itemDesc, token);
								printf("%-10s\t", existingID_itemDesc);
								break;
							}
							case 2:{
								existingID_quantity = token;
								printf("%-10d\t", existingID_quantity);
								break;
							}
							case 3:{
								strcpy(existingID_expiDate, token);
								printf("%-10s\t", existingID_expiDate);
								break;
							}
							case 4:{
								char *unconverted;
								double value = strtod(token, &unconverted);
								existingID_price = value;
								printf("%-10.2f\t", existingID_price);
								break;
							}
							default: {
								token = strtok(NULL, s1);
								break;
							}
						}
						tokenCount++;
						token = strtok(NULL, s1);
					}
					fclose(fp);
					return 2;
					break;
				}
				if(found == 0){
					printf("\nThis is a new item ID: %d\n", newitemID);
					return 1;
				}
			}    
			else{
				fclose(fp);
				return 1;
			}
		}
	}
	
}

int updateProcess(int ID){
	
	item1 itemOnHold;
	int location;
	int count;
	int itemID = ID;
    int valid = 1;
    char theString[100];
    char stringQuant[100];
    char stringPrice[100];
	
	//These are variables for the update after all requirements are met
	int updateCount;
	int itemDescLen = 30;
	//fscanf(fp1, "%i", &itemDescLen);
	char *desc = malloc(sizeof(char)* (itemDescLen + 1));
	desc[itemDescLen] = '\0';
	short currentItemID;
	short currentItemQua;
	char *currentItemExp = malloc(sizeof(char) * (11));  
	currentItemExp[10] = '\0';
	float currentItemPri;
	char expiration;
	
	//These are variable for new details of item to be updated
	int newItemID;
	char newItemDesc[30];
	int newQuantity;
	char newExpiDate[10] = {0};
	float newPrice;
	
	//This variable is to hold old details of item to be updated
	int itemOnHold_itemID;
	int itemOnHold_quantity;
	float itemOnHold_price;
	char itemOnHold_itemDesc[30];
	char itemOnHold_expiDate[11];
	
	int tempID = ID;
	
	FILE *fp1 = fopen("Inventory.csv", "r");
	FILE *fp2 = fopen("copyInventory.csv","w");
	
	if(!fp1){
		printf("\nInventory file does not exist!\n");
		return 0;
	}

	//This part is for user input and counterchecking if input is appropriate
	printf("\nPlease Enter New Item Details (Enter '-' if not applicable):\n");
	
	printf("\nEnter new Item ID: (Enter / to cancel)\t");
	scanf("%s", theString);
	if(strcmp(theString, "/") == 0){
		updateInventoryMenu();
	}
	for(int i=0; i < strlen(theString)+1; i++)
	{
		if(isalpha(theString[i]) || strlen(theString) > 5){ //CHECKING IF MAY LETRA SA ID
           	valid = 0;
		}
	}
	if(valid == 1){
		newItemID = atoi(theString);
		//scanf("%d", &ID);
		int result = updateCheckItemID(tempID, newItemID);
		if ((newItemID<=0) || (newItemID>=100000)){
			updateInvalidInput(9); //default "Input invalid"
		}
		else if(result == 2){
			updateInvalidInput(1); //itemID already taken
		}
	}
    else if(valid == 0)
    {
    printf("\nInvalid ID\n");
    updateProcess(ID);
    }
	
	printf("\nEnter new Description:\t\t");
	scanf(" %[^\n]s", newItemDesc);
	if(strcmp(theString, "/") == 0){
		updateInventoryMenu();
	}
	
	printf("\nEnter new Quantity:\t\t");
	scanf("%s", stringQuant);
	if(strcmp(stringQuant, "/") == 0){
		updateInventoryMenu();
	}
    for(int i=0; i < strlen(stringQuant)+1; i++)
	{
		if(isalpha(stringQuant[i]) || strlen(stringQuant) > 5){ //CHECKING IF MAY LETRA SA ID
           	valid = 0;
		}
	}
	if(valid == 1){
		newQuantity = atoi(stringQuant);
		if (isdigit(&newQuantity)){
			updateInvalidInput(0);
		}
	}else if(valid == 0){
			updateInvalidInput(0);
	}
	
	printf("\nEnter New Expiration Date: (yyyy-mm-dd)\t\t");
	int year, month, day;
	scanf("%d-%d-%d",&year, &month, &day); 
	if (strcmp(updateCheckingDate(year,month,day), "-") == 0) {
		sprintf(newExpiDate, "-");
	}
	else{
		sprintf(newExpiDate, "%d-%d-%d", year, month, day);
	}
					
	printf("\nEnter new price:\t\t");
	scanf("%s", stringPrice);
	if(strcmp(stringPrice, "/") == 0){
		updateInventoryMenu(); 
	}
	for(int i=0; i < strlen(stringPrice)+1; i++)
	{
		if(isalpha(stringPrice[i]) || strlen(stringPrice) > 5){ //CHECKING IF MAY LETRA SA ID
           	valid = 0;
		}
	}
	if(valid == 1){
		newPrice = atof(stringPrice);
		if (isdigit(&newPrice)){
			updateInvalidInput(0);
		}
	}else if(valid == 0){
			updateInvalidInput(0);
	}
	
	fp1 = fopen("Inventory.csv", "r");
	fp2 = fopen("copyInventory.csv","w");
	
	clrscr();
	int z, counter = 0;
	int tokenCount = 1;
	const char s1[5] = "\",\"";
	char line[225];
	
	while(fgets(line,sizeof(line),fp1)){
		char *token;
		token = strtok(line, s1);
		z = atoi(token);
		if (z == itemID){
			printf("MAIN MENU > UPDATE INVENTORY ITEM\nCurrent Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
			while (token!=NULL){
				switch(tokenCount){
					case 1: {
						itemOnHold_itemID = atoi(token);
						printf("%d\t\t", itemOnHold_itemID);
						break;
					}
				case 2:{
						strcpy(itemOnHold_itemDesc, token);
						printf("%s\t", itemOnHold_itemDesc);
						break;
					}
					case 3:{
						itemOnHold_quantity = atoi(token);
					printf("%d\t", itemOnHold_quantity);
						break;
					}
					case 4:{
						strcpy(itemOnHold_expiDate, token);
						printf("%s\t", itemOnHold_expiDate);
						break;
					}
					case 5:{
						char *unconverted;
						double value = strtod(token, &unconverted);
						itemOnHold_price = value;
						printf("%.2f\t", itemOnHold_price);
						break;
					}
					default: {
						break;
					}
				}
				tokenCount++;
				token = strtok(NULL, s1);
			}
		}
	counter++;
	}
		
	fclose(fp1);
	fclose(fp2);
	
	if (strcmp(newExpiDate, "NULL") == 0){
		printf("\n\nUpdated Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n%-10d\t%-10s\t%-10d\t-\t%-10.2f\n", newItemID, newItemDesc, newQuantity, newPrice);
	}else{
		printf("\n\nNew Expiration date is : %s", newExpiDate);
		printf("\n\nUpdated Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n%-10d\t%-10s\t%-10d\t%-10s\t%-10.2f\n", newItemID, newItemDesc, newQuantity, newExpiDate, newPrice);
	}
	printf("\nProceed with update?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	char ch;
	ch = getchar();
	scanf("%c", &ch);
	//printf("I\'m right below the ch variable");
	if(!(ch=='y'|| ch=='Y')){
		updateInvalidInput(3);
		//abort();
	}
		
	int x, i;
		
	fp1 = fopen("Inventory.csv", "r");
	fp2 = fopen("copyInventory.csv","w");
	
	int scanCount = 0;
	
	tokenCount = 5;
	
	while(fgets(line,sizeof(line),fp1)){
		//printf("\nI\'m here inside the loop");
		char *token;
		token = strtok(line, s1);
		z = atoi(token);
		while (token != NULL){
			//printf("\nI\'ve entered another loop");
			if (z == itemID && itemID != newItemID){
				//printf("\nI\'ve entered z!=newItem statement");
				int j;
				for (j = 0; j < 7; j++){
					//printf("\nI\'m in a for loop");
					token = strtok(NULL, s1);
				}
				if (newExpiDate != NULL){
					fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, &newExpiDate, newPrice);
				}else 
				if (newExpiDate == NULL){              
					fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"-\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, newPrice);
				}
			}else if (z == newItemID && itemID == newItemID){
				//printf("\nI\'ve entered z==newItem statement");
				int j;
				for (j = 0; j < 6; j++){
					//printf("\nI\'m in a for loop");
					token = strtok(NULL, s1);
				}
				if (newExpiDate != NULL){
					fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, &newExpiDate, newPrice);
				}else 
				if (newExpiDate == NULL){              
					fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"-\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, newPrice);
				}
			}
			else{
				if(tokenCount != 0){
					if(tokenCount != 1){
						fprintf(fp2,"\"%s\",", token);
						token = strtok(NULL, s1);
						tokenCount--;
					}
					else{
						fprintf(fp2,"\"%s\"", token);
						tokenCount--;
						token = strtok(NULL, s1);
					}
				}
				else{
					fprintf(fp2,"\n");
					tokenCount = 5;
					token = strtok(NULL, s1);
				}
			}
		}
	}
	
	
	fclose(fp1);
	fclose(fp2);
	
	
	fp1 = fopen("copyInventory.csv", "r");
	fp2 = fopen("Inventory.csv","w");
	
	tokenCount = 5;
	
	while(fgets(line,sizeof(line),fp1)){
		char *token;
		token = strtok(line, s1);
		z = atoi(token);
		while (token != NULL){
			if(tokenCount != 0){
				if (token == '-'){
					fprintf(fp2,"\"%s\"", token);
					token = strtok(NULL, s1);
					tokenCount--;
				}
				if(tokenCount != 1){
					fprintf(fp2,"\"%s\",", token);
					token = strtok(NULL, s1);
					tokenCount--;
				}
				else{
					fprintf(fp2,"\"%s\"", token);
					token = strtok(NULL, s1);
					tokenCount--;
				}
			}
			else{
				fprintf(fp2,"\n");
				tokenCount = 5;
				token = strtok(NULL, s1);		
			}
		}
	}
	
	
	fclose(fp1);
	fclose(fp2);
	
	updateSuccessful();

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
	clrscr();
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
        searchMenu();
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
    printf("Search for an Inventory Item\n");
    printf("[A] Search by Product ID\n");
    printf("[B] Search by Product Description\n");
    printf("[C] Back to View Inventory Menu\n");
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
        viewMenu();
    }
    else {
        printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
}

/////////////////////////////////////// VIEW PART ///////////////////////////////////////////////////

void viewMenu()
{
	clrscr();
	char choice;
	printf("View Inventory Item\n");
	printf("\n[A] View All Inventory Items\n");
	printf("[B] Search for an Inventory Item\n");
	printf("[C] Return to Main Menu\n");
	printf("\n Please input valid choice: ");
	scanf(" %c", &choice);
	if(choice == 'A')
	{
		sortOption();
	}
	else if(choice == 'B')
	{
		searchMenu();
	}
	else if(choice == 'C')
	{
		clrscr();
		mainMenu();
	}
	else
	{
		printf("\n\nError! Invalid Input\n\n");
        system("pause");
        viewMenu();
	}
}

void sortOption()
{
	clrscr();
	char choice1;
	printf("View All\n");
	printf("\n[A] Sort Product ID in Ascending Order\n");
	printf("[B] Sort Product ID in Descending Order\n");
	printf("[C] Return to Main Menu\n");
	printf("\nPlease input valid choice: ");
	scanf(" %c", &choice1);
	if(choice1 == 'A')
	{
		idsortascend();
	}
	else if(choice1 == 'B')
	{
		idsortdescend();
	}
	else if(choice1 == 'C')
	{
		clrscr();
		mainMenu();
	}
	else 
	{
		printf("\n\nError! Invalid Input\n\n");
        system("pause");
        sortOption();
	}

}

void idsortascend()
{
	typedef struct item
{
	int productID;
	char productDescription[30];
	int quantity;
	char expiration[30];
	float price;
}item;
 			FILE *fp;
            
            fp = fopen("inventory.csv","r");
            char buff[500];
            int row_count = 0;
            int field_count = 0;
            item products[999];
            int i = 0;
            char complete[500][100];
            
            while(fgets(buff, sizeof(buff),fp))
            {
                
                int field_count = 0;
                row_count++;
                
                strcpy(complete[i], buff);
                
                
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0'; 
                        int realResult = atoi(result); 
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1)
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) 
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3)
                    {
                    	char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].expiration, result);
                    }
                    if (field_count == 4) 
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        float thePrice = strtod(result,NULL);
                        
                       products[i].price = thePrice; 
                        
                    }
                    field = strtok(NULL, ",");
                    field_count++;
                }
                i++;
            }
            fclose(fp);

            
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            printf("\n\tProduct ID\t\tDescription\t\tQuantity\t\tExp Date\t\tPrice\n");
            for(int x=0;x<i;x++)
            {
                    for(int y=x+1;y<i;y++)
                        {
                            
                            if(products[y].productID < products[x].productID && products[x].productID != 0)
                                {
                                    idTmp = products[x].productID;
                                    products[x].productID = products[y].productID;
                                    products[y].productID = idTmp;

                                    strcpy(descTmp ,products[x].productDescription);
                                    strcpy(products[x].productDescription, products[y].productDescription);
                                    strcpy(products[y].productDescription, descTmp);

                                    quantTmp = products[x].quantity;
                                    products[x].quantity = products[y].quantity;
                                    products[y].quantity = quantTmp;

                                    strcpy(expTmp ,products[x].expiration);
                                    strcpy(products[x].expiration, products[y].expiration);
                                    strcpy(products[y].expiration, expTmp);

                                    priceTmp = products[x].price;
                                    products[x].price = products[y].price;
                                    products[y].price = priceTmp;
                                    
                                }
                        }
                        
          }
            
            
            
            for(int x=0;x<i;x++)
            {
                //printf("\n        \"%d\"                 %0.10s\"%d\"            %s           \"%.2f\"",products[x].productID,products[x].productDescription,
                //products[x].quantity,products[x].expiration,products[x].price);
                printf("\n        %*d", -5, products[x].productID);
                printf("                   %*.10s", -10, products[x].productDescription);
                printf("              %*d", -4, products[x].quantity);
                printf("                    %*.12s", -16, products[x].expiration);
                printf("        %*.2f", -2, products[x].price);
          
            }  
         		postsortScreen();
            
}

void idsortdescend()
{
	typedef struct item
{
	int productID;
	char productDescription[30];
	int quantity;
	char expiration[30];
	float price;
}item;
 			FILE *fp;
            
            fp = fopen("inventory.csv","r");
            char buff[500];
            int row_count = 0;
            int field_count = 0;
            item products[999];
            int i = 0;
            char complete[500][100];
            
            while(fgets(buff, sizeof(buff),fp))
            {
                
                int field_count = 0;
                row_count++;
                
                strcpy(complete[i], buff);
                
                
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0'; 
                        int realResult = atoi(result); 
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1)
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) 
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3)
                    {
                    	char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].expiration, result);
                    }
                    if (field_count == 4) 
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        float thePrice = strtod(result,NULL);
                        
                       products[i].price = thePrice; 
                        
                    }
                    field = strtok(NULL, ",");
                    field_count++;
                }
                i++;
            }
            fclose(fp);

            
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            printf("\n\tProduct ID\t\tDescription\t\tQuantity\t\tExp Date\t\tPrice\n");
            for(int x=0;x<i;x++)
            {
                    for(int y=x+1;y<i;y++)
                        {
                            
                            if(products[y].productID > products[x].productID && products[x].productID != 0)
                                {
                                    idTmp = products[x].productID;
                                    products[x].productID = products[y].productID;
                                    products[y].productID = idTmp;

                                    strcpy(descTmp ,products[x].productDescription);
                                    strcpy(products[x].productDescription, products[y].productDescription);
                                    strcpy(products[y].productDescription, descTmp);

                                    quantTmp = products[x].quantity;
                                    products[x].quantity = products[y].quantity;
                                    products[y].quantity = quantTmp;

                                    strcpy(expTmp ,products[x].expiration);
                                    strcpy(products[x].expiration, products[y].expiration);
                                    strcpy(products[y].expiration, expTmp);

                                    priceTmp = products[x].price;
                                    products[x].price = products[y].price;
                                    products[y].price = priceTmp;
                                    
                                }
                        }
                        
          }
            
            
            
            for(int x=0;x<i;x++)
            {
                //printf("\n        \"%d\"                 %0.10s\"%d\"            %s           \"%.2f\"",products[x].productID,products[x].productDescription,
                //products[x].quantity,products[x].expiration,products[x].price);
                printf("\n        %*d", -5, products[x].productID);
                printf("                   %*.10s", -10, products[x].productDescription);
                printf("              %*d", -4, products[x].quantity);
                printf("                    %*.12s", -16, products[x].expiration);
                printf("        %*.2f", -2, products[x].price);
          
            }  
         		postsortScreen();
            
}

void postsortScreen()
{
			char choice1;
	    	printf("\n\n[A] Return to Main Menu\n");
            printf("[B] Return to View Menu\n");
            printf("Please input valid choice: ");
            scanf(" %c", &choice1);
            if(choice1 == 'A')
            {
            	clrscr();
            	mainMenu();
			}
			else if(choice1 == 'B')
			{
				clrscr();
				viewMenu();
			}
			else
			{
				clrscr();
				printf("Invalid Input!");
				postsortScreen();
			}
            
}
