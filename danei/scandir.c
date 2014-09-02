#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>


int main()
{
	struct dirent **d;
	int r,i;
	r = scandir("/root",&d,0,0);
	printf("子目录的个数:%d\n",r);
	for(i = 0;i<r;i++)
	{
		printf("%s\n",d[i]->d_name);
	}
	while(*d)
	{
		printf("%s\n",(*d)->d_name);
		d++;
	}
}

