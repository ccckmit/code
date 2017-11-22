#include <stdio.h>
#include <stdarg.h>

void printList(int head, ... ) {
  va_list va;
  va_start(va, head);
  int i;
  for(i=head ; i != -1; i=va_arg(va,int)) {
    printf("%d ", i);
  }
  va_end(va);
}

int main( void ) {
  printList(3, 7, 2, 5, 4, -1);
}
