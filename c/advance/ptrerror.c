#include <stdio.h>

int main() {
  int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *ptr = a;
  int i;
  for (i=0; i<3; i++) {
    printf("%d ", *ptr);
    ptr += sizeof(int);
  }
}
