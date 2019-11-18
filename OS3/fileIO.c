#include<stdio.h>
#include<stdlib.h>
#include"fileIO.h"
#include<string.h>
#include<ctype.h>
#include<time.h>

Transaction transactions[128];
Product products[128];
int days[128];
int customers[128];
char* items[128][64];
int lineNo = 0;

int fpeek(FILE *stream) { //Peek next char in the file
    int c;
    c = fgetc(stream);
    ungetc(c, stream);
    return c;
}

Transaction* readFile(const char* fileName){

    FILE *file;
    file = fopen(fileName, "read");

    if(file == NULL){
        printf("Error! File not found.");   
        exit(1);
    }

    char c;
    char tmp[64];
    int tmpDay = 0, tmpCustomerId = 0;
    char* itemsTemp[128];
    int wordLen = 0, wordNo = 0;

    while(c = fgetc(file)){

        if (c == EOF){
            if(wordNo > 1){
                c = '\r';
            }else{
                break;
            }
        }
        

        if(c == ' '){
            char p = fpeek(file);
            if(isalpha(p) == 0 || wordLen == 0){
                continue;
            }
        }
        
        if(c == ',' || c == '\r'){

            tmp[wordLen] = '\0';

            if(wordNo == 0){
                int numLen = wordLen - 4;
                char subStr[numLen+1];
                for(int i=0; i<numLen; i++){
                    subStr[i] = tmp[4+i];
                }
                subStr[numLen] = '\0';
                tmpDay = atoi(subStr);
            }else if (wordNo == 1){
                int numLen = wordLen - 9;
                char subStr[numLen+1];
                for(int i=0; i<numLen; i++){
                    subStr[i] = tmp[9+i];
                }
                subStr[numLen] = '\0';
                tmpCustomerId = atoi(subStr);
            }else{
                char str[wordLen];
                char* strPointer = malloc(sizeof(char)*wordLen);
                for(int i=0; i<wordLen+1;i++){
                    str[i] = tmp[i];
                }
                strcpy(strPointer, str);
                itemsTemp[wordNo-2] = strPointer;         
            }

            if(c == '\r'){

                Transaction* t = (Transaction*)malloc(sizeof(Transaction*));
                t->day = tmpDay;
                t->customer = tmpCustomerId;

                for(int i=0; i<wordNo-1; i++){
                    t->items[i] = itemsTemp[i];
                }

                transactions[lineNo] = *t;

                c = fgetc(file);
                wordNo = 0;
                lineNo++;
            }else{
                wordNo++;
            }
            wordLen = 0;

        }else{
            tmp[wordLen] = c;
            wordLen++;
        }
    }
    fclose(file);
    return transactions;
}

void writeFile(const char* fileName, char* itemSet[], int priceSet[]){
    FILE *file;
    file = fopen(fileName, "w");
    int i = 0;
    while(itemSet[i] != NULL){
        fprintf(file,"%s, %d₺\n", itemSet[i], priceSet[i]);
        i++;
    }
    fclose(file);
}

Product* readProducts(const char* fileName){
    FILE *file;
    file = fopen(fileName, "read");


    if(file == NULL){
        printf("Error! File not found.");   
        exit(1);
    }

    char c;
    char tmp[64];
    char* tmpName;
    int tmpPrice = 0;
    int wordLen = 0, wordNo = 0;

    while(c = fgetc(file)){

        if (c == EOF && wordNo < 1){
            break;
        }
        
        if(c == ' '){
            char p = fpeek(file);
            if(isalpha(p) == 0 || wordLen == 0){
                continue;
            }
        }
        
        if(c == ',' || c == '\n'){

            tmp[wordLen] = '\0';

            if(wordNo == 0){
                char str[wordLen];
                tmpName = malloc(sizeof(char)*(wordLen + 1));
                for(int i=0; i<wordLen+1;i++){
                    str[i] = tmp[i];
                }
                strcpy(tmpName, str);
            }else if (wordNo == 1){
                char subStr[wordLen-1];
                for(int i=0; i<wordLen-1; i++){
                    subStr[i] = tmp[i];
                }
                subStr[wordLen-1] = '\0';
                tmpPrice = atoi(subStr);
            }else{
                printf("ERROR");        
            }

            if(c == '\n'){

                Product* p = (Product*)malloc(sizeof(Product*));
                p->name = tmpName;
                p->price = tmpPrice;

                products[lineNo] = *p;

                wordNo = 0;
                lineNo++;
            }else{
                wordNo++;
            }
            wordLen = 0;

        }else{
            tmp[wordLen] = c;
            wordLen++;
        }
    }
    fclose(file);
    return products;
}

