#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
int main()
{
	DIR *dir;
	struct dirent *ptr;
	int i;
	dir=opendir("/bin/");
	while((ptr=readdir(dir))!=NULL)
	{
		printf("%s\n",ptr->d_name);
	}
	closedir(dir);
	return 1;
}