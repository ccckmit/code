#include <stdio.h>

int main(void) {
// #line 100 "renameFromMacroVar.c"
  printf("Compiling %s, line: %d, on %s, at %s, STDC=%d",
           __FILE__, __LINE__, __DATE__, __TIME__, __STDC__);

  return 0;
}
