#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <string.h>

#define MAXSIZE 100
void Createdir(char *);
int main(int argc,char *argv[])
{
	if(argc <= 1){
	
		printf("mkdir:Usage:dirstr\n");
		exit(1);
	}
	while(--argc){
		argv++;
		Createdir(*argv);
	}
}

void Createdir(char *path)
{
	char data[MAXSIZE];
	if((strcmp(path,".") == 0) || (strcmp(path,"/")==0))
                return;
	if(access(path,F_OK) == 0)
		return;
	else{
		strcpy(data,path);
		dirname(path);
		Createdir(path);
	}
	if(mkdir(data,777) == -1){
		perror("mkdir error");
		exit(1);
	}
	return;
}
