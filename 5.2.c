/*
Multiply two matrices, each matrix being created by different processes. The multiplication calculation can be carried out in any of the processes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int length = 4;

void multiply(int matrixA[length][length], int matrixB[length][length]){

        int i, j, k;
        int matrix[length][length];

                // Multiply the matrixes
        for (i = 0; i < length; i++)
                for (j = 0; j < length; j++)
                        matrix[i][j] = 0;

        for (i = 0; i < length; i++)
                for (j = 0; j < length; j++)
                        for (k = 0; k < length; k++)
                                matrix[i][j] = matrixA[i][k] * matrixB[k][j];

        printf("Result - Multiplied Matrices:");
        printMatrix(matrix);
}

void printMatrix(int matrix[length][length]){

        int i, j;

        printf("\n");
        for (i = 0; i < length; i++)
                for (j = 0; j < length; j++)
                        if (j < length - 1)
                                printf(" %d ", matrix[i][j]);
                        else
                                printf(" %d \n", matrix[i][j]);
        printf("\n");
}


int main(){

        int file_pipe[2];
        int matrixA[length][length], matrixB[length][length];
        int fork_result, status, i, j;

        time_t t;
        srand((unsigned) time(&t));

        if (pipe(file_pipe) == -1)
                return 1;

        fork_result = fork();
        if (fork_result == -1)
                return 2;
                
        if (fork_result != 0){ // Parent Process

                waitpid(fork_result, &status, 0);

                        // Create matrixA
                for (i = 0; i < length; i++)
                        for (j = 0; j < length; j++)
                                matrixA[i][j] = rand() % 20;

                        // Print matrixA in the screen
                printf("MatrixA:");
                printMatrix(matrixA);

                        // Read the pipe
                int matrixRead[length][length];
                if (read(file_pipe[0], &matrixRead, sizeof(matrixRead)) == - 1) { return 3;}
                printf("---\nProcess 1: Read Matrix B from the pipe!\n---\n\n");

                        // Calls function multiply to multiply the matrixes
                multiply(matrixA, matrixRead);

        }else{  // Child process

                        // Create MatrixB
                for (i = 0; i < length; i++)
                        for (j = 0; j < length; j++)
                                matrixB[i][j] = rand() % 10;

                        // Print matrixB in the screen
                printf("\nMatrixB: ");
                printMatrix(matrixB);

                        // Write MatrixB in the pipe
                if (write(file_pipe[1], &matrixB, sizeof(matrixB)) == -1) { return 4;}
                printf("---\nProcess 2: Wrote MatrixB in the pipe!\n---\n\n");
        }

        return 0;
}
