#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>

int main()
{
	DIR *d;
	struct dirent *de;
	d = opendir("/root");
	if(d == NULL){
		perror("open dir:");
		exit(1);
	}
	while((de = readdir(d)) != NULL){
		printf("%s\ttype:%d\n",de->d_name,de->d_type);
	}
	closedir(d);
}
