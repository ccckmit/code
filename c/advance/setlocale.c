//Declaration:  char *setlocale(int type, const char *locale); 
 


//type must be one of the following macros (defined in <locale.h>): 

//LC_ALL: refers to all localization categories.
//LC_COLLATE: affects the operation of the strcoll() function.
//LC_CTYPE: alters the way the character functions work.
//LC_MONETARY: determines the monetary format.
//LC_NUMERIC: changes the decimal-point character for formatted input/output functions.
//LC_TIME: determines the behavior of the strftime() function.

  #include <locale.h>
  #include <stdio.h>

  int main(void)
  {
    printf(setlocale(LC_ALL, ""));

    return 0;
  }

         
