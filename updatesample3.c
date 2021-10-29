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
	char itemDesc;
	int quantity;
	char expiration;
	float price;
}item;

void mainMenu();
void updateByDesc();
void updateAgain();
void updateInvalidInput(int invType);
void updateItem();
void updateInventory();

char* updateCheckingDate(int day,int month,int year);

int updateCheckItemID(int itemID, int count);
int updateByID(int ID);
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
	abort();

}

void updateAgain(){
	char ch;
	printf("Do you want to try updating an item again?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	getchar();
	scanf("%c",&ch);
	if(ch=='y'|| ch=='Y'){
		updateInventoryMenu();
		abort();
	}
	else{
		mainMenu();
		abort();
	}
	abort();
	
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
			abort();
			break;
		}
		case 2:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nNo Items Matched.\n\n");
			updateAgain();
			abort();
			break;
		}
		case 3:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nUpdate cancelled! Item NOT updated!\n\n");
			updateAgain();
			abort();
			break;
		}
		default:{		
			clrscr();
			printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nInvalid Input\n\n");
			updateAgain();
			abort();
			break;
		}
	}
		
	return;
}

void updateSuccessful(){
	clrscr();
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nUpdate Successful!\n\n");
	updateAgain();
	abort();
}

void updateItem(){
	
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
	token = strtok(line, delimit);
	int counter = 0;
	int i;
	
	while(fgets(line,sizeof(line),fpointer2)){
		
		addTheBackUp[i].itemID = atoi(token);
		token = strtok(NULL, delimit);
		addTheBackUp[i].itemDesc = token;
		token = strtok(NULL, delimit);
		addTheBackUp[i].quantity = atoi(token);
		token = strtok(NULL, delimit);
		addTheBackUp[i].expiration = token;
		token = strtok(NULL, delimit);
		addTheBackUp[i].price = atoi(token);
		token = strtok(NULL, delimit);
		counter++;
	}
	
	
	for (i = 0; i<500;i++){
		fprintf(fpointer, "\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", addTheBackUp[i].itemID, addTheBackUp[i].itemDesc, addTheBackUp[i].quantity, addTheBackUp[i].expiration, addTheBackUp[i].price);
		//fprintf(fp2, "\"%5d\",\"%30s\",\"%d\",\"%10s\",\"%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	}
	
	printf("\n\nInventory file reset!");
	
	//fprintf(fpointer, "11101,Nat. Spring (500mL),200,-,10.50\n11201,Nat. Spring (1L),100,-,16.00\n11202,Nat. Spring (1L),300,-,16.50\n12101,Datu Puti Vinegar (1L),100,2022-03-22,38.25\n51101,Nivea Silver Protect (50mL),50,2023-08-31,45.00\n");
	//fprintf(fpointer, "21101,Kalapati (500mL),200,-,10.50\n21201,Crocodile (1L),100,-,16.00\n21202,Nat. Lion (1L),300,-,16.50\n12101,22101 Daga Vinegar (1L),100,2022-03-22,38.25\n61101,Nivea Silver Anaconda,50,2023-08-31,45.00\n");
 	//fprintf(fpointer, "\"11101\",\"Nat. Spring (500mL)\",\"200\",\"-\",\"10.50\"\n\"11201\",\"Nat. Spring (1L)\",\"100\",\"-\",\"16.00\"\n\"11202\",\"Nat. Spring (1L)\",\"300\",\"-\",\"16.50\"\n\"12101\",\"Datu Puti Vinegar (1L)\",\"100\",\"2022-03-22\",\"38.25\"\n\"51101\",\"Nivea Silver Protect (50mL)\",\"50\",\"2023-08-31\",\"45.00\"\n");
	//fprintf(fpointer, "\"21101\",\"Kalapati\",\"200\",\"-\",\"10.50\"\n\"21201\",\"Crocodile\",\"100\",\"-\",\"16.00\"\n\"21202\",\"Lion\",\"300\",\"-\",\"16.50\"\n\"22101\",\"Daga\",\"100\",\"2022-03-22\",\"38.25\"\n\"61101\",\"Anaconda\",\"50\",\"2023-08-31\",\"45.00\"\n");
	
	fclose(fpointer);
	fclose(fpointer2);
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
	char inputDate = ("%d/%d/%d", year, month, day);
	char *otherString = inputDate;
	return otherString;
}


int totalInventory;
void display(){
	//printf("\n")
	int totalInventory;
	item1 item;
	int count;
	FILE *fp = fopen("Database\\Inventory.csv","r");
	//const char s1[5] = ",";
	const char s1[5] = "\",\"";
    char line[225];
	printf("MAIN MENU > UPDATE INVENTORY ITEM\nProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n");
	while(fgets(line,sizeof(line),fp)){
		char *token;
		count++;
        //char line[225];
		token = strtok(line, s1);
		while (token!=NULL){
			printf("%-10s", token);
			token = strtok(NULL, s1);
		}
		//printf("\n");
	}
	totalInventory = count;
    fclose(fp);
	printf("Total No. of items in the Inventory: \t %d\n\n", totalInventory);
    system("pause");
    clrscr();
    mainMenu();
	abort();
}


int updateSearch(int searchChoice){
	
	int sChoice = searchChoice;
	do{
	char itemDesc[20];
	char *x;
	int ID, found, z;
	int counter = 1;
	item1 item;
	FILE *fp = fopen("Database\\Inventory.csv","r");
	const char s1[5] = "\",\"";
			
	if (sChoice == 1){
		printf("\nPlease input Item ID:\t\t");
		scanf("%d", &ID);
		if ((ID<=0) || (ID>=100000)){
			updateInvalidInput(0);
			updateAgain();
			abort();
		}
		else{
		    char line[225];
			while(fgets(line,sizeof(line),fp)){
				while (ID != z) {
					counter++;
					char *token;
					token = strtok(line, s1);
					//int tempId = *token;
					z = atoi(token);
					//printf("temp is:\t%d\n",tempId);
					//printf("token is :\t%d\n",&token);
					//printf("X is :\t%d\n",&x);
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
						updateByID(z);
						abort();
					}
					token = strtok(NULL, s1);
					break;
				}
			}
			fclose(fp);
			if (found == 0){
				printf("\nNot found.");
			    fclose(fp);
				updateInvalidInput(0);
				updateAgain();
				abort();
			}
		    fclose(fp);
			updateInvalidInput(0);
			updateAgain();
		}
	}
	else if (sChoice == 2){
		printf("\n\nPlease Enter Item Desc:\t\t");
		scanf(" %[^\n]%*c", itemDesc);
		int j;
		for(j = 0; itemDesc[j] != '\0'; j++){
			if (itemDesc[j]>='a' && itemDesc[j]<='z' || itemDesc[j]>='A' && itemDesc[j]<='Z'){
			    char line[225];
				char *ret;
				ret = strstr(x, itemDesc);
				printf("The substring is: %s\n", ret);
				while(fgets(line,sizeof(line),fp)){
					while (!(strstr(x, itemDesc))) {
						counter++;
						char *token;
						token = strtok(line, s1);
						//int tempId = *token;
						x[10] = atoi(token);
						//printf("temp is:\t%d\n",tempId);
						//printf("token is :\t%d\n",&token);
						//printf("X is :\t%d\n",&x);
						if (ret){
							clrscr();
							printf("MAIN MENU > UPDATE INVENTORY ITEM\nYou will be updating:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
							while (token!=NULL){
				            	found = 1;
								printf("%-10s\t", token);
								token = strtok(NULL, s1);
							}
							ID = '\0';
				    		fclose(fp);
							abort();
						}
						token = strtok(NULL, s1);
						break;
					}
				}
				fclose(fp);
				if (found == 0){
					printf("\nNot found.");
				    fclose(fp);
					updateInvalidInput(0);
					updateAgain();
					abort();
				}
			}
			else{
				updateInvalidInput(0);
				updateAgain();
			}
		}
		    fclose(fp);
			updateInvalidInput(0);
			updateAgain();
		}
		//else{
		//	updateInvalidInput(0);
		//	updateAgain();
		//	abort();
		//}
	}while(sChoice!=0);
}


/*
void updateSearchByID(){
	int i;
	for(i=0;i<count;i++)
	{
		if(ino==ptr[i].itemID)
		{
			return i;
		}
	}
	return -1;
}
*/

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
			//int tempId = *token;
			z = atoi(token);
			//printf("temp is:\t%d\n",tempId);
			//printf("token is :\t%d\n",&token);
			//printf("X is :\t%d\n",&x);
			
			if ((newitemID != tempID) && (newitemID == z)){
				clrscr();
				printf("MAIN MENU > UPDATE INVENTORY ITEM\nThis Item ID is already taken by:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
				while (token!=NULL){
					//printf("%-10s\t", token);
					switch(tokenCount){
						case 0: {
							int otherInt = token;
							//strncpy existingID_itemID = otherInt;
							strcpy(existingID_itemID, otherInt);
							printf("%-10d\t", existingID_itemID);
							break;
						}
						case 1:{
							//existingID_itemDesc[30] = token;
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
							//existingID_expiDate[30] = token;
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

int updateByID(int ID){
	
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
	char expiration[10];
	
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
		
	//updateItem();
	//FILE *fp=fopen("Database\\Inventory.csv","w+");
	//fread(&product, sizeof(product),1,fp);
	//FILE *counter=fopen("counter.dat","r");
	//int count;
	//fscanf(counter,"%d",&count);
	//fclose(counter);
	
	//count = updateNoofRec();
	
	
	//This part is for user input and counterchecking if input is appropriate
	printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
	
	printf("\nEnter new Item ID:\t\t");
	scanf("%d",&newItemID);
	if (isdigit(&newItemID)){
			updateInvalidInput(9); //itemID already taken
	}
	else if(updateCheckItemID(tempID, newItemID) == 2){
			updateInvalidInput(1); //itemID already taken
			abort();
	}
	
	printf("\nEnter new Description:\t\t");
	scanf(" %[^\n]s", newItemDesc);
	printf("\nEnter new Quantity:\t\t");
	scanf("%d",&newQuantity);
	if (isdigit(&newQuantity)){
		updateInvalidInput(0);
	}
	
	printf("\nEnter new Expiration Date: (yyyy/mm/dd)\t\t");
	int year, month, day;
	scanf("%d/%d/%d",&year,&month,&day);
	if (year && month && day  != NULL){
		updateCheckingDate(year, month, day);
	}
	else{
		strcpy(expiration, "-");
	}
	
	printf("\nEnter new price:\t\t");
	scanf("%f",&newPrice);
	if (isdigit(&newQuantity)){
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
			//int tempId = *token;
			z = atoi(token);
			//printf("temp is:\t%d\n",tempId);
			//printf("token is :\t%d\n",&token);
			//printf("X is :\t%d\n",&x);
			if ((newItemID == itemID) && (z == itemID)){
				printf("MAIN MENU > UPDATE INVENTORY ITEM\nCurrent Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
				while (token!=NULL){
					//printf("%-10s\t", token);
					switch(tokenCount){
						case 1: {
							itemOnHold_itemID = atoi(token);
							//strcpy(itemOnHold_itemID, token);
							printf("%-10d\t", itemOnHold_itemID);
							break;
						}
						case 2:{
							//itemOnHold_itemDesc = token;
							strcpy(itemOnHold_itemDesc, token);
							//printf("mark lang malakas");
							printf("%-10s\t", itemOnHold_itemDesc);
							break;
						}
						case 3:{
							//itemOnHold_quantity = atoi(token);
							strcpy(itemOnHold_quantity, token);
							//printf("mark lang malakas");
							printf("%-10d\t", itemOnHold_quantity);
							break;
						}
						case 4:{
							//itemOnHold_expiDate[30] = token;
							strcpy(itemOnHold_expiDate, token);
							//printf("mark lang malakas");
							printf("%-10s\t", itemOnHold_expiDate);
							break;
						}
						case 5:{
							//printf("mark lang malakas");
							char *unconverted;
							double value = strtod(token, &unconverted);
							itemOnHold_price = value;
							printf("%-10.2f\t", itemOnHold_price);
							break;
						}
						default: {
							token = strtok(NULL, s1);
							break;
						}
					}
					tokenCount++;
					//token = strtok(NULL, s1);
				}
			}
		counter++;
		}
		
	fclose(fp1);
	fclose(fp2);
	
	totalInventory = counter;
	
	printf("\n\nUpdated Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n%-10d\t%-10s\t%-10d\t%-10s\t%-10.2f\n", newItemID, newItemDesc, newQuantity, expiration, newPrice);
		
	fp1 = fopen("Database\\Inventory.csv", "r");
	fp2 = fopen("Database\\copyInventory.csv","w");
		
		
	char ch;
	printf("\nProceed with update?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	getchar();
	scanf("%c",&ch);
	if(!(ch=='y'|| ch=='Y')){
		updateInvalidInput(3);
		abort();
	}
		
	int x, i;
	//item1 invUpdate;
	//int itemCount;
	//fscanf(fp3, "%i", &itemCount);
	printf("\nTotal No. of items:  %d\n", &totalInventory);
	int scanCount = 0;
	item1 *updatedInventory = malloc(sizeof(item1) * totalInventory); 
	
	for (i = 0; i < totalInventory; i++){
		
		char *currentDesc = malloc(sizeof(char)* (itemDescLen + 1));
		currentDesc[itemDescLen] = '\0';
		unsigned short currentItemID;
		unsigned short currentItemQua;
		char *currentItemExp = malloc(sizeof(char) * (11));  
		currentItemExp[10] = '\0';
		float currentItemPri;
		char expiration[10];
		
		while(!feof){
			while(fgets(line,sizeof(line),fp1)){
				char *token;
				token = strtok(line, s1);
				//int tempId = *token;
				z = atoi(token);
				//printf("temp is:\t%d\n",tempId);
				//printf("token is :\t%d\n",&token);
				//printf("X is :\t%d\n",&x);
			if (z != newItemID){
					printf("This is a test I've entered the if z != newItemID");
					while (token!=NULL){
						//printf("%-10s\t", token);
						switch(tokenCount){
							case 1: {
								updatedInventory[counter].itemID = atoi(token);
								//strcpy(itemOnHold_itemID, token);
								printf("%-10d\t", updatedInventory[counter].itemID);
								break;
							}
							case 2:{
								//itemOnHold_itemDesc = token;
								strcpy(updatedInventory[counter].itemDesc, token);
								//printf("mark lang malakas");
								printf("%-10s\t", updatedInventory[counter].itemDesc);
							break;
								}
							case 3:{
								//itemOnHold_quantity = atoi(token);
								strcpy(updatedInventory[counter].quantity, token);
								//printf("mark lang malakas");
								printf("%-10d\t", itemOnHold_quantity);
								break;
							}
							case 4:{
								//itemOnHold_expiDate[30] = token;
								strcpy(updatedInventory[counter].expiDate, token);
								//printf("mark lang malakas");
								printf("%-10s\t", itemOnHold_expiDate);
								break;
							}
							case 5:{
								//printf("mark lang malakas");
								char *unconverted;
								double value = strtod(token, &unconverted);
								updatedInventory[counter].price = value;
								printf("%-10.2f\t", updatedInventory[counter].price);
								break;
							}
							default: {
								token = strtok(NULL, s1);
								break;
							}
						}
						tokenCount++;
					//token = strtok(NULL, s1);
					}
					
					printf("\nI'm copying old data\n");
					printf("\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"\n", updatedInventory[counter].itemID, updatedInventory[counter].itemDesc, updatedInventory[counter].quantity, updatedInventory[counter].expiDate, updatedInventory[counter].price);
		
				}
				else{
					updatedInventory[scanCount].itemID = newItemID;
					strcpy(updatedInventory[scanCount].itemDesc, newItemDesc);
					updatedInventory[scanCount].quantity = newQuantity;
					strcpy(updatedInventory[scanCount].expiDate, expiration);
					updatedInventory[scanCount].price = newPrice;
					
					
				printf("\nI'm copying new data\n");
				printf("%5d, %s, %d, %s, %.2f\n", updatedInventory[updateCount].itemID, updatedInventory[updateCount].itemDesc, updatedInventory[updateCount].quantity, updatedInventory[updateCount].expiDate, updatedInventory[updateCount].price);
				
				}
			}
		}
		
		/*fscanf(fp1, "\"%d\",\"%s\",\"%d\",\"%s\",\"%.2f\"", &currentItemID, currentDesc, &currentItemQua, currentItemExp, &currentItemPri);
			
		if (itemID != currentItemID){
			updatedInventory[scanCount].itemID = currentItemID;
			strcpy(updatedInventory[scanCount].itemDesc, currentDesc);
			updatedInventory[scanCount].quantity = currentItemQua;
			strcpy(updatedInventory[scanCount].expiDate, currentItemExp);
			updatedInventory[scanCount].price = currentItemPri;
		}
		else{
			updatedInventory[scanCount].itemID = newItemID;
			strcpy(updatedInventory[scanCount].itemDesc, newItemDesc);
			updatedInventory[scanCount].quantity = newQuantity;
			strcpy(updatedInventory[scanCount].expiDate, expiration);
			updatedInventory[scanCount].price = newPrice;
		}
		scanCount++;
		
		/*
		while(fgets(line,sizeof(line),fp1)){
			char *token;
	        //char line[225];
			token = strtok(line, s1);
			while (token!=NULL){
				printf("\t%-10s", token);
				token = strtok(NULL, s1);
		}
		*/
	}
	
	for (i = 0; i < totalInventory; i++){
		printf("\"%5d\",\"%s\",\"%d\",\"%s\",%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
		//fprintf(fp4, "%i", updateCount);		
		fprintf(fp2, "\"%5d\",\"%30s\",\"%d\",\"%10s\",\"%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	}
	system("pause");
	
		
		fclose(fp1);
		fclose(fp2);
	
		//const char s1[5] = "\",\"";
		/*
	fp1 = fopen("Database\\Inventory.csv", "r");
	fp2 = fopen("Database\\copyInventory.csv","w");
	
	
	updatedInventory= malloc(sizeof(item1) * totalInventory);
	counter = 0;
	tokenCount = 0;
	while(!feof){
		while(fgets(line,sizeof(line),fp1)){
			while (tempID != z) {
				char *token;
				token = strtok(line, s1);
				z = atoi(token);
				
				if (z!=newItemID){
					while (token!=NULL){
						switch(tokenCount){
							case 0: {
								updatedInventory[counter].itemID = token;
								break;
							}
							case 1:{
								strcpy(updatedInventory[counter].itemDesc, token);
								break;
							}
							case 2:{
								updatedInventory[counter].quantity = token;
								break;
							}
							case 3:{
								strcpy(updatedInventory[counter].expiDate, token);
								break;
							}
							case 4:{
								char *unconverted;
								double value = strtod(token, &unconverted);
								updatedInventory[counter].price = value;
								break;
							}
							default: {
								token = strtok(NULL, s1);
								break;
							}
						}
						printf("\nI'm copying old data\n");
						printf("\"%d\",\"%30s\",\"%d\",\"%s\",\"%.2f\"\n", updatedInventory[counter].itemID, updatedInventory[counter].itemDesc, updatedInventory[counter].quantity, updatedInventory[counter].expiDate, updatedInventory[counter].price);
		
						tokenCount++;
						token = strtok(NULL, s1);
					}
				}else{
					strcpy(updatedInventory[counter].itemDesc, newItemDesc);
					updatedInventory[counter].itemID = newItemID;
					updatedInventory[counter].quantity = newQuantity;
					
					// This is for converting struct date into string
					memcpy(expiration, &newExpiDate, sizeof expiration);
					strcpy(updatedInventory[counter].expiDate, expiration);
					//===============================
					
					//strcpy(updatedInventory[counter].expiDate, newExpiDate);
					updatedInventory[counter].price = newPrice;
					
					printf("\nI'm copying new data\n");
					printf("\"%d\",\"%30s\",\"%d\",\"%s\",\"%.2f\"\n", updatedInventory[counter].itemID, updatedInventory[counter].itemDesc, updatedInventory[counter].quantity, updatedInventory[counter].expiDate, updatedInventory[counter].price);
					tokenCount++;
				}
				counter++;
				fclose(fp1);
				fclose(fp2);
				break;
			}
		}
	}
	system("pause");
		/*
		
		for (i = 0; i < itemCount; i++){
			
			// This is for converting struct date into string
			memcpy(expiration, &newExpiDate, sizeof expiration);
			strcpy(updatedInventory[itemCount].expiDate, expiration);
			//===============================
			
			//fscanf(fp1, "%5d,%[^\n]%*c,%d,%s,%.2f", &itemID, desc, &currentItemQua, currentItemExp, &currentItemPri);
			//fscanf(fp1, "%5d %s %d %s %.2f", itemID, desc, currentItemQua, currentItemExp, currentItemPri);
			fscanf(fp1, "%5d\",\" %s\",\" %d\",\" %s\",\" %.2f", itemID, desc, currentItemQua, currentItemExp, currentItemPri);
			printf("\nI got this from scan");
			printf("\nitemID \t\t%d", itemID);
			printf("\ndesc \t\t%s", desc);
			printf("\ncurrentItemQua \t%d", currentItemQua);
			printf("\ncurrentItemExp \t%s", &currentItemExp);
			printf("\ncurrentItemPri \t%.2f", currentItemPri);
			printf("\n");
			printf("\nHere are some inputted data\n%s\t%d\t%d\t%s\t%.2f\n", newItemDesc, newItemID, newQuantity, expiration, newPrice);
			system("pause");
			
			if (itemID!=newItemID){
				//fscanf(fp1, "%5d, %s, %d, %s, %.2f", &itemID, desc, &currentItemQua, currentItemExp, &currentItemPri);
				fscanf(fp1, "\"%5d\", \"%s\", \"%d\", \"%s\", \"%.2f\"", itemID, &desc, currentItemQua, currentItemExp, currentItemPri);
				strcpy(updatedInventory[updateCount].itemDesc, desc);
				updatedInventory[updateCount].itemID = currentItemID;
				updatedInventory[updateCount].quantity = currentItemQua;
			
				// This is for converting struct date into string
				memcpy(expiration, &currentItemExp, sizeof expiration);
				strcpy(updatedInventory[updateCount].expiDate, expiration);
				//===============================
				
				updatedInventory[updateCount].price = currentItemPri;
				
				printf("\nI'm copying old data\n");
				printf("%5d, %s, %d, %s, %.2f\n", updatedInventory[updateCount].itemID, updatedInventory[updateCount].itemDesc, updatedInventory[updateCount].quantity, updatedInventory[updateCount].expiDate, updatedInventory[updateCount].price);	
				system("pause");	
				updateCount++;
				break;
			}else{
				strcpy(updatedInventory[itemCount].itemDesc, newItemDesc);
				updatedInventory[itemCount].itemID = newItemID;
				updatedInventory[itemCount].quantity = newQuantity;
				
				// This is for converting struct date into string
				memcpy(expiration, &newExpiDate, sizeof expiration);
				strcpy(updatedInventory[itemCount].expiDate, expiration);
				//===============================
				
				updatedInventory[itemCount].price = newPrice;
				
				printf("\nI'm copying new data\n");
				printf("%5d, %s, %d, %s, %.2f\n", updatedInventory[updateCount].itemID, updatedInventory[updateCount].itemDesc, updatedInventory[updateCount].quantity, updatedInventory[updateCount].expiDate, updatedInventory[updateCount].price);
				updateCount++;
			}
			
		}
		
		*/
	//printf("\nHere is the updateCount: %d\n", updateCount);
	//int i;
	//for (i = 0; i<totalInventory;i++){
	//	printf("\"%5d\",\"%s\",\"%d\",\"%s\",%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	//	//fprintf(fp4, "%i", updateCount);		
	//	fprintf(fp2, "\"%5d\",\"%30s\",\"%d\",\"%10s\",\"%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	//}
		
		
	//counter = 0;
	//tokenCount = 0;
	//while(fgets(line,counter,fp1)){
	//	printf("\"%5d\",\"%s\",\"%d\",\"%s\",%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	//	//fprintf(fp4, "%i", updateCount);		
	//	fprintf(fp2, "\"%5d\",\"%s\",\"%d\",\"%s\",%.2f\"\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	//}
		
		fclose(fp1);
		fclose(fp2);
		//remove("Database\\Inventory.csv");
		rename("Database\\copyInventory.csv","Database\\Inventory.csv");
		remove("Database\\counter.csv");
		rename("Database\\control.csv","Database\\counter.csv");
		updateSuccessful();
	
		
}


/*
void updateByDesc(){
	char itemDesc[50];
	printf("\n\nPlease Enter Item Desc: ");
	scanf("%[^\n]s", &itemDesc);
	if (itemDesc == ""){
		updateInvalidInput(0);
	}
	else{
		updateInvalidInput(0);
	}
	abort();
}
*/


void mainMenu(){
	int ch = 999999;
	char choice;
	do{
		//printf("\n");
		clrscr();
		printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[X] Exit Program\n\nPlease input Choice: ");
		scanf("%c", &choice);
		    switch(choice){
				case 'A':case 'a':{ 
					updateItem(); break; }
				case 'B':case 'b':{ 
					printf("Your input is %c", choice);  updateInventoryMenu(); break; }
				case 'C':case 'c':{					
					printf("Your input is %c", choice); clrscr(); display(); break; }
				case 'D':case 'd':{					
					printf("Your input is %c", choice); break; }
				case 'X':case 'x':{
					printf("System Terminated.");  exit(0); continue; break; }
		    	default:{					
					//printf("This is default."); 
					ch = 999999; mainMenu(); break; }
			}
			
			
		    /* 
		    clrscr();
		    char userCommand;
			printf("MAIN MENU\n[A] Add Inventory Item\n[B] Update Inventory Item\n[C] View Inventory Item\n[D] Delete Inventory Item\n[X] Exit Program\n\nPlease input Choice: ");
			getchar();
			userCommand = getchar();
			scanf("%c", userCommand);
			
		    switch(userCommand)
			{
		    	case 'A':
				case 'a':{
					printf("Your input is %c", userCommand); 
					break;
					}
		    	case 'B':
				case 'b':{                                                 
					printf("Your input is %c", userCommand); 
					updateInventoryMenu(); break;
					}
		    	case 'C':
				case 'c':{
					printf("Your input is %c", userCommand); 
					break;
					}
		    	case 'D':
				case 'd':{
					printf("Your input is %c", userCommand); 
					break;
					}
		    	case 'X':
				case 'x':{
					printf("System Terminated", userCommand);
					break;
					}
		    	default:
					printf("This is default.", userCommand); 
					break;
			} */
	}
	while (choice==999999);
	abort();
}

int main(){
    //
    int sysInit = 0;
    //while(sysInit == 0){
	FILE *fpointer = fopen("Database\\Inventory.csv", "r");
	if(!fpointer){
		printf("\nInventory file does not exist!");
		return 0;
	}
	else{
		fclose(fpointer);
		mainMenu();
	}
	//}
	return 0;    
}
