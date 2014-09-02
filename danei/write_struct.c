#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
struct stu{
		int no;
		float score;
		char name[20];
};
void save(int fd,struct stu *student);
void input(struct stu *student);
int openfile(char *filename);


int main()
{
	int fd;
	char *filename="test.txt";
	struct stu student;
	fd = openfile(filename);
	while(1){
		input(&student);
		save(fd,&student);
		if(iscontinue() == 0)break;
		
	}
	close(fd);
	
	
}


void input(struct stu *student)
{
	bzero(student,sizeof(struct stu));
	printf("Please input you ID:");
	scanf("%d",&student->no);
	printf("\nPlease input you score:");
	scanf("%f",&student->score);
	printf("\nPlease input you name:");
	scanf("%s",student->name);
}


int openfile(char *filename)
{
	int fd;
	fd = open(filename,O_RDWR|O_CREAT|O_EXCL|O_APPEND,0666);
	if(fd == -1)
	{
		fd = open(filename,O_RDWR|O_APPEND);
		return fd;
	}
}

void save(int fd,struct stu *student)
{	write(fd,student,sizeof(struct stu));
}

int iscontinue()
{
	char data;
	printf("continue input:(y/n)");
	getc(stdin);
	data = getc(stdin);
	if(data == 'y' || data == 'Y')
		return 1;
	else
		return 0;
		
	
}
