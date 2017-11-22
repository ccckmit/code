#include <stdio.h>

int main(void)
{ 
   char s3[7] = "hello!";
   char *s1 = "hello!";
   char s2[] = "yello!";
   char s4[] = {'x', 'e', 'l', 'l', 'o', '!'};
   char s5[] = "abcdefghij";
   printf("s1=%s\n", s1);
   printf("s2=%s\n", s2);
   printf("s3=%s\n", s3);
   printf("s4=%s\n", s4);
   
   char *h = "Hello! §A¦n!";
   printf("%s\n", h);
   int i;
   for (i=0; i<strlen(h); i++) {
     printf("%c\n", h[i]);
   }
   for (i=0; i<strlen(h); ) {
     if (h[i] < 0)
	 {
	   printf("%c%c\n", h[i], h[i+1]);
	   i+=2;
	 }
	 else
	 {
       printf("%c\n", h[i]);
	   i++;
	 }
   }
   
//   char *s4;
//   s4 = 0;
//   scanf("%s", s4);
   return 0; 	
}
