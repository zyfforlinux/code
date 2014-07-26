#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <libgen.h>
int main(int argc,char *argv[]) 
{	
	char *data=NULL;
	data = dirname(argv[1]);
	printf("%s\n",data);
	printf("%s\n",argv[1]);
} 
