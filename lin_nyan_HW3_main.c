/**************************************************************
* Class:  CSC-415-01 Spring 2023
* Name: Nyan Ye Lin
* Student ID: 921572181
* GitHub Name: yye99
* Project: Assignment 3 - Simple Shell
*
* File: lin_nyan_HW2_main.c
*
* Description: Creating a simple shell that takes and process the command line
*
**************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {

    while(1) {

        printf("prompt $ ");
        
        char *buffer = malloc(102);
        fgets(buffer,102,stdin);         // prevents buffer overflow

        // temp pointer to count space
        char *temp = buffer;

        // counting the spaces to know substring count
        // 2 spaces --> 3 substring
        int space = 0;
        for( space = 0; temp[space]; temp[space] == ' ' ? space++ : *temp++);

        // strtok to divide up the inputs
        char delimiter[] = " ";
        char *token = strtok(buffer,delimiter); 

        // 1 for last substring and 1 for NULL
        int inputLength = space + 2;     
        
        // initialzed args with new length
        char *args[inputLength];     
        
        int i = 0;
        
        while(token != NULL) {

            // strcspn to remove the \n
            // at the end of each substring
            token[strcspn(token,"\n")] = 0;

            args[i] = token;
            token = strtok(NULL,delimiter);
            i++;
        }

        // add NULL at the end to terminate
        args[i] = NULL;


        if((strcmp(args[0],"exit"))  == 0) {
            break;
        }

        pid_t pid;
        pid = fork();

        if( pid < 0) {
            printf("Error: fork faild.");
        }
        else if (pid == 0) {
            // Child Process
            execvp(args[0],args);
        }
        else { 
            
            // Parent Process
            int status;
            pid_t child = wait(&status);
            int existStatus = WEXITSTATUS(status);
            
            printf("Child : %d, existed with %d.\n",child,existStatus);
        }


    }

}