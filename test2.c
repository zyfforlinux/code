#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<utmp.h>
#include<stdlib.h>
#include<time.h>
char * get_current_line();
void show(struct utmp *);
void showtime(long timeval);

int main()
{
	int fd;
	struct utmp utmpdata;
	char * myline=NULL;
	myline = get_current_line();
	int size = sizeof(utmpdata);
	if((fd = open(UTMP_FILE,O_RDONLY)) == -1){
		perror("Open file failue:");
		exit(1);
	}
//	printf("%d",fd);
	while(read(fd,&utmpdata,size) == size){
	//	if(myline == NULL || strcmp(utmpdata.ut_line,myline)==0)
			if(strcmp(utmpdata.ut_user,getlogin()) == 0)
				show(&utmpdata);
	}
	close(fd);
	return 0;
	
		
	
}


void show(struct utmp *data)
{
	if(data->ut_type != USER_PROCESS)
                return;
//	showtime(data->ut_tv.tv_sec);
//	showtime(data->ut_time);
 // 	printf("Hello World");
//	printf("%d\n",data->ut_tv.tv_sec);
	printf("%d\n",data->ut_time);
}

char * get_current_line()
{
        char *line;
        if(line = ttyname(0))
                if(strncmp(line,"/dev/",5) == 0)
                        line += 5;
        return line;
}


void showtime(long timeval)
{
        char *cp;
        cp = ctime(&timeval);
        printf("% 12.12s\n",cp+4);
}


time_t get_current_time()
{
	return time((time_t)0);
}

int get_total_session_time(long timecount)
{
	
}
