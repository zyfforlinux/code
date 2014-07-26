#include<unistd.h>
#include<stdio.h>
#include<time.h>
int main(int argc,char *argv[])
{
	time_t current;
	printf("%d\n",time((time_t)0));
}
