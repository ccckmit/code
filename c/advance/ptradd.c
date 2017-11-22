#include <stdio.h>

int main() {
  char c = 'a';
  char *cp = &c;
  printf("&c=%p\n", &c);
  printf("cp=%p\n", cp);
  printf("cp+1=%p\n", cp+1);
  printf("cp+3=%p\n", cp+3);

  int i = 1;
  int *ip = &i;
  printf("&i=%p\n", &i);
  printf("ip=%p\n", ip);
  printf("ip+1=%p\n", ip+1);
  printf("ip+3=%p\n", ip+3);
}
