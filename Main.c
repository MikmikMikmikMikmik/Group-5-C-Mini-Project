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


typedef struct item2{
	unsigned int itemID;
	char itemDesc[20];
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
void updateByID();
void updateByDesc();
void updateAgain();
void updateInvalidInput();
void updateItem();
void updateInventory();
void updateCheckingDate(int day,int month,int year);
void updateNoofRec();

int updateCheckItemID(int itemID, int count);
int updateSearchID(item ptr[],int ino,int count);

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
			updateByID(); break;
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
	
	fprintf(fpointer, "11101,Nat. Spring (500mL),200,-,10.50\n11201,Nat. Spring (1L),100,-,16.00\n11202,Nat. Spring (1L),300,-,16.50\n12101,Datu Puti Vinegar (1L),100,2022-03-22,38.25\n51101,Nivea Silver Protect (50mL),50,2023-08-31,45.00\n");
	//fprintf(fpointer, "\"11101\",\"Nat. Spring (500mL)\",\"200\",\"-\",\"10.50\"\n\"11201\",\"Nat. Spring (1L)\",\"100\",\"-\",\"16.00\"\n\"11202\",\"Nat. Spring (1L)\",\"300\",\"-\",\"16.50\"\n\"12101\",\"Datu Puti Vinegar (1L)\",\"100\",\"2022-03-22\",\"38.25\"\n\"51101\",\"Nivea Silver Protect (50mL)\",\"50\",\"2023-08-31\",\"45.00\"\n");
	
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

void display(){
	item2 item;
	FILE *fp;
	const char s1[3] = ", ";
	const char s2[2] = "-";
    char *token;
	fp = fopen("Inventory.csv","r");
	while(fread(&item,sizeof(item),1,fp)){
        char line[225];
		token = strtok(line, s1);
		printf("\n%d%20s%7d",item.itemID,item.itemDesc,item.quantity);	
		token = strtok(line, s2);
		if (item.expiDate==NULL || item.expiDate<0){
			printf("-");
		}
		else{
			printf("%7d / %2d / %2d",item.expiDate[0].year,item.expiDate[0].month,item.expiDate[0].day);
		}
		printf("%7.2f",item.price);
	}
}


int updateSearchID(item ptr[],int ino,int count)
{
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

void updateByID(){
	
	struct item product[100];
	int location;

	FILE *fp=fopen("Inventory.csv","rb");
	FILE *counter=fopen("counter.dat","r");

	int count;
	fscanf(counter,"%d",&count);

	fread(&product, sizeof(product), 1, fp);
	
	printf("\n\nPlease Enter Item ID: ");
	int itemID;
	scanf("%d", &itemID);
	
	location=updateSearchID(product,itemID,count);
	int i;
	if(location!=-1)
	{
		//int updateSearch = product.itemID;
		//product.itemID = updateCheckItemID(updateSearch,count);
		
		/*
		for(i=location;i<count-1;i++)
		{
			product[i]=product[i+1];
		}
		count--;
		printf("Record has been succesfully deleted\n");
		*/

		fclose(counter);

		FILE *counterw=fopen("counter.dat","w");
		fprintf(counterw,"%d",count);
		fclose(counterw);
		FILE *fpointer=fopen("Inventory.csv","rb");
		FILE *counter=fopen("counter.dat","r");
	
		int count=0;
	
	
		fscanf(counter,"%d",&count);
		fread(&product, sizeof(product), 1, fpointer);
		fclose(fpointer);
	
		/*
		while (fread(&product,sizeof (item),1,fp))
		{
			count++;
		}
		*/
		clrscr();
		printf("MAIN MENU > UPDATE INVENTORY ITEM\nYou will be updating:\nProduct ID\tDescription\t\tQuantity\tExp Date\t\tPrice\n");
	
	
		int i; 
		for(i=0;i<count;i++)
		{
			printf("%5d\t",product[i].itemID);
			printf("%20s\t",product[i].itemDesc);
			printf("%5d\t",product[i].quantity);
			printf("%4d/%2d/%2d\t",product[i].expiration.year,product[i].expiration.month,product[i].expiration.day);
			printf("%.2f\n",product[i].price);
		}
		
		//==============================
		
		
			//updateItem();
	
		FILE *fp=fopen("Inventory.csv","w+");
		fread(&product, sizeof(product),1,fp);
	
		//FILE *counter=fopen("counter.dat","r");
		//int count;
		fscanf(counter,"%d",&count);
		fclose(counter);
	
		int itemID;
		char itemDesc[50];
		int quantity;
		date expiration;
		float price;
		
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
	else if(location==-1){
		updateInvalidInput();
		updateAgain();
	}
	
	if (itemID<1 && itemID>999999999){
		updateInvalidInput();
		updateAgain();
	}
	/*
	else{
		product.itemID=updateCheckItemID(product.itemID,count);
		
		//=======================================
		
		FILE *fpointer=fopen("Inventory.csv","rb");
		FILE *counter=fopen("counter.dat","r");
	
		int count=0;
	
	
		fscanf(counter,"%d",&count);
		fread(&product, sizeof(product), 1, fpointer);
		fclose(fpointer);
	
		
		//while (fread(&product,sizeof (item),1,fp))
		//{
		//	count++;
		//}
		
		clrscr();
		printf("MAIN MENU > UPDATE INVENTORY ITEM\nYou will be updating:\nProduct ID\tDescription\t\tQuantity\tExp Date\t\tPrice\n");
	
	
		int i; 
		for(i=0;i<count;i++)
		{
			printf("%10d\t",product[i].itemID);
			printf("%12s\t",product[i].itemDesc);
			printf("%5d\t",product[i].quantity);
			printf("%4d/%2d/%2d\t",product[i].expiration.year,product[i].expiration.month,product[i].expiration.day);
			printf("%.2f\n",product[i].price);
		}
		
		//==============================
		
		
			//updateItem();
	
		FILE *fp=fopen("Inventory.csv","w+");
		fread(&product, sizeof(product),1,fp);
	
		//FILE *counter=fopen("counter.dat","r");
		//int count;
		fscanf(counter,"%d",&count);
		fclose(counter);
	
		int itemID;
		char itemDesc[50];
		int quantity;
		date expiration;
		float price;
		
		printf("\nPlease Enter New Item Details (Enter '-' if not applicable):");
		printf("\nEnter new Item ID:\t\t");
		scanf("%d",itemID);
		printf("\nEnter new Description:\t\t");
		scanf("%s",itemDesc);
		printf("\nEnter new Quantity:\t\t");
		scanf("%d",quantity);
		printf("\nEnter new Expiration Date: (yyy/mm/dd)\t\t");
		scanf("%d/%d/%d",&product[count].expiration.year,&product[count].expiration.month,&product[count].expiration.day);
		updateCheckingDate(&product[count].expiration.year,&product[count].expiration.month,&product[count].expiration.day);
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
				strcpy(product[i].itemDesc, itemDesc);
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
	*/
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
	int choice;
	do{
		clrscr();
		printf("MAIN MENU\n[1] Add Inventory Item\n[2] Update Inventory Item\n[3] View Inventory Item\n[4] Delete Inventory Item\n[0] Exit Program\n\nPlease input Choice: ");
		scanf("%d", &choice);
		    switch(choice){
				case 1:{
					printf("Your input is %d", choice); updateNoofRec(); display(); break; }
				case 2:{					                                                          
					printf("Your input is %d", choice); updateInventory(); break; }
				case 3:{					
					printf("Your input is %d", choice); updateItem(); break; }
				case 4:{					
					printf("Your input is %d", choice); break; }
				case 0:{
					printf("System Terminated."); choice = 0; break; }
		    	default:{					
					printf("This is default."); choice = 0; break; }
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
	while (choice==0);
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
