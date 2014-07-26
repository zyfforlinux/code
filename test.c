#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	

	struct stat size;
	int  fd;
//	int fp = open(*++argv,O_RDWR);
	if(argc != 2){
		printf("Usage:%s filepath\n",*argv);
		exit(1);
	}
	FILE *fp = fopen(*++argv,"r");
	while((fd = fileno(fp)) == -1)
	{
		perror("get fd error:");
		exit(1);
	}

//	printf("%s\n",*argv);
//	printf("%d\n",fp);
	if(fstat(fd,&size) == -1)
	{
		perror("stat error: ");
		exit(1);
	}
	printf("%d",size.st_size);
}

