#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	time_t tm = time((time_t *)0);
	printf("%s\n",ctime(&tm));
}
