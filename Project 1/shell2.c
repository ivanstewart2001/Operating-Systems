#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;
pid_t child_pid;

void handle_sigint(int sig) {
    printf("\n%s", prompt);
    fflush(stdout);
}

void handle_sigalrm(int sig) {
    if (child_pid != 0) {
        printf("Child process took too long and is being killed.\n");
        kill(child_pid, SIGKILL);
    }
}

int main() {
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
    char *arguments[MAX_COMMAND_LINE_ARGS];

    signal(SIGINT, handle_sigint);
    signal(SIGALRM, handle_sigalrm);

    while (true) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s%s", cwd, prompt);
        fflush(stdout);

        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }

        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        strcpy(cmd_bak, command_line);
        char *token = strtok(command_line, delimiters);
        int token_count = 0;
        while (token != NULL) {
            arguments[token_count] = token;
            token_count++;
            token = strtok(NULL, delimiters);
        }
        arguments[token_count] = NULL;

        bool background = false;
        if (token_count > 0) {
            if (strcmp(arguments[token_count - 1], "&") == 0) {
                arguments[token_count - 1] = NULL;
                background = true;
            }
        }

        char *input_file = NULL;
        char *output_file = NULL;
        for (int i = 0; i < token_count; i++) {
            if (strcmp(arguments[i], "<") == 0) {
                input_file = arguments[i + 1];
                arguments[i] = NULL;
            } else if (strcmp(arguments[i], ">") == 0) {
                output_file = arguments[i + 1];
                arguments[i] = NULL;
            }
        }

        if (strcmp(arguments[0], "cd") == 0) {
            chdir(arguments[1]);
        } else if (strcmp(arguments[0], "pwd") == 0) {
            printf("%s\n", cwd);
        } else if (strcmp(arguments[0], "exit") == 0) {
            exit(0);
        } else {
            child_pid = fork();
            if (child_pid == 0) {
                if (input_file != NULL) {
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                if (output_file != NULL) {
                    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                execvp(arguments[0], arguments);
                perror("execvp");
                exit(1);
            } else if (child_pid > 0) {
                if (!background) {
                    alarm(10);  // set the alarm to 10 seconds
                    int status;
                    waitpid(child_pid, &status, 0);
                    alarm(0);  // cancel the alarm
                }
            } else {
                perror("fork");
                exit(1);
            }
        }
    }
    return -1;
}
