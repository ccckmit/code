#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int sum1 = sum(10);
  printf("sum=%d", sum1);
  return 1;
}

int sum(int n) {
  int s=0;
  int i;
  for (i=1; i<=n;i++) {
     s = s + i;
  }
  return s;
}
