#include <stdio.h>
#include <locale.h> 

int main() {
  char *locale_return = setlocale(LC_ALL, ""); 
  printf("locale_return=%s\n", locale_return);
  locale_return = setlocale(LC_CTYPE, "zh_TW.Big5"); 
  printf("locale_return=%s\n", locale_return);  
  char str1[] = "Hello! §A¦n", str2[100];
  wchar_t wstr[100];
  int wlen=mbstowcs(wstr, str1);
  int clen=wcstombs(str2, wstr);
  printf("str1=%s wstr1=%ls %wlen=%d str2=%s clen=%d\n", str1, wstr, wlen, str2, clen);
  int i;
  for (i=0; i<wcslen(wstr); i++)
    printf("%#.4x ", wstr[i]);
  printf("\n");
  return 1;
}
