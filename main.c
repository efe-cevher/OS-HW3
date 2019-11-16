#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"transaction.h"

int days[127];
int customers[127];
char* items[127][63];
char* itemSet[127];


/*
struct transaction {
    int day;
    int customerId;
    Item* items;
};
typedef struct transaction Transaction;

struct item {
    char* name;
    int price;
};
typedef struct item Item;
*/

int fpeek(FILE *stream) {
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

int isUnique(char* strIn){
    int i;
    int len = sizeof(itemSet)/sizeof(itemSet[0]);

    if(len > 0 ){
        for(i = 0; i < len; ++i){
            if(itemSet[i] != NULL){
                if(!strncmp(itemSet[i], strIn, strlen(strIn))){
                    return 0;
                }
            }
            
        }
    }
    
    
    return 1;
}

void readFile(const char* fileName){

    FILE *file;
    file = fopen(fileName, "read");

    if(file == NULL){
        printf("Error! File not found.");   
        exit(1);
    }
    char c;
    int wordLen = 0;
    int wordNo = 0;
    int lineNo = 0;
    char tmp[63];
    int uniqueCount=0;

    while((c = fgetc(file)) != EOF){

        if(c == ' '){
            char p = fpeek(file);
            if(isalpha(p) == 0 || wordLen == 0){
                continue;
            }
        }

        if(c == ',' || c == '\n'){

            tmp[wordLen] = '\0';

            if(wordNo == 0){
                int numLen = wordLen - 4;
                char subStr[numLen+1];
                for(int i=0; i<numLen; i++){
                    subStr[i] = tmp[4+i];
                }
                subStr[numLen] = '\0';
                days[lineNo] = atoi(subStr);
            }else if (wordNo == 1){
                int numLen = wordLen - 9;
                char subStr[numLen+1];
                for(int i=0; i<numLen; i++){
                    subStr[i] = tmp[9+i];
                }
                subStr[numLen] = '\0';
                customers[lineNo] = atoi(subStr);
            }else{
                char str[wordLen];
                char* strPointer = malloc(sizeof(char)*wordLen);
                for(int i=0; i<wordLen;i++){
                    str[i] = tmp[i];
                }
                str[wordLen] = '\0'; 
                strcpy(strPointer, str);
                items[lineNo][wordNo-2] = strPointer;

                printf("\n Str: %s", strPointer);

                if(isUnique(strPointer)){
                    itemSet[uniqueCount] = strPointer;
                    uniqueCount++;
                }
            }

            if(c == '\n'){
                wordNo = 0;
                wordLen = 0;
                lineNo++;
                continue;
            }else{
                wordNo++;
                wordLen = 0;
            }
        }else{
            tmp[wordLen] = c;
            wordLen++;
        }
    }
    printf("\nCOUNT: %d", uniqueCount);
    fclose(file);
}

int main(){

    readFile("market.txt");

    int counter = 0;
    for (int i=0; i<20; i++){
        printf("\nDay: %d", days[i]);
        printf("\nCustomer: %d", customers[i]);
        
        for(int j=0; j<10; j++){
            if(items[i][j] != NULL){
                printf("\nItem: %s", items[i][j]);
    
            }
            
        }
        
        

        
    }
    int i=0;
        while (itemSet[i] != NULL)
        {
            printf("\n un: %s", itemSet[i]);
            i++;
        }
    

    return 0;
}