#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define PAGELEN 24
#define LINLEN 512

void do_more(FILE *);
int see_more(FILE *,FILE *);

int main(int argc,char *argv[])
{
	FILE *fp;
	if(argc == 1)
		do_more(stdin);
	else
//遍历读取每一个文件
		while(--argc)
		if((fp = fopen(*++argv,"r")) != NULL)
		{
			do_more(fp);
			fclose(fp);
		}
		else
			exit(1);
	return 0;
}

void do_more(FILE *fp)
/*
 *read PAGELEN lines
 *
 */
{
	char line[LINLEN];
	int num_of_lines = 0;
//	int see_more(),reply;
	FILE * fp_tty;
	fp_tty = fopen("/dev/tty","r");
	if(fp_tty == NULL)
		exit(1);

	int reply;
	while(fgets(line,LINLEN,fp)){
		if(num_of_lines == PAGELEN){
		reply = see_more(fp_tty,fp);
		if(reply == 0)
			break;
		num_of_lines -=reply;

		}
	if(fputs(line,stdout) == EOF)
		exit(1);
		num_of_lines++;

	}

}

int see_more(FILE *cmd,FILE *openfile)
{


/*
 * getc fgetc 函数的区别和联系，getc有可能被实现成是一个宏。
 *
 */
	int c,fd;
	struct stat fileinfo;
	printf("\033[7m more?\033[m");
//	int bytes = lseek(openfile,0,SEEK_CUR);
	if((fd = fileno(openfile)) == -1)
	{
		perror("get fd error:");
		exit(1);
	}
	int bytes = lseek(fd,0,SEEK_CUR);
	if(fstat(fd,&fileinfo) == -1)
	{
		perror("get file info error");
		exit(1);
	}
//	printf("%d\n",bytes);
//	printf("%d\n",fileinfo.st_size);
	int  b = ((bytes*1.0)/fileinfo.st_size)*100;
	printf("\033[6m (%%%d)\033[m",b);
//	printf("(%%%d)",float(bytes)/float(fileinfo.st_size)*100.0);
	while((c = getc(cmd)) != EOF)
	{
	  if(c == 'q')
		return 0;
	  if(c == ' ')
		return PAGELEN;
	  if(c == '\n')
		return 1;
	}
	return 0;
}
