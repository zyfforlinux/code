#include<curses.h>
#include<stdio.h>


int main()
{
	
}


void init()
{
	initscr();
	noecho();
	keypad(stdscr,TRUE);
}
