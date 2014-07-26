#include<stdio.h>
#define PAGELEN 24
#define LINLEN 512

void do_more(FILE *);
int see_more();

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
//	FILE * fp_tty;
//	fp_tty = fopen("/dev/tty","r");
//	if(fp_tty == NULL)
//		exit(1);

	int reply;
	while(fgets(line,LINLEN,fp)){
		if(num_of_lines == PAGELEN){
		reply = see_more();
		if(reply == 0)
			break;
		num_of_lines -=reply;

		}
	if(fputs(line,stdout) == EOF)
		exit(1);
		num_of_lines++;

	}

}

int see_more()
{


/*
 * getc fgetc 函数的区别和联系，getc有可能被实现成是一个宏。
 *
 */
	int c;
	printf("\033[7m more?\033[m");
	while((c = getchar()) != EOF)
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
