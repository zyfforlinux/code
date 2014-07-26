#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	struct stat fileinfo;
	stat(*++argv,&fileinfo);
	if(fileinfo.st_mode & S_IRUSR)
		printf("用户可读");
	else
		printf("用户不可读");
}
