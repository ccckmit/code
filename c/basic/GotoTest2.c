#include <stdio.h>
#include <stdlib.h>

int main()
{
  int s = sum(10);
  printf("1+..+10=%d\n", s);
}

int sum(n) 
{
	int s=0;
	int i=0;
loop:	if (i>n) goto end;
	s = s + i;
	i++;
	goto loop;
end :
//	printf("sum=%d", sum);
	return s;
}
