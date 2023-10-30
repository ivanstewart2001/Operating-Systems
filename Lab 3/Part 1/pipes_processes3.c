// START OF pipes_processes3.c FILE //

#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char **argv)
{
    printf("\n");

    int pipefd[2];
    int pipefd2[2];

    char *cat_args[] = {"cat", "scores", NULL};
    char *grep_args[] = {"grep", argv[1], NULL};
    char *sort_args[] = {"sort", NULL};

    // create pipe1
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    // fork (cat)
    if (fork() == 0) {
        // replace stdout with write end of pipe
        dup2(pipefd[1], 1);

        // close unused read end
        close(pipefd[0]);

        // execute cat
        execvp("cat", cat_args);
        exit(0);
    }

    // create pipe2
    if (pipe(pipefd2) == -1) {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    // fork (grep)
    if (fork() == 0) {
        // replace stdin with read end of pipe
        dup2(pipefd[0], 0);

        // replace stdout with write end of second pipe
        dup2(pipefd2[1], 1);

        // close unused ends
        close(pipefd[1]);
        close(pipefd2[0]);

        // execute grep
        execvp("grep", grep_args);
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    // fork (sort)
    if (fork() == 0) {
        // replace stdin with read end of second pipe
        dup2(pipefd2[0], 0);

        // close unused write end
        close(pipefd2[1]);

        // execute sort
        execvp("sort", sort_args);
        exit(0);
    }

    close(pipefd2[0]);
    
    wait(NULL); // Wait for all child processes to finish

    printf("\n"); // Print a new line at the end of the program

    return 0;
}

// END OF pipes_processes3.c FILE //
