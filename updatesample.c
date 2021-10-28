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
void updateCheckingDate(int day,int month,int year);
void updateNoofRec();

int updateCheckItemID(int itemID, int count);
int updateByID(int ID);
int updateSearchByID(item ptr[],int ino,int count);

void updateInventory(){
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
			updateSearchID(); break;
		}
		case 2: {
			updateByDesc(); break;
		}
		default:{
			clrscr();
			printf("\nInvalid choice!!");
			updateInventory();
		}
	}
}

void updateAgain(){
	char ch;
	printf("\nDo you want to try updating an item again?\n[Y] Yes\n[N] No\n\nPlease input choice: ");
	getchar();
	scanf("%c",&ch);
	if(ch=='y'|| ch=='Y'){
		updateInventory();
	}
	else{
		mainMenu();
	}
}

void updateInvalidInput(){
	clrscr();
	printf("MAIN MENU > ADD INVENTORY ITEM\n");
	printf("\nInvalid Input");
	updateAgain();
}

void updateItem(){
	
	//char line[225];
	//FILE * fpointer = fopen("Inventory.txt", "r");

	//fgets(line, 255, fpointer);

	//fclose(fpointer);
	
	FILE *fpointer = fopen("Inventory.csv", "w+");
	if(!fpointer){
		printf("\nInventory file does not exist!");
	}
	
	//fprintf(fpointer, "11101,Nat. Spring (500mL),200,-,10.50\n11201,Nat. Spring (1L),100,-,16.00\n11202,Nat. Spring (1L),300,-,16.50\n12101,Datu Puti Vinegar (1L),100,2022-03-22,38.25\n51101,Nivea Silver Protect (50mL),50,2023-08-31,45.00\n");
	fprintf(fpointer, "\"11101\",\"Nat. Spring (500mL)\",\"200\",\"-\",\"10.50\"\n\"11201\",\"Nat. Spring (1L)\",\"100\",\"-\",\"16.00\"\n\"11202\",\"Nat. Spring (1L)\",\"300\",\"-\",\"16.50\"\n\"12101\",\"Datu Puti Vinegar (1L)\",\"100\",\"2022-03-22\",\"38.25\"\n\"51101\",\"Nivea Silver Protect (50mL)\",\"50\",\"2023-08-31\",\"45.00\"\n");
	
	fclose(fpointer);
	
	/*int i;
	int flag=0;
    for(i=0;i<count;i++)
    {
    	if(product[i].productNumero==pno)
    	{
    		flag=1;

    		product[i].price=price;
    		printf("\n\nPrice updated\n");
    		break;
    	}
    }*/
}


void updateNoofRec(){
	item2 item;
	FILE *fp;
	fp = fopen("Inventory.csv","r");
	fseek(fp,0,SEEK_END);
	int total =  ftell(fp)/sizeof(item2);
	printf("\n\nThere are %d total items in the inventory", total);
	fclose(fp);
}

int updateCheckItemID(int itemID, int count)
{
	item product[100];
	FILE *fp=fopen("Inventory.csv","rb");
	fread(&product, sizeof(product), 1, fp);

	int i; for(i=0;i<count;i++)
	{
		if(itemID==product[i].itemID)
		{
			return itemID;
		}

	}

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
		updateInvalidInput();
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


void searchByID() {
    system("cls");
    item1 p1;
    FILE *fp;
    int j, pId, found = 0;
    fp = fopen("Inventory.csv", "r");


    printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\n");
        printf("\nProduct ID\tDescription\tQuantity\tExp Date\tPrice");
        printf("\n%d\t%s\t%d\t%s\t%f", p1.itemID, p1.itemDesc, p1.quantity, p1.expiDate, p1.price);
    printf("Enter Product ID to Search: ");
    scanf("%5d", &pId);
    
    while(fread(&p1,sizeof(item1),1,fp))
    {
        if(p1.itemID == pId){
            found = 1;
            printf("\nProduct ID\tDescription\tQuantity\tExp Date\tPrice");
            printf("\n%d\t%s\t%d\t%s\t%f", p1.itemID, p1.itemDesc, p1.quantity, p1.expiDate, p1.price);
        }
    }
    if(!found) {
        printf("\nRecord Not Found\n");
        system("pause");
    }

    fclose(fp);
}

/*
void display(){
	printf("\n");
	item1 item;
	FILE *fp = fopen("Inventory.csv","r");
	const char s1[5] = "\",\"";
	const char s2[2] = "-";
    char line[225];
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
    return;	
}
*/

int updateSearchID(){
	//======================================
	int ID, found, x;
	int counter = 0;
	printf("\n\nPlease input Item ID:\t\t");
	scanf("%d", &ID);
	//system("pause");
	//printf("%d", ID);
	//if ((ID<=0) || (ID>=100000)){
	//	updateInvalidInput();
	//	updateAgain();
	//}
		item1 item;
		FILE *fp = fopen("Inventory.csv","r");
		const char s1[5] = "\",\"";
		const char s2[2] = "-";
	    char line[100];
		while(fgets(line,sizeof(line),fp)){
			counter++;
			char *token;
			token = strtok(line, s1);
			//int tempId = *token;
			x = atoi(token);
			//printf("temp is:\t%d\n",tempId);
			//printf("token is :\t%d\n",&token);
			//printf("X is :\t%d\n",&x);
			if (ID == x){
				clrscr();
				printf("MAIN MENU > UPDATE INVENTORY ITEM\nYou will be updating:\nProduct ID\tDescription\t\tQuantity\tExp Date\tPrice\n");
				while (token!=NULL){
	            	found = 1;
					printf("%-10s\t", token);
					token = strtok(NULL, s1);
				}
				ID = 999999;
				updateByID(x);
			}
			//else if(ID = 999999){
			//		printf("\nNo ID found.");
			//		break;}
			printf("\nControl got here.");
			break;
		}
		if (found == 0){
			printf("\nNot found.");
	    	return 0;
		}
	    fclose(fp);
	    return 0;
	
}

int updateSearchByID(item ptr[],int ino,int count){
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

int updateByID(int ID){
	
	struct item1 product;
	int location;
	//int count = updateNoofRec();
	int itemID = ID;
		
			//updateItem();
	
		FILE *fp=fopen("Inventory.csv","w+");
		fread(&product, sizeof(product),1,fp);
	
		//FILE *counter=fopen("counter.dat","r");
		//int count;
		//fscanf(counter,"%d",&count);
		//fclose(counter);
	
		int newItemID;
		char newItemDesc[20];
		int newQuantity;
		date newExpiDate;
		float newPrice;
		
		printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
		printf("\nEnter new Item ID:\t\t");
		scanf("%d",itemID);
		printf("\nEnter new Description:\t\t");
		scanf("%s",itemDesc);
		printf("\nEnter new Quantity:\t\t");
		scanf("%d",quantity);
		printf("\nEnter new Expiration Date: (yyy/mm/dd)\t\t");
		scanf("%d/%d/%d",&product[count].expiration.year,&product[count].expiration.month,&product[count].expiration.day);
		updateCheckingDate(product[count].expiration.year,product[count].expiration.month,product[count].expiration.day);
		printf("\nEnter new price:\t\t");
		scanf("%f",price);
	
		//int i;
		int flag=0;
	    for(i=0;i<count;i++)
	    {
	
	    	if(product[i].itemID==itemID)
	    	{
	    		flag=1;
				product[i].itemID 		= itemID;
				//product[i].itemDesc 	= itemDesc;
				//strcpy(product[i].itemDesc, itemDesc);
				product[i].quantity 	= quantity;
				product[i].expiration 	= expiration;
				product[i].price 		= price;
	    		break;
	    	}
	    	
	    }
	    
	    if (flag==1)
	    {
			FILE *fp2=fopen("Inventory1.csv","wb");
			fwrite(&product, sizeof(item), count, fp2);
			remove("Inventory.csv");
			rename("Inventory1.csv","Inventory.csv");
			fclose(fp2);
	
			char ch;
			updateAgain();
		}
	
	    else
	    {
			updateInvalidInput();
			updateAgain();
		}
	}
}

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
}


void mainMenu(){
	int choice = 999999;
	do{
		printf("\n");
		//clrscr();
		printf("MAIN MENU\n[1] Add Inventory Item\n[2] Update Inventory Item\n[3] View Inventory Item\n[4] Delete Inventory Item\n[0] Exit Program\n\nPlease input Choice: ");
		scanf("%d", &choice);
		    switch(choice){
				case 1:{ 
					updateInventory(); break; }
				case 2:{ 
					printf("Your input is %d", choice);  updateNoofRec(); updateSearchID(); break; }
				case 3:{					
					printf("Your input is %d", choice); updateItem(); break; }
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
					updateInventory(); break;
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
	while (choice==99999);
	return;
}

int main(){
    //
    int sysInit = 0;
    //while(sysInit == 0){
	FILE *fpointer = fopen("Inventory.csv", "r");
	if(!fpointer){
		printf("\nInventory file does not exist!");
		return 0;
	}
	else{
		mainMenu();
	}
	//}
	return 0;    
}
