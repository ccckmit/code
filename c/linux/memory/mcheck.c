#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>

int main() {
  char *buf = malloc(1000);
  free(buf);
  mcheck(0);
}
