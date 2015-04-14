//must compile with -lncurses option to g++

#include <ncurses.h>


int main()
{

	initscr();
	
	char ch = 'X';

	mvaddch(5,10,ch);
	mvaddch(3,4,ch);
	mvaddch(6,7,ch);
	mvaddch(2,4,ch);
	mvaddch(9,9,ch);


	getch();
	endwin();
	return 0;
}
