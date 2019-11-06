#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"transaction.h"


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
    Transaction* transactions[100];


    while((c = fgetc(file)) != EOF){

        if(c == ' '){
            continue;
        }

        if(c == ',' || c == '\n'){

            tmp[wordLen] = '\0';

            

            if(wordNo == 0){
                transactions[lineNo] = (Transaction*)malloc(sizeof(Transaction*));
                char subStr[wordLen - 4];
                memcpy(subStr, &tmp[4], wordLen - 4);
                transactions[lineNo]->day = atoi(subStr);
                printf("%d", atoi(subStr));
            }else if (wordNo == 1){
                char subStr[wordLen - 9];
                memcpy(subStr, &tmp[9], wordLen - 9);
                transactions[lineNo]->customerId = atoi(subStr);
            }else{
                transactions[lineNo]->items = (char**) malloc(sizeof(char*) * 64);
                transactions[lineNo]->items[wordNo - 2] = tmp; 
            }

            if(c == '\n'){
                wordNo = 0;
                wordLen = 0;
                lineNo++;
                continue;
            }
            
            wordLen = 0;
            wordNo++;
            continue;
        }
        
        tmp[wordLen] = c;
        wordLen++;
        
    }
}

int main(){

    readFile("market.txt");
    printf("\n");

    return 0;
}