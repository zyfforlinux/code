#include<ncurses.h>

int main()
{
	initscr();
	//border(0,0,0,0,0,0,0,0);
//	box(stdscr,0,0);
//	mvhline(2,10,'=',20);
//	mvvline(2,10,'*',20);
//	addch(ACS_LLCORNER);
	if(has_colors() == TRUE){
		start_color();
		init_pair(1,COLOR_RED,COLOR_WHITE);
		init_pair(2,COLOR_BLUE,COLOR_WHITE);
		init_pair(3,COLOR_YELLOW,COLOR_WHITE);
		init_pair(4,COLOR_BLACK,COLOR_WHITE);
		bkgd(COLOR_PAIR(4));
	}
	else
		return 0;

	mvaddch(2,10,'z'|COLOR_PAIR(1));
	attron(COLOR_PAIR(3));
	mvaddstr(3,11,"Hello 你好 ");
	attroff(COLOR_PAIR(3));
	getch();
	endwin();
	return 0;
}
