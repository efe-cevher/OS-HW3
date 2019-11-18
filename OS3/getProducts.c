#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"

int main(){

    Product* products = readProducts("price.txt");

    int i=0;
    while (products[i].name != NULL)
    {
        printf("\n Product: %s %d₺ ", products[i].name, products[i].price);
        i++;
    }

    
    
}