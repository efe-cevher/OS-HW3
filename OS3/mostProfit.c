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

int main(){

    Transaction* transactions = readFile("market.txt");
    products = readProducts("price.txt");

    int dayTotals[1024];
    int days[128];
    int totaldays = 0;

    char* item;
    int i=0, j, count=0;
    while(transactions[i].customer != NULL){
        j = 0;
        int new = 1;
        for(int k=0; k<totaldays; k++){
            if(days[k] == transactions[i].day){
                new = 0;
                break;
            }
        }
        if(new){
            days[totaldays] = transactions[i].customer;
            totaldays++;
        }

        if(dayTotals[transactions[i].day] == NULL){
            dayTotals[transactions[i].customer] = 0;
        }
        
        while(item = transactions[i].items[j] != NULL){
            dayTotals[transactions[i].day] += checkProductPrice(transactions[i].items[j]);
            j++;
        }
        i++;
    }
    int maxTotal = 0;
    int maxDay = 0;
    for(int i=0; i<totaldays; i++){
        if(dayTotals[days[i]] > maxTotal){
            maxTotal = dayTotals[days[i]];
            maxDay = days[i];
        }
    }

    printf("\n Day with most profit: %d, Profi of the day: %d", maxDay, maxTotal);

}