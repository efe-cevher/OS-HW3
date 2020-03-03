#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("argument count does not match\n"); // check if args given right
		return -1;
	}

	char* inputProduct = argv[1]; //input arg

    Transaction* transactions = readFile("market.txt"); //Get neccesary data from file, via method in FileIO.c

    char* item;
    int i=0, j, count=0;
    while(transactions[i].customer > 0){ //While data is valid continue traversing the array
        j = 0;
        while(transactions[i].items[j] != NULL){ //While data is valid continue traversing the array

            item = transactions[i].items[j];
            if(!strcmp(inputProduct, item)){ // check if given if item equal to input item
                count++;
            }
            j++;
        }
        i++;
    }

    printf("\n%s sold %d times\n",inputProduct, count); // console output

}