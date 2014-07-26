#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
//	int fd = open("/dev/tty","r");
	printf("%s",getlogin());
//	close(fd);
}
