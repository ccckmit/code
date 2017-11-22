//Declaration:  size_t mbstowcs(wchar_t *out, const char *in, size_t size); 
//Return:       returns the number of multibyte characters converted or -1 on error. 

#include <stdlib.h>
#include <stdio.h>

int main(void){

  char *mb = "asdfadsf";
  char str[1000];

  mbstowcs(str, mb, 4);
 
  printf("%ls",str);

}