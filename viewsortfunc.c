#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>

typedef struct item
{
	int productID;
	char productDescription[30];
	int quantity;
	char expiration[30];
	float price;
}item;

int main()
{
	char choice;
    printf("VIEW INVENTORY\n");
    printf("[A] View All\n");
    printf("[B] Search for an Inventory Item\n");
    printf("[C] Back to Menu\n");
    printf("\nPlease input choice: ");
    scanf("%c", &choice);
    if(choice == 'A')
    {
    sortOption();
	}
	return 0;
}

void sortascend()
{
            FILE *fp;
            
            fp = fopen("inventory.csv","r");

            char buff[500];
            int row_count = 0;
            int field_count = 0;
            item products[999];
            int i = 0;
            char complete[500][100];
            
            while(fgets(buff, sizeof(buff),fp))
            {
                
                int field_count = 0;
                row_count++;
                
                strcpy(complete[i], buff);
                
                
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0'; 
                        int realResult = atoi(result); 
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1)
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) 
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3)
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) 
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        float thePrice = strtod(result,NULL);
                        
                       products[i].price = thePrice; 
                        
                    }
                    field = strtok(NULL, ",");
                    field_count++;
                }
                i++;
            }
            fclose(fp);

            
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            
                            if(products[y].productID < products[x].productID && products[x].productID != 0)
                                {
                                    idTmp = products[x].productID;
                                    products[x].productID = products[y].productID;
                                    products[y].productID = idTmp;

                                    strcpy(descTmp ,products[x].productDescription);
                                    strcpy(products[x].productDescription, products[y].productDescription);
                                    strcpy(products[y].productDescription, descTmp);

                                    quantTmp = products[x].quantity;
                                    products[x].quantity = products[y].quantity;
                                    products[y].quantity = quantTmp;

                                    strcpy(expTmp ,products[x].expiration);
                                    strcpy(products[x].expiration, products[y].expiration);
                                    strcpy(products[y].expiration, expTmp);

                                    priceTmp = products[x].price;
                                    products[x].price = products[y].price;
                                    products[y].price = priceTmp;
                                    
                                }
                        }
                        
          }
            
            
            
            for(int x=0;x<sizeof(buff);x++)
            {
                printf("\n \"%d\"   %s   \"%d\"   %s   \"%.2f\"",products[x].productID,products[x].productDescription,
                products[x].quantity,products[x].expiration,products[x].price);
            }  
            
}

void sortdescend()
{
            FILE *fp;
            
            fp = fopen("inventory.csv","r");

            char buff[500];
            int row_count = 0;
            int field_count = 0;
            item products[999];
            int i = 0;
            char complete[500][100];
            
            while(fgets(buff, sizeof(buff),fp))
            {
                
                int field_count = 0;
                row_count++;
                
                strcpy(complete[i], buff);
                
                
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0)
                    {
                       
                        char *result = field+1; 
                        result[strlen(result)-1] = '\0'; 
                        int realResult = atoi(result); 
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) 
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) 
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3)
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) 
                    {
                        
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        float thePrice = strtod(result,NULL);
                        
                       products[i].price = thePrice; 
                        
                    }
                    field = strtok(NULL, ",");
                    field_count++;
                }
                i++;
            }
            fclose(fp);

           
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
           
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                           
                            if(products[y].productID > products[x].productID && products[x].productID != 0)
                                {
                                    idTmp = products[x].productID;
                                    products[x].productID = products[y].productID;
                                    products[y].productID = idTmp;

                                    strcpy(descTmp ,products[x].productDescription);
                                    strcpy(products[x].productDescription, products[y].productDescription);
                                    strcpy(products[y].productDescription, descTmp);

                                    quantTmp = products[x].quantity;
                                    products[x].quantity = products[y].quantity;
                                    products[y].quantity = quantTmp;

                                    strcpy(expTmp ,products[x].expiration);
                                    strcpy(products[x].expiration, products[y].expiration);
                                    strcpy(products[y].expiration, expTmp);

                                    priceTmp = products[x].price;
                                    products[x].price = products[y].price;
                                    products[y].price = priceTmp;
                                    
                                }
                        }
                        
          }
            
            
            //PRINT
            for(int x=0;x<sizeof(buff);x++)
            {
                printf("\n \"%d\"   %s   \"%d\"   %s   \"%.2f\"",products[x].productID,products[x].productDescription,
                products[x].quantity,products[x].expiration,products[x].price);
            }  
            
}


void sortOption()
{
	char choice;
	printf("\nView All Menu\n");
	printf("[A] Sort ID in Ascending Order\n");
	printf("[B] Sort ID in Descending Order\n");
	printf("[C] Return to Main Menu\n");
	printf("Please input a valid choice: ");
	scanf(" %c", &choice);
	if(choice == 'A')
	{
		sortascend();
	}
	else if (choice == 'B')
	{
		sortdescend();
	}
}

