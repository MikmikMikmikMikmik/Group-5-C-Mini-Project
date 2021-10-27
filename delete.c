#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
// fopen, fclose, getc, putc, getw, putw, fprintf, cputs, wputs, fputs

typedef struct date
{
    int year;
    int month;
    int day;
}date;

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

void addProduct()
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

void display() 
{
    item product;
    FILE *fp;
    fp = fopen("myINVENTORY.txt", "r");
    while(fread(&product, sizeof(item),1,fp))
    {
        
        printf("\n%-10d%-25s%-30d%-35s%-40f",product.productID, product.productDescription, product.quantity, product.expiration
        , product.price);
    }

    fclose(fp);
}

void deleteItem()
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
            if(isalpha(deleteItemID[i]))
            {
                valid = 0;
            }
            i++;
        }
        if (valid == 0)
        {
            printf("Invalid ID");
        }
        else if (valid == 1)
        {
            
            int itemID = atoi(deleteItemID);
            
            item s1;
            FILE *fp, *fpl;
            int j, rno, found = 0;
            char details[100];
            
            fp = fopen("myINVENTORY.txt","r");
            fpl = fopen("temp.txt","w");
            while (fread(&s1,sizeof(item),1,fp))
            {
                
                if(s1.productID == itemID)
                {
                    found=1;
                  printf("\n DO YOU WANT TO DELETE\n \nProduct ID     Description          Quantity     Exp Date         Price");
                  printf("\n%-15d%-20s%-15d%-20s%-15f ? [Y/N] : ",s1.productID, s1.productDescription, s1.quantity, s1.expiration
                     , s1.price);
                   /* strcat(details, "daf");
                    strcat(details, "   ");
                    strcat(details, s1.productDescription);
                    strcat(details, "   ");
                    strcat(details, s1.quantity);
                    strcat(details, "   ");
                    strcat(details, s1.expiration);
                    strcat(details, "   ");
                    char price[20];
                    sprintf(price, "%g", s1.price);
                    strcat(details, price);
                    strcat(details, "   ");*/
                }
                else
                {
                    fwrite(&s1,sizeof(item),1,fpl);
                }
            }
            fclose(fp);
            fclose(fpl);
            if (found)
            {
                printf(" ");
                char choke[10];
                scanf(" %s",&choke);
                if(strcmp (choke, "Y") == 0 || strcmp (choke, "y") == 0)
                {
                     fpl = fopen("temp.txt","r");
                     fp = fopen("myINVENTORY.txt","w");
                     while (fread(&s1,sizeof(item),1,fpl))
                     {
                        fwrite(&s1,sizeof(item),1,fp);
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
            else
            {
                printf("\nItem Does Not Exist\n\n");
            }
           
             }
    }
}

void deleteChoice()
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

