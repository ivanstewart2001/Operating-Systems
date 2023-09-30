#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t print_flag = 0;

void handler(int signum) { 
  printf("Hello World!\n");
  print_flag = 1;
  alarm(1); 
}

int main(int argc, char * argv[]) {
  signal(SIGALRM, handler); 
  alarm(1); 
  while(1) {
    if (print_flag) {
      printf("Turing was right!\n");
      print_flag = 0;
    }
  }
  return 0; 
}
