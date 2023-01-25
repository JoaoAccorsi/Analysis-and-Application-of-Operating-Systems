/*
Implement a program that creates three threads, that is, three functions. A function must write on the screen “AAAAA”, the second “BBBBB” and the third “CCCCC”. 
Run the three threads, ensuring it's always written to the screen “AAAAABBBBBCCCCC”, in that order. 
To make sure the printed order is correct, regardless of the order of scheduling, include a sleep (2) command in the second function, i.e. the one that writes “BBBBB”.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *thread_function1(void *arg){
    printf("AAAAA");
    pthread_exit(0);
}

void *thread_function2(void *arg){
    printf("BBBBB");
    sleep(2);
    pthread_exit(0);
}

void *thread_function3(void *arg){
    printf("CCCCC");
    pthread_exit(0);
}

int main(){

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);
    pthread_create(&thread3, NULL, thread_function3, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\n");

    return 0;
}
