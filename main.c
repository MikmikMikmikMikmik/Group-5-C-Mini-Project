#include <stdio.h>
#include <stdlib.h>

int main()
{
    //
    int sysInit = 0;
    //while(sysInit == 0){
		updateInventory();
	//}

	    
	
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
	scanf("Please input Choice: %c", &userCommand);
	    
	    switch(userCommand){
	    	case 'A':
			case 'a':{
				printf("Your input is %c", userCommand);
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
				sysInit = 1;
	    		break;}
	    	case 'D':
			case 'd':{
				printf("Your input is %c", userCommand);
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


