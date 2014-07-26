#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST 
void show_info(struct utmp *);
void showtime(long);
char * get_current_line();
int main()
{
///	printf("%s",get_current_line);
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	char *myline = NULL;
	myline = get_current_line();
	if((utmpfd = open(UTMP_FILE,O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(read(utmpfd,&current_record,reclen) == reclen)
	if(myline == NULL || strcmp(current_record.ut_line,myline) == 0)
		show_info(&current_record);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)
		return;
//	if(strcmp(utbufp->ut_line,get_current_line) != 0)
//		return;
	printf("%-8.8s",utbufp->ut_name);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	printf(" ");
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
	printf("% 12.12s",cp+4);
}

char * get_current_line()
{
	char *line;
	//line指向当前用户的终端设备名称
	if(line = ttyname(0))
	//比较前5个字符看看是不是/dev/开头,如果是将line后移五个即使终端设备名
		if(strncmp(line,"/dev/",5) == 0)
			line += 5;
	//返回终端设备名
	return line; 
}
