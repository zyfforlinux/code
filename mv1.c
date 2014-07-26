#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

void do_dir(char *path1,char *path2);
void do_file(char *path1,char *path2);


int main(int argc,char *argv[])
{
	struct stat fileinfo;
	if(argc != 3){
		fprintf(stderr,"mv:Usage source dst");
		exit(1);
	}
	stat(argv[1],&fileinfo);
	if((access(argv[1],F_OK)==0) && S_ISREG(fileinfo.st_mode)){
		stat(argv[2],&fileinfo);
		if(S_ISDIR(fileinfo.st_mode))
			do_dir(argv[1],argv[2]);
		else
			do_file(argv[1],argv[2]);
	}	
	else{
		fprintf(stderr,"source not common file");
		exit(1);
	}		
}

void do_file(char *path1,char *path2)
{
	if(access(path2,F_OK) == 0){
		fprintf(stderr,"dst file have exists");
		exit(1);
	}
	if(rename(path1,path2) == -1)
		perror("rename fail:");
}

void do_dir(char *path1,char *path2)
{
	char dst[strlen(path1)+strlen(path2)+3];
	if(access(path2,F_OK) != 0){
		fprintf(stderr,"dst file not exists");
		exit(1);
	}
	strcpy(dst,path2);
	if(path2[strlen(path2)-1] != '/')
		strcat(dst,"/");
	strcat(dst,path1);
	rename(path1,dst);
	
}
