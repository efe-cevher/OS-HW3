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
#define BUFFER_SIZE 64

int randr(int min, int max){ //generate rand vaiue in range
    
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int isUnique(char* str, char* itemSet[]){ //check if item is unique return 1 if it is 0 if not
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
    
    Transaction* transactions = readFile("market.txt"); //Get neccesary data from file, via method in FileIO.c
    char* itemSet[1024];
    int priceSet[1024];
    int uniqueNum = 0;
    int j, i=0;
    while(transactions[i].customer > 0){ //While data is valid continue traversing the array
        j = 0;
        while(transactions[i].items[j] != NULL){
            if(isUnique(transactions[i].items[j], itemSet)){
                itemSet[uniqueNum] = transactions[i].items[j];
                priceSet[uniqueNum] = randr(1,100); //set rand price
                uniqueNum++;
            }
            j++;
        }
        i++;
    }
    writeFile("price.txt", itemSet, priceSet);
}

// Executed inside child provess when its turn
void childProcess(int taskId, char* arg){
    switch (taskId)
    {
    case 1:
    {
        char* argv[2];
		argv[0] = "getProducts.out";
        argv[1] = NULL; // with no arg

		if(execv(argv[0], argv)==-1) //exec funciton to give the process the actual task
			printf("Error in calling exec!!\n");
        break;
    }
    case 2:
    {
        char* argv[2];
		argv[0] = "findSellRate.out";
        argv[1] = arg; // with arg

		if(execv(argv[0], argv)==-1)
			printf("Error in calling exec!!\n");
        break;
    }
    case 3:
    {
        char* argv[2];
		argv[0] = "customerTotal.out";
        argv[1] = arg;

		if(execv(argv[0], argv)==-1)
			printf("Error in calling exec!!\n");
        break;
    }
    case 4:
    {
        char* argv[2];
		argv[0] = "topCustomer.out";
        argv[1] = NULL;

		if(execv(argv[0], argv)==-1)
			printf("Error in calling exec!!\n");
        break;
    }
    case 5:
    {
        char* argv[2];
		argv[0] = "mostProfit.out";
        argv[1] = NULL;

		if(execv(argv[0], argv)==-1)
			printf("Error in calling exec!!\n");
        break;
    }
    default:
        break;
    }
}



int main(){
    
    srand(time(NULL)); //initalizer for randoms to work
    createPrices(); //Create prices.txt

    // file descriptors
    int fds[2]; //pipe to send task id 
    int fds2[2]; // child process that took the task id sends back its pid to make parent process wait until its done

    if (pipe (fds) || pipe(fds2)){
        fprintf (stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }

    int n1 = fork(); 
    int n2 = fork();
    int n3 = fork();
    //Created 7 child processes, there are total 8 processes now

    if (n1 > 0 && n2 > 0 && n3 > 0) { //PARENT PROCESS

    close(fds[READ]);
    close (fds2[WRITE]);

        while (1){

            sleep(1); // waiting for better testing experience

            char argTmp[BUFFER_SIZE];
            
            
            int taskId = randr (1,5); //Choose a random task

            printf("\n\n>Task No:%d is about to be executed! (if any child processes left)\n\n", taskId);
            sleep(2); // waiting for better testing experience

            if(taskId == 2){
                printf("Enter the target product to find its sell rate: ");
                scanf(" %s", argTmp);
            }else if(taskId == 3){
                printf("Enter target customers id: ");
                scanf(" %s", argTmp);
            }

            char arg[BUFFER_SIZE];
            for(int i=0; i<BUFFER_SIZE; i++){
                arg[i] = argTmp[i];
            }
            char task[BUFFER_SIZE];

            sprintf(task, "%d,%s", taskId, arg); //combined task id and argument as string before sending (make sure they goes to same process) 
            write(fds[WRITE], &task, BUFFER_SIZE);
            char childPid[BUFFER_SIZE];
            
            read(fds2[READ], &childPid, BUFFER_SIZE);
            
            pid_t cPid = (pid_t) atoi(childPid);
            int status;
            waitpid(cPid,&status,0); //Parent waits for the executing task
            

        }
        close(fds2[READ]);
        close(fds[WRITE]);

    }else if(n1<0 || n2<0 || n3<0){ //Error condition
        fprintf (stderr, "Fork Failed\n");
        return EXIT_FAILURE;
    }
    
    else{ //CHILD PROCESSES

        close (fds[WRITE]);
        close (fds2[READ]);

        while (1){

            char task[BUFFER_SIZE];
            read(fds[READ], task, BUFFER_SIZE);     

            char *pt;
            pt = strtok (task,",");

            int taskId = atoi(pt);
            pt = strtok (NULL, ",");
            char* arg = pt;

            if(taskId > 0 && taskId <6){

                //printf("CHILD entering my id is %d \n", getpid());
                char childPid[BUFFER_SIZE];
                sprintf(childPid, "%d", getpid());
                write(fds2[WRITE], childPid, BUFFER_SIZE); //feedback to parent
                childProcess(taskId, arg); //exec
                exit(0); // end process successfully
            }
        }

        close(fds[READ]);
        close(fds2[WRITE]);

    }

    return 1;
}
