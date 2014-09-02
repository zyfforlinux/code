#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
/* 
 * 项目一:
 * 学生成绩管理系统
 * 目的:熟练使用read,write等IO相关的系统调用
 * 功能:
 *  	显示功能菜单
 *  	添加学生信息
 *  	显示指定学生信息(按学号查，姓名查)
 *  	删除学生信息
 *  	统计学生的平均成绩
 *  	格式化输出学生全部信息
 *
 */


/*
 *学生信息的结构体
 */
struct stu{
	char username[100]; //学生的姓名
	long int id;  	//学生的id
	float score;	//学生的分数
	short flag;	//标志信息是否在文件中存储
	
};

/* 学生信息保存的位置 */
char *filename="stu.dat";
int OpenFile();
int Save(struct stu *student,int fd);
void Input(struct stu *student);
int DelStu(int id,int fd);
void FindStu(int id,int fd);
float AvageScore(int fd);
void PrintStu(int fd);
void ShowMenu();
void MainLoop();

/*
 *打开指定文件，文件不存在则创建文件，文件存在则以追加形式打开。
 *
 */
int OpenFile()
{
	int fd;
	fd = open(filename,O_RDWR|O_CREAT|O_EXCL,0666);
	if(fd == -1)
	{
		fd = open(filename,O_RDWR|O_APPEND);
	}
	return fd;
}

/*
 *保存学生信息 ok
 */
int Save(struct stu *student,int fd)
{
	int n;
	n = write(fd,student,sizeof(struct stu));
	if(n<0)
		return 1;
	else
		return 0;
}


/*
 *录入用户输入的信息 ok 后期加入标准字段，标志其是否在文件中
 */

void Input(struct stu *student)
{
	printf("please input student ID:");
	scanf("%ld",&student->id);
	printf("\nplease input student username:");
	scanf("%s",student->username);
	printf("\nplease input student score:");
	scanf("%f",&student->score);
	student->flag=1;
}

/*删除学生信息 */

int DelStu(int id,int fd)
{
	lseek(fd,0,SEEK_SET);
	struct stu *temp;
	int n,i;
	struct stat st;
	fstat(fd,&st); //获取文件属性信息
	int size = st.st_size;
	int count = size/sizeof(struct stu);
	temp = mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	for(i=0;i<count;i++){
		if(temp[i].id == id)
			temp[i].flag=0;
	}
	munmap(temp,size);
/*
	while(1){
		n = read(fd,&temp,sizeof(struct stu));
		if(n <= 0)
			break;
		if(temp.id == id){
			temp.flag=0; //设置删除标志
			lseek(fd,-size,SEEK_CUR);
			write(fd,&temp,size);
			break;
		}
			
	}
*/
}

/* 查询学生信息 */
void FindStu(int id,int fd)
{
	struct stu temp;
	int n=0;
	/* 重置当前文件指针的位置 */
	lseek(fd,0,SEEK_SET);
	while(1){
		n = read(fd,&temp,sizeof(struct stu));
		if(n <= 0)
			break;
		if(temp.id == id && temp.flag == 1){
			printf("the id is %d\n",temp.id);		
			printf("the username is %s\n",temp.username);		
			printf("the score is %f\n",temp.score);		
			break;
		}
	}
	
}

/* 统计学生的平均成绩 */
float AvageScore(int fd)
{
	float score=0;
	int count=0;
	int n;
	struct stu temp;
	bzero(&temp,sizeof(struct stu));
	lseek(fd,0,SEEK_SET);
	while(1){
		n = read(fd,&temp,sizeof(struct stu));
		if(n<=0)
			break;
		if(temp.flag == 1){
			score += temp.score;
			count++;
		}
	}
	return score/(1.0*count);
}

/* 打印学生信息 */
void PrintStu(int fd)
{
	struct stu temp;
	int n;
	lseek(fd,0,SEEK_SET);
	while(1){
		n = read(fd,&temp,sizeof(struct stu));
		if(n<=0)
			break;
		if(temp.flag == 1)
		printf("%s\t%d\t%f\n",temp.username,temp.id,temp.score,temp.flag);
	}
}


void MainLoop(int fd)
{
	char choose;
	char ch;
	int id;
	struct stu *temp;
	temp = (struct stu *)malloc(sizeof(struct stu));
//	while(choose != '9'){
//	choose = ShowMenu();
	ShowMenu();
	while((ch = getc(stdin)) != EOF && ch != '\n'){
	switch(ch){
		case '1':
				Input(temp);
				Save(temp,fd);
				break;
		case '2':
				printf("please input student id:");
				scanf("%d",&id);
				FindStu(id,fd);
			//	printf("the id is %d stu info\n",id);
			//	printf("the username is %s\n:",temp->username);
			//	printf("the score is %f\n:",temp->score);
				break;
		case '3':
				printf("please input student id:");
				scanf("%d",&id);
				DelStu(id,fd);
				break;
		case '4':
				printf("the student avage score is %f",AvageScore(fd));
				break;
				
		case '5':
				PrintStu(fd);
				break;
		default:
				printf("请输入1,2,3,4,5进行对应的功能");
				break;
	}
	getc(stdin); //获取多余的回车字符
	ShowMenu();
	}

}


void ShowMenu()
{
	char ch;
	printf("+++++++++++++++++++++++++++++++++++++\n");
	printf("1.添加学生信息\n");
	printf("2.查询学生信息\n");
	printf("3.删除学生信息\n");
	printf("4.查看学生的平均成绩\n");
	printf("5.输出全部学生信息\n");
	printf("+++++++++++++++++++++++++++++++++++++\n");
	printf("请输入您的选择(1\\2\\3\\4\\5)");
//	while((ch = getc(stdin)) != EOF && ch != '\n');
//	printf("%c\n",ch);
//	return ch;
}

int main()
{
	int fd = OpenFile();
       	MainLoop(fd);
}
