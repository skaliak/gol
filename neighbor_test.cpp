//#include <iostream>
#include "Point.h"
#include <ncurses.h>

using std::cout;
using std::endl;

void ShowNeighbors(Point p);
void ShowNeighbors(Point p, int bound);
//MARK


int main()
{
	initscr();
	raw();
	//char ch = 'X';
	//mvaddch(5,10,ch);
	//mvaddch(3,4,ch);
	//mvaddch(6,7,ch);
	//mvaddch(2,4,ch);
	//mvaddch(9,9,ch);
	Point p = Point(5,7,7);
	
	//cout << "the point is: " << p << "\n its neighbors are:\n";

	ShowNeighbors(p,7);

	getch();
	endwin();
	return 0;
}

void ShowNeighbors(Point p)
{
	for(int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (!(i == 0 && j == 0))
			{
				Point neighbor = p + Point(i, j);
				//cout << neighbor << endl;
			}
		}
}

void ShowNeighbors(Point p, int bound)
{
	for(int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (!(i == 0 && j == 0))
			{
				Point neighbor = p + Point(i, j, bound);
				//cout << neighbor << endl;
				neighbor.cPrint();
				refresh();
			}
		}
}
