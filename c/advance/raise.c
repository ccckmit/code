#include<signal.h>
#include<stdio.h>

void catch_function(int);

int main(void) {
  if(signal(SIGINT, catch_function)==SIG_ERR){
    printf("signal(SIGINT, catch_function) fail!\n");
    exit(0);
  }

  printf("raise(SIGINT)\n");
  if(raise(SIGINT)!=0) {
    printf("raise(SIGINT) fail !\n");
    exit(0);
  }
  printf("return\n");
  return 0;
}

void catch_function(int signal) {
  printf("catch error!\n");
}
