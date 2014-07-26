#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
void do_ls(char []);

int main(int argc,char *argv[])
{
	if(argc == 1)
		do_ls(".");
	else
/*
 *依次遍历每一个参数，打印目录下的所有文件
 */
		while(--argc){
			printf("%s:\n",*++argv);
			do_ls(*argv);
		}
}

void do_ls(char dirname[])
{
/*
 *定义一个目录流,和目录流结构体保存读到的结果。
 */
	DIR *dir_ptr;
	struct dirent *direntp;
	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr,"ls1:cannot open %s\n",dirname);
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL)
	//打印结果
			printf("%s\n",direntp->d_name);
	//关闭目录流
		closedir(dir_ptr);
	}
}
