#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

struct book{
        char bookname[20];
        char publish[100];
        float price;
        int num;
        char author[100];
};

int main()
{
	int fd;
	int size;
	char bookname[20];
	char publish[100];
	size = sizeof(struct book);
	fd = open("book.dat",O_RDWR);
	lseek(fd,500,SEEK_SET);

//	read(fd,publish,sizeof(publish));
	write(fd,"sss",3);	
	printf("%s\n",publish);
//	lseek(fd,)
	
}
