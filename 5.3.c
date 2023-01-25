/*
The following is a serial version of a program to calculate all prime numbers up to a given number.
Implement a version with multiple processes collaborating to calculate prime numbers.
Rate the performance of your program with two input values: 10,000,000 and 100,000,000. 
When making the comparison, print the result to the screen, as the competition for I/O accomplishments made the program much slower and affected an evaluation.
*/

#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    long int numero;
    int imprimir;
    int numero_thread;
}thread_arg, *ptr_thread_arg;

int verifica_se_primo(long int);
int *thread_funcao (void* arg);
int verificacao_um (long int numero, short int imprimir);

pthread_t threads[3];

int main(int argc, char *argv[]) {

    long int numero = 0;
    short int imprimir, thread;
    pthread_t t1, t2, t3, t4;
    unsigned long resultado = 0;
    int i;

    if (argc != 4) {
        printf ("Uso correto: %s <numero> <imprimir=1,nao_imprimir=0> <multiple threads=1,single thread=0>\n\n", argv[0]);
        return 1;
    }
 
    numero = atol(argv[1]);
    imprimir = atoi(argv[2]);
    thread = atoi(argv[3]);

    if (thread == 0)    
        verificacao_um(numero, imprimir);
    
    else if (thread == 1){

        clock_t start, end;
        start = clock();

        thread_arg arguments[3];
        for (i = 1; i < 5; i ++){
            arguments[i].numero = numero;
            arguments[i].imprimir = imprimir;
            arguments[i].numero_thread = i;
            pthread_create(&(threads[i]), NULL, thread_funcao, &(arguments[i]));
        }
       
       for(i = 1 ; i < 5; i++) {
            pthread_join(threads[i], NULL);
       }

       end = clock();
       double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
       
       printf("\nTempo de execução: %f segundos\n\n", time_spent);

    }   
    else
        printf("\nValores inválidos, por favor, digite um valor válido\n\n");


    return 0;
}

int *thread_funcao (void* arg){

    ptr_thread_arg targ = (ptr_thread_arg)arg;
    
    long int numero = targ->numero;
    int imprimir = targ->imprimir;
    int numero_thread = targ->numero_thread;
    short int result;   
  
    int inicio = ((numero/4) * numero_thread) - (numero/4);
    int final = (numero / 4) * numero_thread;

    for (long int num_int = inicio; num_int <= final; num_int++) {
        result = verifica_se_primo(num_int);
            if (imprimir == 1)
                if (result == 1)
                    printf("%ld eh primo.\n", num_int);  
    }
}

int verificacao_um (long int numero, short int imprimir){

    clock_t start, end;
    start = clock();

    short int result;

    for (long int num_int = 1; num_int <= numero; num_int++){
        result = verifica_se_primo(num_int);
        if (imprimir == 1)
            if (result == 1)
                printf("%ld eh primo.\n", num_int);
    }

    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTempo de execução: %f segundos\n\n", time_spent);

}

int verifica_se_primo(long int numero) {
    long int ant;
    
    for (ant = 2; ant <= (long int)sqrt(numero); ant++) {
        if (numero%ant == 0)
        return 0;
    }

    if (ant*ant >= numero)
        return 1;
}
