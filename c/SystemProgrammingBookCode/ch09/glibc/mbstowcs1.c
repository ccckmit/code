#include <stdio.h>				
#include <stdlib.h>				
#include <string.h>				
#include <locale.h>				
						
int main(void)					
{						
    char mbs[]="�n���n GNU/Linux ����ơA�������� i18n";
    char buffer[10];
    wchar_t wcs[100], wc;
    int n, cnt;

    setlocale(LC_CTYPE, "");
    mbstowcs(wcs, mbs, 99);

    /* pick n-th wide character */
    n=14;
    wc = wcs[n];
    cnt = wctomb(buffer, wc);
    buffer[cnt] = '\0';

    printf("%d th char in wcs =\"%s\"\n", n+1, buffer);	
    printf("%d th char in mbs =\"%c\"\n", n+1, mbs[n]);	
    return 0;
}
