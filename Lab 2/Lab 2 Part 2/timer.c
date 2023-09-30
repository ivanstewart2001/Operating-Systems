#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t timer = 0;
volatile sig_atomic_t flag = 0;

void handler(int signum) {
  printf("Hello World!\n");
  timer++;
  flag = 1;
  alarm(1);
}

void exit_handler(int signum) {
  printf("Total time: %d seconds\n", timer);
  exit(0);
}

int main(int argc, char * argv[]) {
  signal(SIGALRM, handler);
  signal(SIGINT, exit_handler); 
  alarm(1); 
  while (1) {
    if (flag) {
      printf("Turing was right!\n");
      flag = 0;
    }
  }
  return 0; 
}
