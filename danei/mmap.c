#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
/*
 * 算法过程
 * 1.打开文件
 * 2.获得文件的记录大小
 * 3.开始映射
 * 4.获得用户输入的数据
 * 5.存入数据
 */


struct book{
        char bookname[20];
        char publish[100];
        float price;
        int num;
        char author[100];
};

int main()
{
	int fd;
	struct book *s;
	struct stat st;
	int size;
	int count;
	int i;
	fd = open("book.dat",O_RDWR|O_CREAT|O_EXCL,0666);
	if(fd == -1){
		fd = open("book.dat",O_RDWR|O_APPEND);
	}
	fstat(fd,&st);
	size = st.st_size;
	count = size/sizeof(struct book);
	ftruncate(fd,size+sizeof(struct book));
	s = mmap(0,size+sizeof(struct book),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("please input book name:");
	scanf("%s",s[count].bookname);
	printf("please input publish book");
	scanf("%s",s[count].publish);
	printf("please input price:");
	scanf("%f",&s[count].price);
	printf("please inpyt num:");
	scanf("%d",&s[count].num);
	printf("please input author:");
	scanf("%s",s[count].author);
	for(i=0;i<=count;i++)
	{
	//	s[i].num--;
		printf("%s\t%s\t%f\t%d\t%s",s[i].bookname,s[i].publish,s[i].price,s[i].num,s[i].author);
		printf("\n");
	}
	munmap(s,sizeof(struct book)+size);
	close(fd);
	
}


