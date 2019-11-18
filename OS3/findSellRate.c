#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>

int main(int argc, char** argv)
{
	if(argc != 1)
	{
		printf("argument count does not match\n");
		return -1;
	}

	char* inputProduct = argv[1];

    Transaction* transactions = readFile("market.txt");

    char* item;
    int i=0, j, count=0;
    while(transactions[i].customer != NULL){
        j = 0;
        while(item = transactions[i].items[j] != NULL){

            if(!strcmp(inputProduct, item)){
                count++;
            }   

            j++;
        }
        i++;
    }

    print("\nGiven product sold %d times", count);

}