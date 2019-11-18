#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h> 
#include<sys/wait.h>
#include"fileIO.h"
#include <sys/types.h> 

#define WRITE 1
#define READ  0

int randr(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int isUnique(char* str, char* itemSet[]){
    int i=0;
    if (itemSet[i] == NULL){
        return 1;
    }
    do{
        if(!strcmp(str, itemSet[i])){
            return 0;
        }
        i++;
    }while(itemSet[i] != NULL);

    return 1;
}

void createPrices(){
    
    Transaction* transactions = readFile("market.txt");
    char* itemSet[1024];
    int priceSet[1024];
    int uniqueNum = 0;
    int j, i=0;
    while(transactions[i].customer != NULL){
        j = 0;
        while(transactions[i].items[j] != NULL){
            if(isUnique(transactions[i].items[j], itemSet)){
                itemSet[uniqueNum] = transactions[i].items[j];
                priceSet[uniqueNum] = randr(1,100);
                uniqueNum++;
            }
            j++;
        }
        i++;
    }
    writeFile("price.txt", itemSet, priceSet);
}


int main(){

    createPrices();

    
/*
    TESTER
    int j, i=0;
    while(transactions[i].customer != NULL){
        printf("\nDay: %d", transactions[i].day);
        printf("\nCustomer: %d", transactions[i].customer);
        j = 0;
        while(transactions[i].items[j] != NULL){
            printf("\nItem: %s", transactions[i].items[j]);
            j++;
        }
        i++;
    }
*/
    fflush(stdout);

    int n1 = fork(); 
    int n2 = fork();
    int n3 = fork();
  
    if (n1 > 0 && n2 > 0 && n3 > 0) { 
        printf("parent\n"); 
        printf("%d %d \n", n1, n2); 
        printf(" my id is %d \n", getpid()); 
    } 

    
    return 0; 

/*
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
            // CHILD PROCES    Close other end first. 
            int taskId;
            printf("Hi, I am child %d\n", i);
            close (fds[WRITE]);
            read(fds[READ], &taskId, sizeof(taskId));
            printf("Task id: %d \n", taskId);
            close(fds[READ]);
            exit(0);
        }
        else if (pid < (pid_t) 0){
            // The fork failed. 
            fprintf (stderr, "Fork failed.\n");
            return EXIT_FAILURE;
        }
        else {
            // PARENT PROCESS Close other end first. 
            int taskId = randr(1,5);
            close (fds[READ]);
            write(fds[WRITE], &taskId, sizeof(taskId));
            close(fds[WRITE]);
        }
    }
    */
    return 1;
}
