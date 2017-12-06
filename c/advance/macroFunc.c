#include <stdio.h>

#if !defined( HELLO_MESSAGE )
   # error "You have forgotten to define the header file name."
#endif

char *format = "%s",
     *hello = HELLO_MESSAGE;

int main() {

  printf ( format, hello );

}
