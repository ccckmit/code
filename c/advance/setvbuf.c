//Header file:     #include <stdio.h>  
//Declaration:     int setvbuf(FILE *stream, char *buf, int mode, size_t size); 
//Return:          returns zero on success, nonzero on failure. 


// Possible values of mode are _IOFBF, _IONBF, and _IOLBF.
//_IOFBF: full buffering.
//_IOLBF: line buffered.
//_IONBF: no buffering.
  
#include <stdio.h>

int main ()
{
  FILE *fp;

  fp=fopen ("myfile.txt","w");

  setvbuf ( fp , NULL , _IOFBF , 1024 );

  // File operations here

  fclose (fp);

  return 0;
}


