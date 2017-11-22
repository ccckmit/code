#include <stdio.h>

int sum(int n) {
  int s=0;
  int i;
  for (i=1; i<=n;i++) {
     s = s + i;
  }
  return s;
}

int main(void) {
  int sum1 = sum(10);
  printf("sum=%d\n", sum1);
  system("pause");
  return 1;
}

