#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>

char *mode_digit(char *);
char mode[10]="rwxr-x--x";


int main()
{
	char *name=NULL;
	name = mode_digit(mode);
	printf("%s\n",name);
	free(name);
	
}


char *mode_digit(char *mode)
{
	
	char *st_mode=NULL;
	st_mode = (char*)malloc(17);
	st_mode[16]='\0';
	int i=0;
	int count=7;
	for(i=0;i<7;i++)st_mode[i]='0';
	while(*mode){
		if(*mode != '-'){
			st_mode[count]='1';
			count++;
		}else{
			st_mode[count]='0';
			count++;
		}
		mode++;	
	}
	return st_mode;
}

