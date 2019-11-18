#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"

Product* products;

int checkProductPrice(char* product){
    int i=0;
    while (products[i].name != NULL){
        if(!strcmp(products[i].name, product)){
            return products[i].price;
        }
        i++;
    }
}

int main(int argc, char** argv)
{
	if(argc != 1)
	{
		printf("argument count does not match\n");
		return -1;
	}

    products = readProducts("price.txt");

    char* inputCustomer = argv[1];

    Transaction* transactions = readFile("market.txt");

    char* item;
    int i=0, j, transactionCount=1, customer, itemCount = 0, totalPaid = 0;
    while(customer = transactions[i].customer != NULL){
        j = 0;

        if(!strcmp(inputCustomer, customer)){
            printf("\nTransaction %d: Day %d, ", transactionCount, transactions[i].day);
            transactionCount++;

            while(item = transactions[i].items[j] != NULL){
                
                printf("%s, ", item);

                totalPaid += checkProductPrice(item);

                j++;
            }
        }
        i++;
    }

    printf("\n\nTotal Paid: %d", totalPaid);

}