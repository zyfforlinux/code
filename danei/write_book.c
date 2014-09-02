#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

struct book{
	char bookname[20];
	char publish[100];
	float price;
	int num;
	char author[100];
};

int openfile(char *filename);
void input(struct book *bookinfo);
int  save(int fd,struct book *bookinfo);
int main()
{
	int fd;
	char *filename="book.dat";
	struct book bookinfo;
	bzero(&bookinfo,sizeof(struct book));
	fd = openfile(filename);
	input(&bookinfo);
	save(fd,&bookinfo);
	close(fd);
}



int openfile(char *filename)
{
	int fd;
	fd = open(filename,O_RDWR|O_CREAT|O_EXCL,0777);
	if(fd == -1)
	{
		fd = open(filename,O_RDWR|O_APPEND);
	}
	return fd;
}


void input(struct book *bookinfo)
{
	printf("please input book name:");
	scanf("%s",bookinfo->bookname);
	printf("\nplease input book publish:");
	scanf("%s",bookinfo->publish);
	printf("\nplease input book price:");
	scanf("%f",&bookinfo->price);
	printf("\nplease input book num:");
	scanf("%d",&bookinfo->num);
	printf("\nplease input book author:");
	scanf("%s",bookinfo->author);
}


int  save(int fd,struct book *bookinfo)
{	
	int n;
	n = write(fd,bookinfo,sizeof(struct book));
	if(n<=0){
		perror("write data:");
		exit(1);
	}
	
}
