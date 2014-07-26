#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main(int argc,char *argv[])
{
	char ans[10];	
	char c;
	int retval = 0;
	fprintf(stderr,"cp:Ok to replace %s? ","aa");
	if(scanf("%9s",ans) == 1){
		if(*ans == 'y' || *ans == 'Y')
			retval = 1;
	}
//	while((c = getchar()) != EOF && c != '\n');
	printf("-------%d------",retval);
}
