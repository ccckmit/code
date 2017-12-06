#include <stdio.h>
#include <locale.h> 

int main() {
  char *locale_return = setlocale(LC_CTYPE, ""); 
  printf("locale_return=%s\n", locale_return);
  locale_return = setlocale(LC_CTYPE, "zh_TW.Big5"); 
  printf("locale_return=%s\n", locale_return);  
  char *str = "Hello World ! §A¦n";
  wchar_t wstr[100];
  char bstr[100];
  mbstowcs(wstr, str);
  wcstombs(bstr, wstr); 
  printf("str=%s\n", str);
  printf("bstr=%s\n", bstr);
  return 1;
}
