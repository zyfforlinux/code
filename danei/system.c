#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
	int r;
	printf("%d\n",getpid());
	sleep(10);
	r = system("ls /");
	printf("%d\n",WEXITSTATUS(r));
	printf("%d\n",r>>8&255);
}
