static inline char * strcpy(char * dest,const char *src)
{
  int d0, d1, d2;
  asm(
    "1:\tlodsb\n\t"
    "stosb\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b"
    :"=&S" (d0), "=&D" (d1), "=&a" (d2)
    :"0" (src),"1" (dest) 
    :"memory");
  return dest;
}

int main(void)
{
  char s[] = "abc", d[100];
  strcpy(d, s);
  printf("d=%s s=%s\n", d, s);
}
