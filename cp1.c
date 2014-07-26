#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *,char *);
int exists(char *);
int main(int argc,char *argv[])
{
	int in_fd,out_fd,n_chars;
	char answer[10];
	char c;
	//设置buf
	char buf[BUFFERSIZE];
	struct stat filebuf;
	char *filename=NULL;
	//判断参数
	if(argc != 4){
		fprintf(stderr,"Usage: %s source destination\n",*argv);
		exit(1);
	}
	//判断-i选项
	if(strcmp(argv[1],"-i") != 0){
		fprintf(stderr,"the cp only use -i\n");
		exit(1);
	}
	//判断源文件和目标文件是否相等
	if(strcmp(argv[2],argv[3]) == 0)
	{
		fprintf(stderr,"No Copy Source File equal Dest File\n");
		exit(1);
	}
	//测试文件是否可以访问
	if(access(argv[3],F_OK) == 0){
		//询问文件是否可以覆盖
		printf("Can you ovver the file (y/n):");
		scanf("%9s",&answer);
		while((c = getchar()) != EOF && c != '\n');
	}
	//判断用户的输入
	if(*answer != 'y' && *answer != 'Y'){
		fprintf(stderr,"the dst file exists,don't over\n");
		exit(1);
	}
	//判断目标是否是目录
	stat(argv[3],&filebuf);
	if(S_ISDIR(filebuf.st_mode))
		if((filename = (char *)malloc(strlen(argv[2])+strlen(argv[3])+3)) == NULL)
			perror("Malloc erro:");
		else{
			if(argv[3][strlen(argv[3])] == '/'){
				strcpy(filename,argv[3]);
				strcat(filename,argv[2]);
			}else{
				strcpy(filename,argv[3]);
				strcat(filename,"/");
				strcat(filename,argv[2]);
			}


		    }
		
	else
		filename = argv[3];
	
	printf("%s\n",filename);
	//读取文件内容
	if((in_fd = open(argv[2],O_RDONLY)) == -1)
		oops("Cannot open",argv[2]);
	if((out_fd = open(filename,O_WRONLY|O_CREAT,COPYMODE)) == -1)
		oops("Cannot create",filename);
	//开始读取
	while((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0)
		if(write(out_fd,buf,n_chars) != n_chars)
		oops("Write error to",filename);
	//判断最后是否写入
	if(n_chars == -1)
		oops("Read error from,argv[1]","");
	//关闭文件
	if(close(in_fd) == -1||close(out_fd) == -1)
		oops("Error closing files","");
	free(filename);
}

void oops(char *s1,char *s2)
{
	fprintf(stderr,"Error:%s ",s1);
	perror(s2);
	exit(1);
}


int exists(char *filename)
{
	return access(filename,F_OK);
		
}
