#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


void clrscr()
{
    system("@cls||clear");
}

typedef struct item1{
	unsigned int itemID;
	char itemDesc;
	unsigned short quantity;
	char expiDate;
	float price;
}item1;

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
//void addAllFromBackUp();
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

/* 
//This command is for Testing
void addAllFromBackUp(){
	
	item *addTheBackUp;
	
	FILE *fpointer = fopen("Inventory.csv", "w+");
	FILE *fpointer2 = fopen("\\Inventory_ST_NoBOM.csv", "r");
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
	
	rename("Database\\Inventory.txt","Inventory.csv");
	
	fclose(fpointer);
	fclose(fpointer2);
	system("pause");
	mainMenu();
	
	}
}
*/

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

/*
//This command is for Testing
void displayAllItems(){
	int totalInventory;
	item1 item;
	int count;
	FILE *fp = fopen("Inventory.csv","r");
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
}
*/

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
    printf("\n\nPlease input Item Desc/Name:\t");
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
	do{
		FILE *fp = fopen("Inventory.csv","r");
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
			fclose(fp);
			int result = updateSearchDesc();
			if(result == 0){
	        	printf("\nItem Name does not exists.\n\n");
	        	updateAgain();
			}
			else{
				printf("\nPlease input Item ID of Item from the List:\t\t");
				scanf("%d", &ID);
				if ((ID<=0) || (ID>=100000)){
					updateInvalidInput(0);
					updateAgain();
					//abort();
				}
				else{
					fclose(fp);
					updateSelectedID(ID);
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
				if (newitemID != z){
					//printf("I'm inside updateCheckItemID funtion");
					printf("\n%d is a new Item ID\n\n", newitemID);
				}else if (newitemID == z){
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
				}
					fclose(fp);
					return 2;
					break;
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
	int result = updateCheckItemID(tempID, newItemID);
	if ((newItemID<=0) || (newItemID>=100000)){
		updateInvalidInput(9); //default "Input invalid"
	}
	else if(result == 2){
		updateInvalidInput(1); //itemID already taken
		//abort();
	}
	
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
	/*
	if ((isdigit(year))) {
		if ((isdigit(month))) {
			if ((isdigit(day))){ 
				sprintf(newExpiDate, '-');
			}
		}
	}else{
	*/
	if((isdigit(year)) || (isdigit(month)) || (isdigit(day))){
		sprintf(newExpiDate, "NULL");
	}
	else{			
		sprintf(newExpiDate, "%d-%d-%d", year, month, day);
	}
					
	printf("\nEnter new price:\t\t");
	scanf("%f",&newPrice);
	if (isdigit(&newPrice)){
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
		printf("\n\nNew Expiration date is : %s", newExpiDate);
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
			if (z == newItemID){
				//printf("\nI\'ve entered z==newItem statement");
				int j;
				for (j = 0; j < 6; j++){
					//printf("\nI\'m in a for loop");
					token = strtok(NULL, s1);
				}
				if (newExpiDate != NULL){
					fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, &newExpiDate, newPrice);
					//printf("\nI\'m printing the new data: \n\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, newItemDesc, newQuantity, &newExpiDate, newPrice);
				}else 
				if (newExpiDate == NULL){              
					fprintf(fp2, "\"%d\",\"%s\",\"%d\",\"-\",\"%.2f\"\n", newItemID, &newItemDesc, newQuantity, newPrice);
					//printf("\nI\'m printing the new data: \n\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", newItemID, newItemDesc, newQuantity, &newExpiDate, newPrice);
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
		//printf("\nI\'m here inside the loop");
		char *token;
		token = strtok(line, s1);
		z = atoi(token);
		while (token != NULL){
			//printf("\nI\'ve entered another loop");
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
	//remove("Inventory.csv"); printf("Old Database Deleted\n");
	//rename("copyInventory.csv", "Inventory.csv"); printf("New Database Renamed\n");
	
	updateSuccessful();

}

/*
//This is for Testing
void updateTesting(){
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
				ch = 999999; updateTesting(); break; }
		}
		
	}
	while (choice==999999);
}
*/

void mainMenu(){
	int ch = 999999;
	char choice;
	do{
		clrscr();
		printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[X] Exit Program\n\nPlease input Choice: ");
		
		// uncomment the line below for testing
		//printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[W] Enter Testing\n[X] Exit Program\n\nPlease input Choice: ");
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
			//case 'W':case 'w':{
			//	updateTesting(); break; }
	    	default:{
				ch = 999999; mainMenu(); break; }
		}
		
	}
	while (choice==999999);
}

int main(){
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
