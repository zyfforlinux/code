#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
char buf[10]="zhangyife";
int a = 100;
int main()
{
	int fd;
	char filename[20];
	int data=8888;
	char bufs[10];
	int n=0;
	sprintf(filename,"/proc/%d/mem",getpid());
	fd = open(filename,O_RDWR);
	if(fd == -1)perror("open file:"),exit(1);
	while((n=read(fd,bufs,10))>0)
	{
		printf("%s\n",buf);
	}
//	pread(fd,&data,4,(int)&a);
//	printf("%d\n",data);
}
