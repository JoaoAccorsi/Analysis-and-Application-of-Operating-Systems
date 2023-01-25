/*
Using Mutex, create a thread_C that captures the temperature (random values) of a farm every second. 
Also, create a thread_P that receives the temperature values from thread_C and processes the temperature average every 10 seconds (parameterized value). 
Finally, create a thread_M that receives the temperature values average of thread_P and report when this average value is below a linear (defined value) 
to activate irrigation from the farm.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

pthread_t threads[2];
int temperature_sum = 0;
int counter = 0;
int temperature = 0;
int hour = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void* thread_M(void* arg){
    int temp = (int *)arg;
    char command[100] = "figlet -f digital Temperature below 15 degrees Celsius!\n";
    
    if (temp < 15)
        system(command);
}

void* thread_P(void* arg){
    pthread_mutex_lock(&mutex);
    
    if (counter < 10)
        pthread_cond_wait(&condition, &mutex);

    hour = hour + 10;
    int aux = (int *)arg;
    int average_temperature_10s = aux / 10;

    printf("Average temperature %ds: %.2d°C\n", hour, average_temperature_10s);
    pthread_create(&threads[2], NULL, &thread_M, (void *)average_temperature_10s);

    pthread_mutex_unlock(&mutex);

}

void* thread_C(){
    pthread_mutex_lock(&mutex);

    temperature = random() % 40;
    temperature_sum = temperature_sum + temperature;
    counter++;

    if (counter == 10){
        pthread_cond_signal(&condition);
        pthread_create(&threads[1], NULL, &thread_P, (void *)temperature_sum);
        counter = 0;
        temperature_sum = 0;
    }

    pthread_mutex_unlock(&mutex);
}

int main() {
    srand(time(NULL));
    
    while(1){
        pthread_create(&threads[0], NULL, &thread_C, NULL);
        sleep(1);
    }

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    
    pthread_exit(NULL);
    return 0;
}
