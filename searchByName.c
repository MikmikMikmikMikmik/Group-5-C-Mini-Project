#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 1024       /* if you need a constant, #define one (or more) */
#define DELIM ",\n"


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
	char itemDesc[20];
	int quantity;
	date expiration;
	float price;
}item;

void mainMenu();
void updateByDesc();
void updateAgain();
void updateInvalidInput();
void updateItem();
void updateInventory();
//void updateSearchByID();
void updateCheckingDate(int day,int month,int year);
void updateNoofRec();
//RAVEN
void viewInventory();
void searchMenu();
void searchByID();
void searchByName();
void searchByName2();
void viewAllProducts();

int updateCheckItemID(int itemID, int count);
int updateByID(int ID);
int updateSearch();

void updateInventoryMenu(){
	clrscr();
	printf("MAIN MENU > ADD INVENTORY ITEM\n");
	printf("SEARCH BY?\n");
	printf("[1]PRODUCT ID\n[2]PRODUCT NAME/DESCRIPTION\n[0]CANCEL UPDATE\n\n Please input choice: ");
	int choice;
	scanf("%d",&choice);

	switch (choice){
		case 0: {
			mainMenu(); break;
		}
		case 1: {
			updateSearch(1); break;
		}
		case 2: {
			updateSearch(2); break;
		}
		default:{
			clrscr();
			printf("\nInvalid choice!!");
			updateInventoryMenu();
		}
	}
}

void updateAgain(){
	char ch;
	printf("\nDo you want to try updating an item again?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
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

void updateInvalidInput(){
	clrscr();
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n");
	printf("\nInvalid Input");
	updateAgain();
	abort();
}

void updateSuccessful(){
	clrscr();
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n");
	printf("\nUpdate Successfully");
	updateAgain();
	abort();
}

void updateItem(){
	
	FILE *fpointer = fopen("Database\\Inventory.csv", "w+");
	if(!fpointer){
		printf("\nInventory file does not exist!");
	}
	
	fprintf(fpointer, "11101,Nat. Spring (500mL),200,-,10.50\n11201,Nat. Spring (1L),100,-,16.00\n11202,Nat. Spring (1L),300,-,16.50\n12101,Datu Puti Vinegar (1L),100,2022-03-22,38.25\n51101,Nivea Silver Protect (50mL),50,2023-08-31,45.00\n");
	fprintf(fpointer, "21101,Kalapati (500mL),200,-,10.50\n21201,Crocodile (1L),100,-,16.00\n21202,Nat. Lion (1L),300,-,16.50\n12101,22101 Daga Vinegar (1L),100,2022-03-22,38.25\n61101,Nivea Silver Anaconda,50,2023-08-31,45.00\n11111,Anaconda Elite,88,2020-08-30,77.00\n");
 //fprintf(fpointer, "\"11101\",\"Nat. Spring (500mL)\",\"200\",\"-\",\"10.50\"\n\"11201\",\"Nat. Spring (1L)\",\"100\",\"-\",\"16.00\"\n\"11202\",\"Nat. Spring (1L)\",\"300\",\"-\",\"16.50\"\n\"12101\",\"Datu Puti Vinegar (1L)\",\"100\",\"2022-03-22\",\"38.25\"\n\"51101\",\"Nivea Silver Protect (50mL)\",\"50\",\"2023-08-31\",\"45.00\"\n");
	//fprintf(fpointer, "\"21101\",\"Kalapati\",\"200\",\"-\",\"10.50\"\n\"21201\",\"Crocodile\",\"100\",\"-\",\"16.00\"\n\"21202\",\"Lion\",\"300\",\"-\",\"16.50\"\n\"22101\",\"Daga\",\"100\",\"2022-03-22\",\"38.25\"\n\"61101\",\"Anaconda\",\"50\",\"2023-08-31\",\"45.00\"\n");
	
	fclose(fpointer);
}


void updateNoofRec(){
	item1 item;
	FILE *fp;
	fp = fopen("Database\\Inventory.csv","r");
	fseek(fp,0,SEEK_END);
	int total = ftell(fp)/sizeof(item1);
	printf("\n\nThere are %d total items in the inventory", total);
	fclose(fp);
	printf("\n");
    system("pause");
    mainMenu();
	abort();
}

int updateCheckItemID(int itemID, int count)
{
	item product[100];
	FILE *fp=fopen("Database\\Inventory.csv","rb");
	fread(&product, sizeof(product), 1, fp);

	int i; for(i=0;i<count;i++)
	{
		if(itemID==product[i].itemID)
		{
	    	fclose(fp);
			return itemID;
		}
	}
	fclose(fp);
	return itemID;
}

void updateCheckingDate(int day,int month,int year)
{
	if( (day>30 && month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		updateInvalidInput();
	}
	if( (day>31 && month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		updateInvalidInput();
	}
	if( (day>29 && month == 2))
	{
		printf("\nInvalid date\nPlease enter details again\n");
	}
	if (year<0 || year>2500)
	{
		printf("\nInvalid date\nPlease enter details again\n");
		updateInvalidInput();
	}
	if (month<1 || month>12)
	{
		printf("\nInvalid date\nPlease enter details again");
		updateInvalidInput();
	}
}

void display(){
	//printf("\n");
	item1 item;
	FILE *fp = fopen("Database\\Inventory.csv","r");
	const char s1[5] = ",";
    char line[225];
	printf("MAIN MENU > UPDATE INVENTORY ITEM\nProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n");
	while(fgets(line,sizeof(line),fp)){
		char *token;
        //char line[225];
		token = strtok(line, s1);
		while (token!=NULL){
			printf("\t%-10s", token);
			token = strtok(NULL, s1);
		}
		printf("\n");
	}
    fclose(fp);
    updateNoofRec();
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
		printf("\n\nPlease input Item ID:\t\t");
		scanf("%d", &ID);
		if ((ID<=0) || (ID>=100000)){
			updateInvalidInput();
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
					//else if(ID = 999999){
					//		printf("\nNo ID found.");
					//		break;}
					printf("\nControl got here.");
					break;
				}
			}
			fclose(fp);
			if (found == 0){
				printf("\nNot found.");
			    fclose(fp);
				updateInvalidInput();
				updateAgain();
				abort();
			}
		    fclose(fp);
			updateInvalidInput();
			updateAgain();
		}
	}
	else if (sChoice == 2) {
		printf("\n\nPlease Enter Item Desc:\t\t");
		printf("tanga");
		scanf(" %[^\n]%*c", itemDesc);
		int j;
		for(j = 0; itemDesc[j] != '\0'; j++){
		printf("tanga\t");
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
						//else if(ID = 999999){
						//		printf("\nNo ID found.");
						//		break;}
						printf("\nControl got here.");
						break;
					}
				}
				fclose(fp);
				if (found == 0){
					printf("\nNot found.");
				    fclose(fp);
					updateInvalidInput();
					updateAgain();
					abort();
				}
			}
			else{
				updateInvalidInput();
				updateAgain();
			}
		}
		    fclose(fp);
			updateInvalidInput();
			updateAgain();
		}
		//else{
		//	updateInvalidInput();
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

int updateByID(int ID){
	
	item1 product;
	int location;
	int count;
	int itemID = ID;
		
	//updateItem();
	//FILE *fp=fopen("Database\\Inventory.csv","w+");
	//fread(&product, sizeof(product),1,fp);
	//FILE *counter=fopen("counter.dat","r");
	//int count;
	//fscanf(counter,"%d",&count);
	//fclose(counter);

	int newItemID;
	char newItemDesc[20];
	int newQuantity;
	date newExpiDate;
	float newPrice;
	//count = updateNoofRec();
	
	printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
	printf("\nEnter new Item ID:\t\t");
	scanf("%d",&newItemID);
	printf("\nEnter new Description:\t\t");
	scanf(" %[^\n]%*c", &newItemDesc);
	printf("\nEnter new Quantity:\t\t");
	scanf("%d",&newQuantity);
	printf("\nEnter new Expiration Date: (yyyy/mm/dd)\t\t");
	scanf("%d/%d/%d",&newExpiDate.year,&newExpiDate.month,&newExpiDate.day);
	updateCheckingDate(newExpiDate.year,newExpiDate.month,newExpiDate.day);
	printf("\nEnter new price:\t\t");
	scanf("%f",&newPrice);
	
	//===============================================
	
	int x;
	item1 invUpdate;
	FILE *fp1 = fopen("Database\\Inventory.csv", "r");
	FILE *fp2 = fopen("Database\\copyInventory.csv","w");
	int itemCount;
	fscanf(fp1, "%i", &itemCount);
	printf("\nThis is the itemCount:  %d\n", &itemCount);
	item1 *updatedInventory = malloc(sizeof(item1) * itemCount);
	
	//const char s1[5] = "\",\"";
	int updateCount;
	int i;
	
	for (i = 0; i < itemCount; i++){
		
		int itemDescLen;
		
		fscanf(fp1, "%i", &itemDescLen);
		
		char *desc = malloc(sizeof(char)* (itemDescLen + 1));
		desc[itemDescLen] = '\0';
		unsigned short currentItemID;
		unsigned short currentItemQua;
		char *currentItemExp = malloc(sizeof(char)*(11));
		float currentItemPri;
		char expiration[10];
		
		fscanf(fp1, "%5d,%[^\n]%*c,%d,%s,%.2f", &itemID, desc, currentItemQua, &currentItemExp, currentItemPri);
		printf("\nI got some data\n%s\t%d\t%d\t%s\t%.2f\n", &desc, itemID, currentItemQua, currentItemExp, currentItemPri);
		printf("\nI got some data\n%s\t%d\t%d\t%s\t%.2f\n", newItemDesc, newItemID, newQuantity, newExpiDate, newPrice);
		system("pause");
		if (!(itemID==newItemID)){
			strcpy(updatedInventory[updateCount].itemDesc, desc);
			updatedInventory[updateCount].itemID = currentItemID;
			updatedInventory[updateCount].quantity = currentItemQua;
		
			// This is for converting struct date into string
			memcpy(expiration, &currentItemExp, sizeof expiration);
			strcpy(updatedInventory[updateCount].expiDate, expiration);
			//===============================
			
			updatedInventory[updateCount].price = currentItemPri;
			
			printf("\nI'm copying old data\n");
			printf("%5d,%s,%d,%s,%.2f\n", updatedInventory[itemCount].itemID, updatedInventory[itemCount].itemDesc, updatedInventory[itemCount].quantity, updatedInventory[itemCount].expiDate, updatedInventory[itemCount].price);	
			system("pause");	
			updateCount++;
		}else{
			strcpy(updatedInventory[itemCount].itemDesc, newItemDesc);
			updatedInventory[itemCount].itemID = newItemID;
			updatedInventory[itemCount].quantity = newQuantity;
			
			// This is for converting struct date into string
			memcpy(expiration, &newExpiDate, sizeof expiration);
			strcpy(updatedInventory[itemCount].expiDate, expiration);
			//===============================
			
			updatedInventory[itemCount].price = newPrice;
			
			updateCount++;
			
			printf("\nI'm copying new data\n");
			printf("%5d,%s,%d,%s,%.2f\n", updatedInventory[updateCount].itemID, updatedInventory[updateCount].itemDesc, updatedInventory[updateCount].quantity, updatedInventory[updateCount].expiDate, updatedInventory[updateCount].price);	
			
		}
		
	}
	printf("\nHere is the updateCount: %d\n", updateCount);
	for (i = 0; i<itemCount;i++){
		printf("%5d,%s,%d,%s,%.2f\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);		
		fprintf(fp2, "%5d,%s,%d,%s,%.2f\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
	}
	fclose(fp1);
	fclose(fp2);
	remove("Database\\Inventory.csv");
	rename("Database\\copyInventory.csv","Database\\Inventory.csv");
	updateSuccessful();
}


/*
void updateByDesc(){
	char itemDesc[50];
	printf("\n\nPlease Enter Item Desc: ");
	scanf("%[^\n]s", &itemDesc);
	if (itemDesc == ""){
		updateInvalidInput();
	}
	else{
		updateInvalidInput();
	}
	abort();
}
*/


void mainMenu() {
	int choice = 999999;
	do{
		//printf("\n");
		clrscr();
		printf("MAIN MENU\n[1] Add Inventory Item\n[2] Update Inventory Item\n[3] View Inventory Item\n[4] Delete Inventory Item\n[0] Exit Program\n\nPlease input Choice: ");
		scanf("%d", &choice);
		    switch(choice){
				case 1:{ 
					viewAllProducts(); break; }
				case 2:{ 
					printf("Your input is %d", choice);  updateInventoryMenu(); break; }
				case 3:{					
					printf("Your input is %d", choice); clrscr(); viewInventory(); break; } // raven
				case 4:{					
					printf("Your input is %d", choice); break; }
				case 0:{
					printf("System Terminated.");  choice = 0; continue; break; }
		    	default:{					
					//printf("This is default."); 
					choice = 999999; break; }
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
//RAVEN
void viewInventory() {
    clrscr();
    char choice;
    printf("VIEW INVENTORY\n");
    printf("[A] View All\n");
    printf("[B] Search for an Inventory Item\n");
    printf("[C] Back to Menu\n");
    printf("Choice: ");
    
    fflush(stdin);
    scanf("%c", &choice);

    printf("%c", &choice);
    if(choice == 'A') {
       viewAllProducts();
    }
    else if(choice == 'B') {
        searchMenu();
    }   
    else if(choice == 'C')   {
        
    }
}

void searchByID() {
    clrscr();
    FILE *fp = fopen("Inventory_ST.csv","r");
    int ID, z, found = 0;
    int counter = 1;
    const char s1[5] = "\",\"";
    
    
    printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\n");
    printf("Enter Product ID to Search: ");
    scanf("%d", &ID);
    if ((ID<=0) || (ID>=100000)) {
        printf("\nInvalid Input\n");
        system("pause");
        searchMenu();
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
					printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
					while (token!=NULL){
						found = 1;
						printf("%-10s\t", token);
						token = strtok(NULL, s1);
					}
					ID = '\0';
					fclose(fp);
				}
				token = strtok(NULL, s1);
				//else if(ID = 999999){
				//		printf("\nNo ID found.");
				//		break;}
				
				break;
			}
		}
		fclose(fp);
		if (found == 0){
			printf("\nNot found.\n\n");
			fclose(fp);
			system("pause");
			searchMenu();
		}
		printf("\n");
		system("pause");
		searchMenu();	
		fclose(fp);
    }
}

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void searchByName() {
    clrscr();
    int found = 0;
    FILE* stream = fopen("Database\\Inventory.csv", "r");

    char pName[30];
    printf("SEARCH FOR AN INVENTORY ITEM > by Item Name\n\n");
    printf("Enter Product Name to Search: ");
    fflush(stdin);
    scanf("%[^\n]s",pName);

    char line[200];
    while (fgets(line, sizeof(line), stream))
    {
        char* tmp = strdup(line);

        printf("Item names are: %s\n", getfield(tmp,2));
            
        free(tmp);

    }
    printf("%d", found);
    fclose(stream);
}

void searchByName2() {
    clrscr();
    int found = 0;
    FILE* stream = fopen("Inventory_ST.csv", "r");

	char line[225];
	const char delims[5] = "\",\"";
	char *token;
	char *token2;
    char pName[100];
    printf("SEARCH FOR AN INVENTORY ITEM > by Item Name\n\n");
    printf("Enter Product Name to Search: ");
    fflush(stdin);
    scanf("%[^\n]s",pName);

	printf("Product ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
	while(fgets(line,sizeof(line),stream)){
		char lineMemory[225]; strcpy(lineMemory, line);
		token = strtok(line, delims);

		token = strtok(NULL, delims);
		if(strcmp(token, pName) == 0 ){
			token2 = strtok(lineMemory, delims);
			while(token2!=NULL) {
				found = 1;
				printf("%-10s\t", token2);
				token2 = strtok(NULL, delims);
			}
		}
	}
	
	if(!found) {
        printf("\nRecord Not Found\n\n");
        system("pause");
        searchMenu();
    }
    
    printf("\n\n");
    system("pause");
    searchMenu();
    fclose(stream);
}

void viewAllProducts(){
    FILE *fp = fopen("Inventory_ST.csv","r");
    if(fp == NULL) {
        perror("Unable to open");
        exit(1);
    }
    char line[200];
    while(fgets(line,sizeof(line),fp)) {
        char *token;
        token = strtok(line, ",");

        while(token!=NULL){
            printf("%-12s", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }
}

void searchMenu() {
    clrscr();
    char choice;
    printf("SEARCH FOR AN INVENTORY ITEM\n");
    printf("[A] SEARCH BY PRODUCT ID\n");
    printf("[B] SEARCH BY PRODUCT NAME/DESCRIPTION\n");
    printf("[C] BACK TO VIEW INVENTORY MENU\n");
    printf("\nPlease input choice: ");
    fflush(stdin);
    scanf("%c", &choice);

    printf("%c", &choice);
    if(choice == 'A') {
       searchByID();
    }
    else if(choice == 'B') {
        searchByName2();
    }
    else if(choice == 'C') {
        viewInventory();
    }
    else {
        printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
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