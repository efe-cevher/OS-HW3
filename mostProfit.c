#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>

Product* products;

//Check product price of given string by traversing Product array
int checkProductPrice(char* product){
    int i=0;
    while (products[i].name != NULL){
        if(!strcmp(products[i].name, product)){
            return products[i].price;
        }
        i++;
    }
}

int main(){

    Transaction* transactions = readFile("market.txt"); //Get neccesary data from file, via method in FileIO.c
    products = readProducts("price.txt"); //create products array with by reading "price.txt" via method in fileIO.c 

    int dayTotals[1024] = {0}; //initalize all locations 0
    int days[128];
    int totaldays = 0;

    char* item;
    int i=0, j, count=0;
    while(transactions[i].customer > 0){ //While data is valid continue traversing the array
        j = 0;
        int new = 1;
        for(int k=0; k<totaldays; k++){
            if(days[k] == transactions[i].day){
                new = 0;
                break;
            }
        }
        if(new){ //if its first occurence assign a location for day
            days[totaldays] = transactions[i].customer;
            totaldays++;
        }
        
        while(transactions[i].items[j] != NULL){
            item = transactions[i].items[j];
            dayTotals[transactions[i].day] += checkProductPrice(item); //add assigned location prices
            j++;
        }
        i++;
    }
    int maxTotal = 0;
    int maxDay = 0;
    //find the max
    for(int i=0; i<totaldays; i++){
        if(dayTotals[days[i]] > maxTotal){
            maxTotal = dayTotals[days[i]];
            maxDay = days[i];
        }
    }

    printf("\nDay with most profit: %d, Profit of the day: %d\n", maxDay, maxTotal); //console output

}