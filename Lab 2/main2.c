#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


#define MAX_COUNT 30
#define MAX_SLEEP 10

void ChildProcess(void) {
    int i;
    int num_iterations = (random() % MAX_COUNT) + 1;

    for (i = 1; i <= num_iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep(random() % MAX_SLEEP);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }
    exit(0);
}

void ParentProcess(void) {
    int status;
    pid_t pid;

    pid = wait(&status);
    printf("Child Pid: %d has completed\n", pid);
}

int main(void) {
    pid_t pid1, pid2;

    srandom(time(NULL));

    pid1 = fork();
    if (pid1 == 0) 
        ChildProcess();

    pid2 = fork();
    if (pid2 == 0) 
        ChildProcess();

    ParentProcess();
    ParentProcess();

    return 0;
}
