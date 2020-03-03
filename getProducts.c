#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"

int main(){

    Product* products = readProducts("price.txt"); // used method in fileIO.c

    int i=0;
    while (products[i].name != NULL)
    {
        printf("\n > %s %d₺ ", products[i].name, products[i].price); // printed items
        i++;
    }

    printf("\n\nThere are %d different products in price.txt\n", i); //printed the counter
    
}