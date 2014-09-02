#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
int openfile(char *filename);
void copy(char *sourcefile,char *dstfile);

int main(int argc,char *argv[])
{
	if(argc != 3){
		fprintf(stderr,"Usage%s sourcefile desfile\n",argv[0]);
		exit(1);
	}
	if(access(argv[1],F_OK)){
		fprintf(stderr,"sourcefile %s not exists\n",argv[1]);
		exit(1);
	}
	copy(argv[1],argv[2]);

}


void copy(char *sourcefile,char *dstfile)
{
	int sfd;
	int dfd;
	int n;
	char buf[BUFSIZ];
	sfd = openfile(sourcefile);
	dfd = openfile(dstfile);
	bzero(buf,BUFSIZ);
	while((n = read(sfd,buf,BUFSIZ)) >0)
	{
		write(dfd,buf,n);
	}
}

int openfile(char *filename)
{
	int fd;
	fd = open(filename,O_RDWR|O_CREAT|O_EXCL,0777);
	if(fd == -1)
	{
		fd = open(filename,O_RDWR);
	}
	return fd;
}

