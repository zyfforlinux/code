#include<curses.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
/*项目二:
 * 基于curses的学生信息录入系统
 * 	目的:熟练使用curses的一些函数的使用
 * 	功能:
 * 		用户输入账号和密码
 * 		对错误输入进行提示
 * 		判断用户账号密码
 * 		登录成功进行页面跳转
 * 		彩色显示
 * 		学生信息录入
 * 		学生信息显示
 *
 */

#define USERNAME "zhang"
#define PASS "zyf"
#define FILENAME "stu.data"
struct stu{
	char username[20];
	float score;
	long int id;
};


void init();
void end();
void layout();
void Input();
void welcome();
void clearscr();
void save(int fd,struct stu *student);
int openfile(char *filename);
void Input(int fd,struct stu *student);
void StdInput(int fd,struct stu *student);


int main()
{
	struct stu *student;
	int fd;
	student = (struct stu*)malloc(sizeof(struct stu));
	fd = openfile(FILENAME);
	init();
	layout();
	Input(fd,student);
	end();
}

void init()
{
	initscr(); //初始化
	if(has_colors() == TRUE)
		start_color();
	else
		exit(1);
	/* 定义颜色对 */
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_RED,COLOR_WHITE);
	init_pair(3,COLOR_BLUE,COLOR_WHITE);
	init_pair(4,COLOR_GREEN,COLOR_WHITE);
	init_pair(5,COLOR_YELLOW,COLOR_WHITE);
	/* 设置屏幕背景颜色 */
	signal(SIGINT,end);
	signal(SIGQUIT,end);
//	bkgd(2);
}


void end()
{
	endwin();
	exit(1);
}

void layout()
{

	box(stdscr,'+','+'); //画边界
	/* 基本布局 */
	attron(A_BOLD|COLOR_PAIR(2));
	mvaddstr((LINES-6)/2,(COLS-6)/2,"username:[      ]");
	mvaddstr((LINES-6)/2+2,(COLS-6)/2,"password:[      ]");
	attroff(A_BOLD|COLOR_PAIR(2));
}


void Input(int fd,struct stu *student)
{
	char username[5];
	char pass[3];
	mvgetnstr((LINES-6)/2,(COLS-6)/2+11,username,5);
	mvgetnstr((LINES-6)/2+2,(COLS-6)/2+11,pass,3);
	refresh();
	if((strcmp(username,USERNAME) == 0) && (strcmp(pass,PASS) == 0)){
		clearscr();
		StdInput(fd,student);
	}
	else{
		mvprintw((LINES-6)/2+6,(COLS-6)/2,"%s","username/password error");
		layout();
		Input(fd,student);
	}	
		
		
}


/* 学生信息输入 */
void StdInput(int fd,struct stu *student)
{
	char score[20];
	char id[20];
	attron(A_BOLD|COLOR_PAIR(3));
	mvprintw((LINES-6)/2-12,(COLS-6)/2+11+5,"%s","Welcome to Student Management System");
	attroff(A_BOLD|COLOR_PAIR(3));

	
	attron(A_BOLD|COLOR_PAIR(2));
	mvaddstr((LINES-6)/2-10,(COLS-6)/2,"username:[                         ]");
	mvaddstr((LINES-6)/2-8,(COLS-6)/2,"id:      [                         ]");
	mvaddstr((LINES-6)/2-6,(COLS-6)/2,"score:   [                         ]");
	attroff(A_BOLD|COLOR_PAIR(2));

	mvgetnstr((LINES-6)/2-10,(COLS-6)/2+11,student->username,20);
	mvgetnstr((LINES-6)/2-8,(COLS-6)/2+11,id,20);
	mvgetnstr((LINES-6)/2-6,(COLS-6)/2+11,score,3);
	refresh();
	student->id = atol(id);
	student->score = atof(score);
	save(fd,student);
	clearscr();
	StdInput(fd,student);
	
}

/* 清屏 */
void clearscr()
{
	erase();
}

/* 打开文件 */
int openfile(char *filename)
{
	int fd;
	fd = open(filename,O_RDWR|O_CREAT|O_EXCL,0666);
	if(fd == -1)
		fd = open(filename,O_RDWR|O_APPEND);
	return fd;
	
}

/* 学生信息保存 */
void save(int fd,struct stu *student)
{
	int n;
	if((n=write(fd,&student,sizeof(struct stu))<=0)){
		perror("write error:");
		exit(2);
	}
}

