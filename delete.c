#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
// fopen, fclose, getc, putc, getw, putw, fprintf, cputs, wputs, fputs

typedef struct item
{
	int productID;
	char productDescription[30];
	int quantity;
	char expiration[30];
	float price;
}item;

void deleteItem();
void deleteChoice();
void deleteMenu();

int main()
{
    
    deleteMenu();
    return 0;

}

void addProduct() //DUMMY CODE
{
	item product;
    FILE *fp;
    fp = fopen("myINVENTORY.txt", "a");
    printf("\nEnter Product ID : ");
    scanf(" %d",&product.productID);
    printf("Enter Product Description : ");
    scanf(" %s",product.productDescription);
    printf("Enter Product Quantity : ");
    scanf(" %d",&product.quantity);
    printf("Enter Product Expiration : ");
    scanf(" %s",product.expiration);
    printf("Enter Product Price : ");
    scanf(" %f",&product.price);
    fwrite(&product, sizeof(item), 1, fp);
    fclose(fp);
}

void display() //DUMMY CODE
{
    item product;
    FILE *fp = fopen("Inventory_ST_xx.csv","r");
	const char s1[5] = ",";
    char line[225];
	printf("\nProduct ID\t\tDescription\t\tQuantity\tExp Date\tPrice\n");
	while(fgets(line,sizeof(line),fp)){
		char *token;
		token = strtok(line, s1);
		while (token!=NULL){
			printf("\t%-10s", token);
			token = strtok(NULL, s1);
		}
		printf("\n");
	}
    fclose(fp);           
}

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
            
            fp = fopen("Inventory_ST_xx.csv","r");
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
                        products[i].productID = realResult;
                        if(products[i].productID == itemID)  //KUNG EXIST ANG ID NILAGAY
                        {
                            found = 1;
                            printf("\n\nDO YOU WANT TO DELETE THIS ITEM???[Y][N] :");
                            printf("\n\n%s",complete);
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
                     fp = fopen("Inventory_ST_xx.csv","w");
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
    char choice[20];
    while(strcmp (choice, "D") != 0 || strcmp (choice, "S")  != 0 || strcmp (choice, "M") != 0 ||
    strcmp (choice, "d") != 0 || strcmp (choice, "s")  != 0 || strcmp (choice, "M") != 0){
    
    printf("\nDELETE MENU");
    printf("\n [D] DELETE INVENTORY ITEM");
    printf("\n [S] SEARCH INVENTORY ITEM (add product dummy)");
    printf("\n [M] MAIN MENU (view products dummy)");
    printf("\n\n PLEASE INPUT CHOICE: ");
    scanf("%s", &choice);
    if (strcmp (choice, "D") == 0 || strcmp (choice, "d") == 0){
        deleteItem();
    }
    else if (strcmp (choice, "S") == 0 || strcmp (choice, "s") == 0){
        addProduct();
        //SEARCH FUNCTION THEN RETURN TO DELETE FUNCTION
        //dummy code young add product
    }
    else if (strcmp (choice, "M") == 0 || strcmp (choice, "m") == 0){
        display();
        //MAIN MENU FUNCTION
        //dummy code yung display
    }

    }
}

void deleteMenu()
{
    deleteChoice();
}

