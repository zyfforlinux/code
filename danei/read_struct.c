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
void finddata(int fd,int no);
void show(int fd,struct stu *student);
int openfile(char *filename);
int main()
{
	int fd;
	int no;
	struct stu student;
	char *filename = "test.txt";
	fd = openfile(filename);
	show(fd,&student);
	printf("please input find no:");
	scanf("%d",&no);
	finddata(fd,no);
	
}




int openfile(char *filename)
{
	int fd;
	fd = open(filename,O_RDONLY);
	if(fd == -1){
		perror("open file:");
		exit(2);
	}
	return fd;
				
}

void show(int fd,struct stu *student)
{
	int n;
	while( (n = read(fd,student,sizeof(struct stu))) >0){
		printf("no:%d\t",student->no);
		printf("score:%f\t",student->score);
		printf("name:%s\n",student->name);
	}	
}

void finddata(int fd,int no)
{
	struct stu temp;
	int n;
	bzero(&temp,sizeof(struct stu));
	lseek(fd,0,SEEK_SET);
	while( (n = read(fd,&temp,sizeof(struct stu))) >0){
		if(temp.no == no){
			printf("find data");
			printf("no:%d\t",temp.no);
			printf("score:%f\t",temp.score);
			printf("name:%s\n",temp.name);
		}
		return;
        }
}
