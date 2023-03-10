/*
Implement two processes that promote a task, collaboratively. A process must download pages from the Internet, for example, using the curl program. 
The second process receives these pages and performs a parser to find the amount of a given word, for example using the egrep and wc programs. 
The second program returns the number of occurrences for the first process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1000
#define EGREP "egrep -oi "
#define FORMAT "'"
#define WORD "rock"
#define PIPE " | "
#define WC "wc -l"
#define OUTPUT " > result.txt"

int main(int argc, char *argv[]){

        int file_pipe[2];
        int fork_result, status;
        char command[MAX] = "";
        FILE* ptr;
        char ch, result;

        fork_result = fork();
        if (fork_result == -1)
                return 1;

        if (fork_result != 0){  

                sleep(3);

                dup(file_pipe[0]);

                char *page_content;
                read(file_pipe[0], page_content, sizeof(page_content));
                printf("Page content read from the pipe!\n");

                strcat(command, EGREP);
                strcat(command, FORMAT);
                strcat(command, WORD);
                strcat(command, FORMAT);
                strcat(command, *page_content);
                strcat(command, PIPE);
                strcat(command, WC);
                strcat(command, OUTPUT);
                system(command);

                                // Send the found pattern to the pipe
                ptr = fopen("result.txt", "r");

                do{
                        result = fgetc(ptr);
                }while(result != EOF);
                pclose(ptr);

                write(file_pipe[1], &result, MAX);
                printf("\nPage pattern was sent to the pipe!\n");

                sleep(2);

        }else{ 

                        // Download the page content and stores in file "file.txt"
                system("curl https://rockinrio.com/rio/pt-br/home/ --output file.txt");
                printf("Page content downloaded!\n");

                        // Read "file.txt" file, and store it in variable ch
                ptr = fopen("file.txt", "r");

                do {
                        ch = fgetc(ptr);
                } while(ch != EOF);
                pclose(ptr);

                        // Writes ch to the pipe
                write(file_pipe[1], &ch, sizeof(ch));
                printf("Page content sent to the pipe!\n");

                sleep(3);

                        // Write the found pattern in the screen
                char *final_result;
                read(file_pipe[0], final_result, MAX);
                printf("\nPage pattern read from the pipe!\n");
                printf("\n---\nThe final pattern found was: %d\n---\n\n", *final_result);

        }
}
