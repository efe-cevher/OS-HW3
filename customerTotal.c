#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>

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
	if(argc != 2)
	{
		printf("argument count does not match\n"); // check if args given right
		return -1;
	}

    products = readProducts("price.txt"); //get price data by reading "price.txt" via method in fileIO.c

    int inputCustomer =  atoi(argv[1]); 

    Transaction* transactions = readFile("market.txt"); //Get neccesary data from file, via method in FileIO.c

    char* item;
    int i=0, j, transactionCount=1, customer, itemCount = 0, totalPaid = 0;

    while(transactions[i].customer > 0){ //While data is valid continue traversing the array
        customer = transactions[i].customer;
        j = 0;

        if(inputCustomer == customer){
            printf("\nTransaction %d: Day %d, ", transactionCount, transactions[i].day); // output transactions of cust one by one
            transactionCount++;

            while(transactions[i].items[j] != NULL){

                item = transactions[i].items[j];
                
                printf("%s, ", item);

                totalPaid += checkProductPrice(item); // add to total

                j++;
            }
        }
        i++;
    }

    printf("\n\nTotal Paid: %d₺\n", totalPaid); // total paid console output

}