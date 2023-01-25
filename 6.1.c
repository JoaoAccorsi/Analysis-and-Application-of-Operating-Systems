/*
Install the figlet application that takes a text and rewrites it in a stylish way in the terminal. 
Implement a program that, upon receiving the SIGUSR2 signal, executes a function that executes the figlet application. 
The text must be entered by the user prior to the call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAX 1000
#define FIGLET "figlet "

char text[MAX];
char command[MAX] = "";

void handle_SIGUSR2(int sig){
    
    pid_t pid = fork();
    
    if (pid == 0){
        sleep(5);
        kill(getpid(), SIGUSR1); // Send SIGUSR1 signal to the parent
    }else{
        strcat(command, FIGLET);
        strcat(command, text);   
        system(command);
    }
}

int main(){

    sigset_t mask;

    scanf("%[^\n]", text);
   
    struct sigaction action;
    memset(&action, 0, sizeof(action));

    action.sa_flags = SA_RESTART;
    action.sa_handler = &handle_SIGUSR2;
    sigaction(SIGUSR2, &action, NULL);

    printf("PID: = %d\n", getpid());
    fflush(stdout);
    
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR2);
    sigdelset(&mask, SIGINT);

    while(1){
        sigsuspend(&mask);
    }

    return 0;
}
