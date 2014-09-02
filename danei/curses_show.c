#include<curses.h>


int main()
{
	initscr();
	box(stdscr,0,0);
	mvaddch(2,10,'A'|A_BOLD|A_UNDERLINE);
	refresh();
	getch();
	endwin();
}
