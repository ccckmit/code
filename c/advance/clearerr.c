//Declaration:  void clearerr(FILE *stream);
                

  #include <stdio.h>
  #include <stdlib.h>

  int main(int argc, char *argv[]) {
    FILE *in, *out;
    char ch;

    if((in=fopen("inFile.txt", "rb")) == NULL) {
      printf("Cannot open input file.\n");
      exit(1);
    }
    if((out=fopen("outFile.txt", "wb")) == NULL) {
      printf("Cannot open output file.\n");
      exit(1);
    }

    while(!feof(in)) {
      ch = getc(in);
      if(ferror(in)) {
        printf("Read Error");
        clearerr(in);
        break;
      } else {
        if(!feof(in))
          putc(ch, out);
         
        if(ferror(out)) {
          printf("Write Error");
          clearerr(out);
          break;
        }
      }
    }
    fclose(in);
    fclose(out);

    return 0;
  }


    
