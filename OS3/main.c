#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h> 
#include<sys/wait.h>

#define WRITE 1
#define READ  0

int days[128];
int customers[128];
char* items[128][64];
char* itemSet[128];
int lineNo = 0;

int fpeek(FILE *stream) { //Peek next char in the file
    int c;
    c = fgetc(stream);
    ungetc(c, stream);
    return c;
}

int isUnique(char* str){
    int i=0;
    if (itemSet[i] == NULL){
        return 1;
    }
    do{
        if(!strncmp(str, itemSet[i], strlen(str))){
            return 0;
        }
        i++;
    }while (itemSet[i] != NULL);

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
    char tmp[64];
    int wordLen = 0, wordNo = 0;

    while((c = fgetc(file)) != EOF){

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
                for(int i=0; i<wordLen+1;i++){
                    str[i] = tmp[i];
                }
                strcpy(strPointer, str);
                items[lineNo][wordNo-2] = strPointer;         
            }

            if(c == '\r'){
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
}

int randr(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void writeFile(const char* fileName){
    FILE *file;
    file = fopen(fileName, "w");
    int i = 0;
    srand(time(NULL)); // initialization for random
    while(itemSet[i] != NULL){
        fprintf(file,"%s, %d₺\n", itemSet[i], randr(1,100));
        i++;
    }
    fclose(file);
}

void createPrices(){
    readFile("market.txt");
    int uniqueNum = 0;
    for(int i=0; i<lineNo; i++){
        int j = 0;
        while(items[i][j] != NULL){    
            if(isUnique(items[i][j])){
                itemSet[uniqueNum] = items[i][j];
                //printf("\nSTR: %s, len: %zu", items[i][j], strlen(items[i][j]));
                uniqueNum++;
            }
            j++; 
        }
    }
    writeFile("price.txt");
}



int main(){

    createPrices();
    
    pid_t pid;
    int fds[2]; // file descriptor

    if (pipe (fds))
    {
      fprintf (stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
    }

    for(int i = 0; i < 7; i++) {
        pid = fork();
        if (pid == (pid_t) 0) {
            /* CHILD PROCESS
                Close other end first. */
            int taskId;
            printf("Hi, I am child %d\n", i);
            close (fds[WRITE]);
            read(fds[READ], &taskId, sizeof(taskId));
            printf("Task id: %d \n", taskId);
            close(fds[READ]);
            exit(0);
        }
        else if (pid < (pid_t) 0){
            /* The fork failed. */
            fprintf (stderr, "Fork failed.\n");
            return EXIT_FAILURE;
        }
        else {
            /* PARENT PROCESS
                Close other end first. */
            int taskId = randr(1,5);
            close (fds[READ]);
            write(fds[WRITE], &taskId, sizeof(taskId));
            close(fds[WRITE]);
        }
    }
    return 1;
}
