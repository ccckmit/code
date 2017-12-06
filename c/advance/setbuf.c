  
#include <stdio.h>

int main ()
{
  char buffer[BUFSIZ];
  FILE *fp1, *fp2;

  fp1=fopen ("test.txt","w");
  fp2=fopen ("test2.txt","a");

  setbuf ( fp1 , buffer );
  fputs ("This is sent to a buffered stream",fp1);
  fflush (fp1);

  setbuf ( fp2 , NULL );
  fputs ("This is sent to an unbuffered stream",fp2);

  //Set buf to null to turn off buffering.
  //The buffer must be BUFSIZ characters long.
  //BUFSIZ is defined in <stdio.h>.  


  fclose (fp1);
  fclose (fp2);

  return 0;

}