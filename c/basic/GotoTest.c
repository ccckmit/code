#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int sum=0;
	int i=0;
loop:	if (i>10) goto end;
	sum = sum + i;
	i++;
	goto loop;
end :
	printf("sum=%d", sum);
	return 1;
}
