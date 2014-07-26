/*
 *pwd1.c version1 from unix program book
 *dest:Show current Path
 *
 *
 */

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t,char *,int);

int main()
{
	printpathto(get_inode("."));
	putchar('\n');
	return 0;
}

/* 
 *recursive print path.
 *
 */
void printpathto(ino_t this_inode)
{
	ino_t my_inode;
	char its_name[BUFSIZ];//BUFSIZ有定义了
//	printf("%d\n",BUFSIZ);//打印一下看看
	if(get_inode("..")!=this_inode)
	{
		chdir("..");//到达上一级目录
		inum_to_name(this_inode,its_name,BUFSIZ);//获取当前目录的名字，放在its_name中
		my_inode = get_inode(".");//获取当前目录的inode节点号
		printpathto(my_inode);//递归
		printf("/%s",its_name);//递归到顶层开始输出
	}
	
}

/*
 *通过inode节点号，查找对应的文件名，并存放再its_name中。
 *
 *
 */
void inum_to_name(ino_t inode_to_find,char *namebuf,int buflen)
{
	DIR *dir_ptr;
	struct dirent *direntp;
	dir_ptr = opendir(".");
	if(dir_ptr == NULL){
		perror(".");
		exit(1);
	}
/*
 *搜索这个目录下的所有文件，找到inode号等于inode_to_find的文件。
 *
 */	
	while((direntp = readdir(dir_ptr)) != NULL)
		if(direntp->d_ino == inode_to_find)
		{
			strncpy(namebuf,direntp->d_name,buflen);
			namebuf[buflen-1] = '\0';
			closedir(dir_ptr);
			return;
		}

	fprintf(stderr,"error looking for unum%d\n",inode_to_find);
	exit(1);

}

/*
 *
 *返回文件的inode节点号
 *
 */
ino_t get_inode(char *fname)
{
	struct stat info;
	if(stat(fname,&info) == -1){
		fprintf(stderr,"Cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}
