#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	struct stat infobuf;
	if(stat("/etc/passwd",&infobuf) == -1)
		perror("/etc/passwd");
	else
		printf("The size of /etc/passwd is %d\n",infobuf.st_size);
}

