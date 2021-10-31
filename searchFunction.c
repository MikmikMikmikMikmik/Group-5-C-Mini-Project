#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clrscr()
{
    system("@cls||clear");
}

void searchMenu();
void searchItemID();
void searchItemName();

void searchItemID() {
    clrscr();
    FILE *fp = fopen("Inventory_ST_NoBOM.csv","r");

    int prodID, found = 0;
	char line[225];
    const char delims[5] = "\",\"";

    char stringID[6];
    int ID;
    
    printf("SEARCH FOR AN INVENTORY ITEM > by Item ID\n\n");
    printf("Enter Product ID to Search: ");
    fflush(stdin);
    scanf("%[^\n]s", stringID);

    printf("%d", strlen(stringID));
    ID = atoi(stringID);
    printf("%d", ID);
    
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
			printf("\nItem ID does not exists.\n\n");
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
    FILE* stream = fopen("Inventory_ST_NoBOM.csv", "r");

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
        
    }
    else {
        printf("\n\nError! Invalid Input\n\n");
        system("pause");
        searchMenu();
    }
}

int main()
{
    searchMenu();
    return 0;
}
