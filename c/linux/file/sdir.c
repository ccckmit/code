#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
	int sign;
	char pathname[]="/root/sxy/temp";
	sign=mkdir(pathname,O_RDWR);
	if(sign==0)
		printf("create succeed!\n");
	else 
		printf("create succeed!\n");
	sign=rmdir(pathname);
	if(sign==0)
		printf("delete succeed!\n");
	else 
		printf("delete failed!\n");
	return 1;
}
