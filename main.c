#include<stdio.h>
#include<stdlib.h>


void readFile(const char* fileName){

    FILE *file;
    file = fopen(fileName, "read");

    if(file == NULL){
        printf("Error! File not found.");   
        exit(1);
    }
    char c;
    int wordLen = 0;
    char tmp[63];

    

    while((c = fgetc(file)) != EOF){
        
        if(c == ','){
            tmp[wordLen] = '\0';
            printf("%s, ", tmp);
            wordLen = 0;
            continue;
        }
        if(c == '\n'){
            printf("YAY");
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