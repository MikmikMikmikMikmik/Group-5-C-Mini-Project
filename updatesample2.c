#include <stdio.h>
#include <stdlib.h>
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

int updateCheckItemID(int itemID, int count);
int updateByID(int ID);
int updateSearch();

void updateInventoryMenu(){
	clrscr();
	printf("MAIN MENU > ADD INVENTORY ITEM\nSEARCH BY?\n[A]PRODUCT ID\n[B]PRODUCT NAME/DESCRIPTION\n[X]CANCEL UPDATE\n\n Please input choice: ");
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
		}
	}
}

void updateAgain(){
	clrscr();
	char ch;
	printf("\nMAIN MENU > UPDATE INVENTORY ITEM\nDo you want to try updating an item again?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
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
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nInvalid Input");
	updateAgain();
	abort();
}

void updateSuccessful(){
	clrscr();
	printf("MAIN MENU > UPDATE INVENTORY ITEM\n\nUpdate Successfully");
	updateAgain();
	abort();
}

void updateItem(){
	
	FILE *fpointer = fopen("Database\\Inventory.csv", "w+");
	if(!fpointer){
		printf("\nInventory file does not exist!");
	}
	
	//fprintf(fpointer, "11101,Nat. Spring (500mL),200,-,10.50\n11201,Nat. Spring (1L),100,-,16.00\n11202,Nat. Spring (1L),300,-,16.50\n12101,Datu Puti Vinegar (1L),100,2022-03-22,38.25\n51101,Nivea Silver Protect (50mL),50,2023-08-31,45.00\n");
	//fprintf(fpointer, "21101,Kalapati (500mL),200,-,10.50\n21201,Crocodile (1L),100,-,16.00\n21202,Nat. Lion (1L),300,-,16.50\n12101,22101 Daga Vinegar (1L),100,2022-03-22,38.25\n61101,Nivea Silver Anaconda,50,2023-08-31,45.00\n");
 	fprintf(fpointer, "\"11101\",\"Nat. Spring (500mL)\",\"200\",\"-\",\"10.50\"\n\"11201\",\"Nat. Spring (1L)\",\"100\",\"-\",\"16.00\"\n\"11202\",\"Nat. Spring (1L)\",\"300\",\"-\",\"16.50\"\n\"12101\",\"Datu Puti Vinegar (1L)\",\"100\",\"2022-03-22\",\"38.25\"\n\"51101\",\"Nivea Silver Protect (50mL)\",\"50\",\"2023-08-31\",\"45.00\"\n");
	fprintf(fpointer, "\"21101\",\"Kalapati\",\"200\",\"-\",\"10.50\"\n\"21201\",\"Crocodile\",\"100\",\"-\",\"16.00\"\n\"21202\",\"Lion\",\"300\",\"-\",\"16.50\"\n\"22101\",\"Daga\",\"100\",\"2022-03-22\",\"38.25\"\n\"61101\",\"Anaconda\",\"50\",\"2023-08-31\",\"45.00\"\n");
	
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
	//const char s1[5] = ",";
	const char s1[5] = "\",\"";
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
	else if (sChoice == 2){
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

int updateCheckItemID(int ID, int newID){
	
	int tempID = ID; 
	int newitemID = newID;
	
	FILE *fp1 = fopen("Database\\Inventory.csv", "r");
	
	//This variable is to hold old details of item to be updated
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
							//existingID_itemID = token;
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
							//existingID_quantity = token;
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
	unsigned short currentItemID;
	unsigned short currentItemQua;
	char *currentItemExp = malloc(sizeof(char) * (11));  
	currentItemExp[10] = '\0';
	float currentItemPri;
	char expiration[10];
	
	//These are variable for new details of item to be updated
	int newItemID;
	char newItemDesc[20];
	int newQuantity;
	date newExpiDate;
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
	
	printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
	printf("\nEnter new Item ID:\t\t");
	scanf("%d",&newItemID);
	if(checkUpdateItemID(tempID, newItemID) == 2){
				updateAgain();
				abort();
	}
	printf("\nEnter new Description:\t\t");
	scanf(" %[^\n]%*c", &newItemDesc);
	printf("\nEnter new Quantity:\t\t");
	scanf("%d",&newQuantity);
	printf("\nEnter new Expiration Date: (yyyy/mm/dd)\t\t");
	scanf("%d/%d/%d",&newExpiDate.year,&newExpiDate.month,&newExpiDate.day);
	updateCheckingDate(newExpiDate.year, newExpiDate.month, newExpiDate.day);
	//strcpy(expiration, newExpiDate);
	printf("\nEnter new price:\t\t");
	scanf("%f",&newPrice);
	
	//===============================================
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
			
			if (tempID == z){
				clrscr();
				printf("MAIN MENU > UPDATE INVENTORY ITEM\nCurrent Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
				while (token!=NULL){
					//printf("%-10s\t", token);
					switch(tokenCount){
						case 0: {
							//itemOnHold_itemID = token;
							printf("%-10d\t", itemOnHold_itemID);
							break;
						}
						case 1:{
							//itemOnHold_itemDesc[30] = token;
							strcpy(itemOnHold_itemDesc, token);
							printf("%-10s\t", itemOnHold_itemDesc);
							break;
						}
						case 2:{
							//itemOnHold_quantity = token;
							printf("%-10d\t", itemOnHold_quantity);
							break;
						}
						case 3:{
							//itemOnHold_expiDate[30] = token;
							strcpy(itemOnHold_expiDate, token);
							printf("%-10s\t", itemOnHold_expiDate);
							break;
						}
						case 4:{
							//printf("edi shing\t");
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
					token = strtok(NULL, s1);
				}
			}
			fclose(fp1);
			break;
		}
	}
	
	printf("\n\nUpdated Product Details:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n%-10d\t%-10s\t%-10d\t%-10s\t%-10.2f\n", newItemID, newItemDesc, newQuantity, expiration, newPrice);
		
	char ch;
	printf("\nProceed with update?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	getchar();
	scanf("%c",&ch);
	if(!(ch=='y'|| ch=='Y')){
		updateAgain();
		abort();
	}
	else{
			
		int x, i;
		//item1 invUpdate;
		int itemCount;
		fscanf(fp3, "%i", &itemCount);
		printf("\nThis is the itemCount:  %i\n", itemCount);
		item1 *updatedInventory = malloc(sizeof(item1) * itemCount);
		
		for (i = 0; i < itemCount; i++){
			char *desc = malloc(sizeof(char)* (itemDescLen + 1));
			desc[itemDescLen] = '\0';
			unsigned short currentItemID;
			unsigned short currentItemQua;
			char *currentItemExp = malloc(sizeof(char) * (11));  
			currentItemExp[10] = '\0';
			float currentItemPri;
			char expiration[10];
			
			while(fgets(line,sizeof(line),fp1)){
				char *token;
		        //char line[225];
				token = strtok(line, s1);
				while (token!=NULL){
					printf("\t%-10s", token);
					token = strtok(NULL, s1);
				}
			}
		}
	
		//const char s1[5] = "\",\"";
		
		
		for (i = 0; i < itemCount; i++){
			printf("\nPumasok na ng for-i Loop\n");
			
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
		printf("\nHere is the updateCount: %d\n", updateCount);
		for (i = 0; i<itemCount;i++){
			printf("%5d,%s,%d,%s,%.2f\n", updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
			fprintf(fp4, "%i", updateCount);		
			fprintf(fp2, "%i\n%5d,%s,%d,%s,%.2f\n", updateCount, updatedInventory[i].itemID, updatedInventory[i].itemDesc, updatedInventory[i].quantity, updatedInventory[i].expiDate, updatedInventory[i].price);
		}
		fclose(fp1);
		fclose(fp2);
		remove("Database\\Inventory.csv");
		rename("Database\\copyInventory.csv","Database\\Inventory.csv");
		remove("Database\\counter.csv");
		rename("Database\\control.csv","Database\\counter.csv");
		updateSuccessful();
		
	}
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
