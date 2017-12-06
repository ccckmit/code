#include <stdio.h>

int main(void) {
// #line 100 "line.c"
  printf("Compiling %s, line: %d, on %s, at %s",
           __FILE__, __LINE__, __DATE__, 
           __TIME__);

  return 0;
}
