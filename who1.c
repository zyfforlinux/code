#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#define SHOWHOST 
void show_info(struct utmp *,int);
void showtime(long);

int main(int argc,char *argv[])
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	if((utmpfd = open(UTMP_FILE,O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	
	int flag = atoi(argv[1]);
//	printf("%d\n",flag);
	while(read(utmpfd,&current_record,reclen) == reclen)
		show_info(&current_record,flag);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp,int flag)
{
	if(utbufp->ut_type != flag) 
		return;
//	printf("%-8.8s",utbufp->ut_name);
//	printf(" ");
//	printf("%-8.8s",utbufp->ut_line);
//	printf(" ");
	showtime(utbufp->ut_time);
//	printf("%10ld",utbufp->ut_time);
	printf(" ");
#ifdef SHOWHOST
	printf("%s",utbufp->ut_host);
#endif
	printf("\n");
}

void showtime(long timeval)
{
	char *cp;
	cp = ctime(&timeval);
	printf("%s",cp);
	//printf("% 12.12s",cp+4);
}

