#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


void clrscr()
{
    system("@cls||clear");
}

int sysInit = 0;

typedef struct date
{
	int year;
	int month;
	int day;
}date;

typedef struct item1{
	unsigned int itemID;
	char itemDesc;
	unsigned short quantity;
	char expiDate;
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
	char itemDesc;
	int quantity;
	char expiDate;
	float price;
}item;

void mainMenu();
void updateByDesc();
void updateAgain();
void updateInvalidInput(int invType);
void addAllFromBackUp();
void updateInventory();

char* updateCheckingDate(int day,int month,int year);

int updateCheckItemID(int itemID, int count);
int updateProcess(int ID);
int updateSearch();

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
	//abort();

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
		//abort();    
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
	//abort();
}

void addAllFromBackUp(){
	
	item *addTheBackUp;
	
	FILE *fpointer = fopen("Database\\Inventory.csv", "w+");
	FILE *fpointer2 = fopen("Database\\Inventory_ST_NoBOM.csv", "r");
	if(!(fpointer2 || fpointer)) {
		printf("\nInventory file does not exist!");
	}
	else{
	
	char *token;
	char delimit [] = "\",\"";
    char line[999];
	int counter = 0;
	int tokenCount = 5;
	int i;
	
	
	while(fgets(line,sizeof(line),fpointer2)){
		token = strtok(line, delimit);
		while (token != NULL){
			if(tokenCount != 0){
				if(tokenCount != 1){
					fprintf(fpointer,"\"%s\",", token);
					token = strtok(NULL, delimit);
					tokenCount--;
				}
				else{
					fprintf(fpointer,"\"%s\"", token);
					tokenCount--;
					token = strtok(NULL, delimit);
				}
			}
			else{
				fprintf(fpointer,"\n");
				tokenCount = 5;
				token = strtok(NULL, delimit);
			}
		}
	}
	printf("\n\nInventory file reset!\n\n");
	
	rename("Database\\Inventory.txt","Database\\Inventory.csv");
	
	fclose(fpointer);
	fclose(fpointer2);
	system("pause");
	mainMenu();
	
	}
}


char* updateCheckingDate(int day,int month,int year)
{
	if( (day>30 && month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		updateInvalidInput(0);
	}
	if( (day>31 && month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		updateInvalidInput(0);
	}
	if( (day>29 && month == 2))
	{
		printf("\nInvalid date\nPlease enter details again\n");
	}
	if (year<0 || year>2500)
	{
		printf("\nInvalid date\nPlease enter details again\n");
		updateInvalidInput(0);
	}
	if (month<1 || month>12)
	{
		printf("\nInvalid date\nPlease enter details again");
		updateInvalidInput(0);
	}
	char *inputDate = "";
	inputDate = "%d/%d/%d", year, month, day;
	char *otherString = inputDate;
	return otherString;
}


void displayAllItems(){
	int totalInventory;
	item1 item;
	int count;
	FILE *fp = fopen("Database\\Inventory.csv","r");
	const char s1[5] = ",\"";
    char line[225];
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n\tProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
	while(fgets(line,sizeof(line),fp)){
		char *token;
		count++;
		token = strtok(line, s1);
		while (token!=NULL){
			printf("\t%s", token);
			token = strtok(NULL, s1);
		}
	}
	totalInventory = count;
    fclose(fp);
	printf("\n\nTotal No. of items in the Inventory: \t %d\n\n", totalInventory);
    system("pause");
    clrscr();
    mainMenu();
	//abort();
}

int indexOfSubString(char str[], char s[]){
	int i,j,k,l;
	l = strlen(s);
	for (i=0; str[i+l-1]; i++){
		k = i;
		for (i=0; str[i+l-1]; i++){
			if (str[k] != s[j]){
				break;
				k++;
			}
			if(j==l)
			return 1;
		}
		return -1;
	}

}

void updateSelectedID(int ID){
	
	FILE *fp = fopen("Database\\Inventory.csv","r");
	
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


int updateSearch(int searchChoice){
	
	int sChoice = searchChoice;
	char itemDesc[20];
	char *x;
	int ID, found, z;
	int counter = 1;
	item1 item;
	do{
		FILE *fp = fopen("Database\\Inventory.csv","r");
		const char s1[5] = "\",\"";
				
		if (sChoice == 1){
			printf("\nPlease input Item ID:\t\t");
			scanf("%d", &ID);
			if ((ID<=0) || (ID>=100000)){
				updateInvalidInput(0);
				updateAgain();
				//abort();
			}
			else{
				updateSelectedID(ID);
			}
		}
		else if (sChoice == 2){
				
			int totalInventory;
			item1 item;
			int count;
			FILE *fp = fopen("Database\\Inventory.csv","r");
			
			printf("\n\nPlease Enter Item Desc:\t\t");
			scanf(" %[^\n]%*c", itemDesc);
			
			
			//Problem here ==========================================
			
			system("pause");
			clrscr();
			
			int index;
			const char s1[5] = ",\"";
		    char line[225];
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\tProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
			
			char *previousToken;
			
			while(fgets(line,sizeof(line),fp)){
				char *token;
				count++;
				token = strtok(line, s1);
				previousToken = token;
				while (token!=NULL){
					index = indexOfSubString(token, itemDesc);
					if (index == -1){
						printf("\t%s", previousToken);
						printf("\t%s", token);
						printf("\t%s", token);
						printf("\t%s", token);
						printf("\t%s", token);
						printf("\t%s", token);
						token = strtok(NULL, s1);
					}else{	
						previousToken = token;
						token = strtok(NULL, s1);
					}
				}
			totalInventory = count;
		    fclose(fp);
			}
			
			
			
			/*
			int found;
			
		    while(fread(&item,sizeof(item),1,fp))
	    	{
	        	if(strcmp(item.itemDesc, itemDesc) == 0 ){
	            	found = 1;
		            printf("\n%d\t%-20s\t%d\t%s\t%.2f", item.itemID, item.itemDesc , item.quantity , item.expiDate , item.price);
	    	    }
	    	}
	    	if(!found) {
	        	printf("\n\nItem Name does not exist!\n\n");
	        	system("pause");
	        	updateAgain();
	    	}
	    	
			*/
	    	
			printf("\nPlease input Item ID of Item from the List:\t\t");
			scanf("%d", &ID);
			if ((ID<=0) || (ID>=100000)){
				updateInvalidInput(0);
				updateAgain();
				//abort();
			}
			else{
				updateSelectedID(ID);
			}
		}
	}while(sChoice!=0);
}


int updateCheckItemID(int ID, int newID){
	
	int tempID = ID; 
	int newitemID = newID;
	
	FILE *fp1 = fopen("Database\\Inventory.csv", "r");
	
	int existingID_itemID;                     
	int existingID_quantity;
	float existingID_price;
	char existingID_itemDesc[30];
	char existingID_expiDate[11];
	
	int z, counter;
	int tokenCount = 0;
	const char s1[5] = "\",\"";
    char line[225];
	while(fgets(line,sizeof(line),fp1)){
		while (tempID != z) {
			counter++;
			char *token;
			token = strtok(line, s1);
			z = atoi(token);
			if ((newitemID != tempID) && (newitemID == z)){
				clrscr();
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
				fclose(fp1);
				return 2;
				break;
			}
			else{
				fclose(fp1);
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
	char newExpiDate[11];
	float newPrice;
	
	//This variable is to hold old details of item to be updated
	int itemOnHold_itemID;
	int itemOnHold_quantity;
	float itemOnHold_price;
	char itemOnHold_itemDesc[30];
	char itemOnHold_expiDate[11];
	
	int tempID = ID;
	
	FILE *fp1 = fopen("Database\\Inventory.csv", "r");
	FILE *fp2 = fopen("Database\\copyInventory.csv","w");
	FILE *fp3 = fopen("Database\\counter.dat","r");
	FILE *fp4 = fopen("Database\\control.dat","w");
	
	if(!fp1 || !fp3){
		printf("\nInventory file does not exist!\n");
		return 0;
	}
	
	
	//This part is for user input and counterchecking if input is appropriate
	printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
	
	printf("\nEnter new Item ID:\t\t");
	scanf("%d",&newItemID);
	if ((newItemID<=0) || (newItemID>=100000)){
		updateInvalidInput(9); //default
	}
	else if(updateCheckItemID(tempID, newItemID) == 2){
		updateInvalidInput(1); //itemID already taken
		//abort();
	}
	//alternative way of catching characters on a string
	/*
	for(j = 0; newItemID[j] != '\0'; j++){
		//check if string is not a digit
		if (!(
		
		(itemDesc[j] <= 47 && itemDesc[j] >= 58) || 
		
			printf("\n\nThis is a good String\t\t");
			break;
		}
	}
	*/
	
	printf("\nEnter new Description:\t\t");
	scanf(" %[^\n]s", newItemDesc);
	
	printf("\nEnter new Quantity:\t\t");
	scanf("%d",&newQuantity);
	if (isdigit(&newQuantity)){
		updateInvalidInput(0);
	}
	
	printf("\nEnter New Expiration Date: (yyyy-mm-dd)\t\t");
	int year, month, day;
	scanf("%d-%d-%d",&year, &month, &day); 
	if (year == '-') {
		strcpy(expiration, "-");
	}
	
					
	printf("\nEnter new price:\t\t");
	scanf("%f",&newPrice);
	if (isdigit(&newPrice)){
		updateInvalidInput(0);
	}
	
	//===============================================
	
	fp1 = fopen("Database\\Inventory.csv", "r");
	fp2 = fopen("Database\\copyInventory.csv","w");
	
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
						printf("%d\t", itemOnHold_itemID);
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
	
	printf("\n\nUpdated Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n%-10d\t%-10s\t%-10d\t%-10s\t%-10.2f\n", newItemID, newItemDesc, newQuantity, expiration, newPrice);
	
	printf("\nProceed with update?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	char ch;
	ch = getchar();
	scanf("%c", &ch);
	printf("I\'m right below the ch variable");
	if(!(ch=='y'|| ch=='Y')){
		updateInvalidInput(3);
		//abort();
	}
		
	int x, i;
		
	fp1 = fopen("Database\\Inventory.csv", "r");
	fp2 = fopen("Database\\copyInventory.csv","w");
	
	int scanCount = 0;
	//item1 *updatedInventory = malloc(sizeof(item1) * totalInventory); 
	
	tokenCount = 5;
	
	while(fgets(line,sizeof(line),fp1)){
		//printf("\nI\'m here inside the loop");
		char *token;
		token = strtok(line, s1);
		z = atoi(token);
		while (token != NULL){
			//printf("\nI\'ve entered another loop");
			if (z == newItemID){
				//printf("\nI\'ve entered z==newItem statement");
				int j;
				for (j = 0; j < 6; j++){
					//printf("\nI\'m in a for loop");
					token = strtok(NULL, s1);
				}
				fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, &expiration, newPrice);
				//printf("\nI\'m printing the new data: \n\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, newItemDesc, newQuantity, expiration, newPrice);
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
	
	
	fp1 = fopen("Database\\copyInventory.csv", "r");
	fp2 = fopen("Database\\Inventory.csv","w");
	
	tokenCount = 5;
	
	while(fgets(line,sizeof(line),fp1)){
		//printf("\nI\'m here inside the loop");
		char *token;
		token = strtok(line, s1);
		z = atoi(token);
		while (token != NULL){
			//printf("\nI\'ve entered another loop");
			if(tokenCount != 0){
				if (token = '-'){
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
				tokenCount = 6;
				token = strtok(NULL, s1);		
			}
		}
	}
	
	
	fclose(fp1);
	fclose(fp2);
		
	//remove("Database\\Inventory.csv"); printf("Old Database Deleted\n");
	//rename("Database\\copyInventory.csv", "Database\\Inventory.csv"); printf("New Database Renamed\n");
	
	updateSuccessful();

}


void testing(){
	int ch = 999999;
	char choice;
	do{
		clrscr();
		printf("THIS IS FOR TESTING PURPOSES\n[A] Add all the items from back-up dummy data\n[B] Update Inventory Item\n[C] Display all the Items in Inventory\n[X] Main menu\n\nPlease input Choice: ");
		scanf("%c", &choice);
		    
		switch(choice){
			case 'A':case 'a':{ 
				addAllFromBackUp(); break; }
			case 'B':case 'b':{ 
				updateInventoryMenu(); break; }
			case 'C':case 'c':{					
				clrscr(); displayAllItems(); break; }
			case 'X':case 'x':{
				mainMenu(); continue; break; }
	    	default:{
				ch = 999999; testing(); break; }
		}
		
	}
	while (choice==999999);
}

void mainMenu(){
	int ch = 999999;
	char choice;
	do{
		clrscr();
		printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[W] Enter Testing\n[X] Exit Program\n\nPlease input Choice: ");
		scanf("%c", &choice);
		    
		switch(choice){
			case 'A':case 'a':{
				ch = 999999; mainMenu(); break; }
			case 'B':case 'b':{
				updateInventoryMenu(); break; }
			case 'C':case 'c':{
				ch = 999999; mainMenu(); break; }
			case 'D':case 'd':{
				ch = 999999; mainMenu(); break; }
			case 'X':case 'x':{
				printf("System Terminated.");  exit(0);break; }
			case 'W':case 'w':{
				testing(); break; }
	    	default:{
				ch = 999999; mainMenu(); break; }
		}
		
	}
	while (choice==999999);
	//abort();
}

int main(){
    int sysInit = 0;
	FILE *fpointer = fopen("Database\\Inventory.csv", "r");
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
