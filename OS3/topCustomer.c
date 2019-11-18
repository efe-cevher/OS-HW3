#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>

int main(){

    Transaction* transactions = readFile("market.txt");

    int customerTotals[1024];
    int customers[128];
    int totalCustomers = 0;

    char* item;
    int i=0, j, count=0;
    while(transactions[i].customer != NULL){
        j = 0;
        int new = 1;
        for(int k=0; k<totalCustomers; k++){
            if(customers[k] == transactions[i].customer){
                new = 0;
                break;
            }
        }
        if(new){
            customers[totalCustomers] = transactions[i].customer;
            totalCustomers++;
        }

        if(customerTotals[transactions[i].customer] == NULL){
            customerTotals[transactions[i].customer] = 0;
        }
        
        while(item = transactions[i].items[j] != NULL){

            customerTotals[transactions[i].customer]++;
            j++;
        }
        i++;
    }
    int maxTotal = 0;
    int maxCustomer = 0;
    for(int i=0; i<totalCustomers; i++){
        if(customerTotals[customers[i]] > maxTotal){
            maxTotal = customerTotals[customers[i]];
            maxCustomer = customers[i];
        }
    }

    printf("\nCustomer id who purchase most items: %d", maxCustomer);

}
