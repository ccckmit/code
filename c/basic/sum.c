#include <stdio.h>

int main() 
{
  int sum=0, i;
  for (i=0; i<=10; i++)
    sum += i;
  printf("sum(1..10)=%d", sum);
}
