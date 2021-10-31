#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>

void sort();

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
    viewInventory();
    return 0;
}

void clrscr()
{
    system("@cls||clear");
}


void IDascend()
{
			
			clrscr();
            FILE *fp;
            char choice;
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
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
            
            
            //PRINT
            for(int x=0;x<sizeof(buff);x++)
            {
                printf("\n \"%d\"   %s   \"%d\"   %s   \"%.2f\"",products[x].productID,products[x].productDescription,
                products[x].quantity,products[x].expiration,products[x].price);
            }  
    
            
            
}

void IDdescend()
{
			clrscr();
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
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

void quantascend()
{
			clrscr();
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
                            if(products[y].quantity < products[x].quantity && products[x].quantity != 0)
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

void quantdescend()
{
			clrscr();
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
                            if(products[y].quantity > products[x].quantity && products[x].quantity != 0)
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

void priceascend()
{
			clrscr();
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
                            if(products[y].price < products[x].price && products[x].price != 0)
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

void pricedescend()
{
			clrscr();
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
                            if(products[y].price > products[x].price && products[x].price != 0)
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

void expdateascend()
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
                
                //strcpy(tempComplete, buff);
                char *field = strtok(buff,",");

                while (field)
                {
                    if (field_count == 0) // ID
                    {
                        //printf("\n%s",field);
                        char *result = field+1; // delete ang last element yung "
                        result[strlen(result)-1] = '\0'; // yung unang " naman
                        int realResult = atoi(result); // convert to int
                        products[i].productID = realResult;
                       
                    }
                    if (field_count == 1) // DESCRIPTION
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        strcpy(products[i].productDescription, result);
                    }
                    if (field_count == 2) // QUANTITY
                    {
                        char *result = field+1;
                        result[strlen(result)-1] = '\0';
                        int quant = atoi(result);
                       products[i].quantity = quant; 
                    }
                    if (field_count == 3) //EXPIRATION
                    {
                        strcpy(products[i].expiration, field);
                    }
                    if (field_count == 4) // PRICE
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

            //mga temporary
            int idTmp;
            char descTmp[50];
            int quantTmp;
            char expTmp[50];
            float priceTmp;
            
            //SORT
            for(int x=0;x<sizeof(buff);x++)
            {
                    for(int y=x+1;y<sizeof(buff);y++)
                        {
                            //PWEDE PALITAN ANG < ng > para Descending
                            //PWEDE ITO GAWIN SA ID AT QUANTITY KASE NUMBERS ANG PINAG COCOMPARE
                            //DI KO LANG ALAM SA ALPHABET
                            if(products[y].expiration < products[x].expiration && products[x].expiration != 0)
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

void viewOption()
{
	clrscr();
	char choice;
	printf("[A] Sort by ID\n");
	printf("[B] Sort by Description\n");
	printf("[C] Sort by Quantity\n");
	printf("[D] Sort by Price\n");
	printf("[E] Sort by Expiration Date\n");
	printf("[X] Return to Previous Menu\n");
	scanf(" %c", &choice);
	if(choice == 'A')
	{
		idsortchoice();
	}
	else if(choice == 'C')
	{
		quantsortchoice();
	}
	else if(choice == 'D')
	{
		pricesortchoice();
	}
}

void idsortchoice()
{
	clrscr();
	char choice;
	printf("[A] Sort Product ID in Ascending Order\n");
	printf("[B] Sort Product ID in Decending Order\n");
	printf("[X] Return to Previous Menu\n");
	printf("\nPlease input choice: ");
	scanf(" %c", &choice);
	if(choice == 'A')
	{
		IDascend();
	}
	else if(choice == 'B')
	{
		IDdescend();
	}
	else if (choice == 'X')
	{
		viewOption();
	}
	else
	{
		printf("Please input a valid choice!\n\n");
		idsortchoice();
	}
}

void quantsortchoice()
{
	clrscr();
	char choice;
	printf("[A] Sort Quantity in Ascending Order\n");
	printf("[B] Sort Quantity in Decending Order\n");
	printf("[X] Return to Previous Menu\n");
	printf("\nPlease input choice: ");
	scanf(" %c", &choice);
	if(choice == 'A')
	{
		quantascend();
	}
	else if (choice == 'B')
	{
		quantdescend();
	}
	else if (choice == 'X')
	{
		viewOption();
	}
	else
	{
		printf("Please input a valid choice!\n\n");
		quantsortchoice();
	}
}

void pricesortchoice()
{
	clrscr();
	char choice;
	printf("[A] Sort Price in Ascending Order\n");
	printf("[B] Sort Price in Decending Order\n");
	printf("[X] Return to Previous Menu\n");
	printf("\nPlease input choice: ");
	scanf(" %c", &choice);
	if(choice == 'A')
	{
		priceascend();
	}
	else if (choice == 'B')
	{
		pricedescend();
	}
	else if (choice == 'X')
	{
		viewOption();
	}
	else
	{
		printf("Please input a valid choice!\n\n");
		pricesortchoice();
	}
}

void viewInventory()
{
	clrscr();
	char choice;
	printf("VIEW INVENTORY\n");
	printf("[A] View All\n");
	printf("[B] Search for an Inventory Item\n");
	printf("[C] Back to Menu\n");	
	printf("\nPlease input choice: ");
	scanf("%c", &choice);
	if(choice == 'A');
	{
		viewOption();
	}
	
	
	return 0;
}

