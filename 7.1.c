/*
Implement a program that creates a chain of N threads (in addition to the main thread). 
The chain must comply with following sequence: 1st thread creates 2nd thread, 2nd thread creates 3rd thread, ..., (N-1) thread creates Na thread. 
Each thread should print its ID and the ID of the thread that created it. Ensure that the information displayed on the screen will occur in the order
inverse of the creation of threads, that is, initially the information of the Na thread appears, after the (N-1)a , ..., then of the 2nd and finally of the 1st.
*/
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX 1000000

pthread_t threads[MAX];
int counter = 0;
long int number = 0;

typedef struct {
    long int number;
}thread_arg, *ptr_thread_arg;


void *thread_function(void *arg){    
    
    printf("'Child'  Thread - %lu \n\n", pthread_self());
    counter++;
    
    if (counter < number){
        pthread_create(&threads[counter], NULL, thread_function, (void *)counter);
        printf("'Parent' Thread - %lu \n", pthread_self());
        pthread_join(threads[counter], NULL);
    }
}

int main(int argc, char *argv[]) {
 
     if (argc < 1) {
        printf("Please write the number of threads!\n");
        return 1;
    }

    number = atol(argv[1]);

    pthread_create(&threads[0], NULL, thread_function, (void *)0);
    
    printf("'Parent' Thread - %lu \n", pthread_self());

    pthread_join(threads[0], NULL);

    return 0;
}
