#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int main()
{
	int fd;
	char name[20];
	int age;
	float score;
	int r;
	fd = open("write.cc",O_RDONLY);
	if(fd == -1){
		perror("Error Read from file: ");
		exit(1);
	}
	while(1){
		r = read(fd,name,sizeof(name));
		if(r <= 0) break;
		r = read(fd,&age,sizeof(int));
		r = read(fd,&score,sizeof(float));
		printf("%s,\t%4hd,\t%.2f,\t\n",name,age,score);
	}
	close(fd);
}

