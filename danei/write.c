#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	char buf[BUFSIZ];
/*
 * 往0,1,2写数据
	write(0,"Hello World\n",12);
	write(1,"Hello World\n",12);
	write(2,"Hello World\n",12);
*/


/*
 * 从0,1读取数据，并判定输入情况
 */

	read(1,buf,BUFSIZ);
	switch(*buf){
		case 'q':
			exit(1);
			break;
		case 'w':
			printf("Hello World");
			break;
		default:
			printf("Usage:%s w|q",argv[0]);
			break;
	}
	printf("%s",buf);
	return 0;
}


