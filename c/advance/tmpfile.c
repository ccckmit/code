// tmpfile: opens a temporary binary file for read/write operations and returns a pointer to the stream
//Declaration:  FILE *tmpfile(void); 
//Return:       returns a null pointer on failure. 

#include <stdio.h>

int main(void){
  FILE *temp;
  if((temp=tmpfile())==NULL) {
    printf("Cannot open temporary work file.\n");
    exit(1);
  }
}


