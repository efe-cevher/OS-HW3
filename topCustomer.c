#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>

int main(){

    Transaction* transactions = readFile("market.txt"); //Get neccesary data from file, via method in FileIO.c

    int customerTotals[1024] = {0};
    int customers[128];
    int totalCustomers = 0;

    char* item;
    int i=0, j, count=0;
    while(transactions[i].customer > 0){ //While data is valid continue traversing the array
        j = 0;
        int new = 1;
        for(int k=0; k<totalCustomers; k++){
            if(customers[k] == transactions[i].customer){  //check if is it first occurance of the customer
                new = 0; 
                break;
            }
        }
        if(new){ //if its first occurence assign a location for him/her to track
            customers[totalCustomers] = transactions[i].customer;
            totalCustomers++;
        }
        
        while(transactions[i].items[j] != NULL){

            item = transactions[i].items[j];
            customerTotals[transactions[i].customer]++; //increment assigned location for customer for each item of the transaction
            j++;
        }
        i++;
    }
    int maxTotal = 0;
    int maxCustomer = 0;

    //find the max
    for(int i=0; i<totalCustomers; i++){ 
        if(customerTotals[customers[i]] > maxTotal){
            maxTotal = customerTotals[customers[i]];
            maxCustomer = customers[i];
        }
    }

    printf("\nCustomer id of customer who purchased most items: %d\n", maxCustomer); // console output

}
