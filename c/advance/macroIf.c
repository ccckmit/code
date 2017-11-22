#include <stdio.h>

int main() {
#ifdef Linux
  printf("OS=LINUX\n");
#elif defined(Windows)
  printf("OS=Microsoft Windows\n");
#elif defined(OS)
  printf("OS=%s", OS);
#else 
  printf("OS=Unknown\n");
#endif
}
