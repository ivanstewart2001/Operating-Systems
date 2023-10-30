#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_SLEEP_TIME 5
#define MAX_DEPOSIT 100
#define MAX_WITHDRAW 50
#define NUM_ITERATIONS 25

typedef struct {
    int BankAccount;
    int Turn;
} shared_data;

void DearOldDad(shared_data *data) {
    srand(time(NULL));
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sleep(rand() % MAX_SLEEP_TIME);
        int account = data->BankAccount;
        while (data->Turn != 0);
        if (account <= 100) {
            int balance = rand() % MAX_DEPOSIT;
            if (balance % 2 == 0) {
                account += balance;
                printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, account);
            } else {
                printf("Dear old Dad: Doesn't have any money to give\n");
            }
        } else {
            printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
        }
        data->BankAccount = account;
        data->Turn = 1;
    }
}

void PoorStudent(shared_data *data) {
    srand(time(NULL));
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sleep(rand() % MAX_SLEEP_TIME);
        int account = data->BankAccount;
        while (data->Turn != 1);
        int balance = rand() % MAX_WITHDRAW;
        printf("Poor Student needs $%d\n", balance);
        if (balance <= account) {
            account -= balance;
            printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, account);
        } else {
            printf("Poor Student: Not Enough Cash ($%d)\n", account);
        }
        data->BankAccount = account;
        data->Turn = 0;
    }
}

int main() {
    int ShmID = shmget(IPC_PRIVATE, sizeof(shared_data), IPC_CREAT | 0666);
    if (ShmID < 0) {
        printf("*** shmget error ***\n");
        exit(1);
    }

    printf("Process has received a shared memory of two integers...\n");

    shared_data *data = (shared_data *) shmat(ShmID, NULL, 0);
    if (data == (void *) -1) {  
        printf("*** shmat error ***\n");
        exit(1);
    }

    printf("Process has attached the shared memory...\n");

    data->BankAccount = 0;
    data->Turn = 0;

    printf("Orig Bank Account = %d\n", data->BankAccount);

    pid_t pid = fork();
    if (pid < 0) {
        printf("*** fork error ***\n");
        exit(1);
    } else if (pid == 0) {
        PoorStudent(data);
        exit(0);
    }

    DearOldDad(data);

    wait(NULL);
    printf("Process has detected the completion of its child...\n");

    shmdt((void *) data);
    printf("Process has detached its shared memory...\n");

    shmctl(ShmID, IPC_RMID, NULL);
    printf("Process has removed its shared memory...\n");

    printf("Process exits...\n");
    
    return 0;
}
