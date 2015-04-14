/******************************
**	Peter Lindberg
**	Project 5
**	Game of life
**
******************************/


#include <iostream>
#include <string>
#include <vector>
#include <curses.h>
//#include <unistd.h>
#include <sstream>

#include "cell.h"

#define DBG false
#define BR cout << "\n\n";
#ifndef AON
#define AON if(ANIMATE)  //animate is in Point.h
#endif

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	AON initscr();
	
	AON curs_set(0);

	//std::vector<Point> blinker = {{0,0}, {0,1}, {0,2}};
	//std::vector<Point> glider = {{0,2}, {1,0}, {1,2}, {2,1}, {2,2}};
	//std::vector<Point> block = {{0,0}, {0,1}, {1,0}, {1,1}};

	int glider[] = {0,2,1,0,1,2,2,1,2,2,-1};
	int spaceship[] = {0,0,0,3,1,4,2,0,2,4,3,1,3,2,3,3,3,4,-1};
	int gun[] = {1,5,2,5,1,6,2,6,35,3,35,4,36,3,36,4,
				12,4,11,5,11,6,11,7,12,8,13,9,14,9,
				14,3,13,3,16,4,18,6,15,6,17,5,17,6,17,7,16,8,
				21,5,21,4,21,3,22,5,22,4,22,3,
				23,2,23,6,25,2,25,1,25,6,25,7,-1};
	int gsubset[] = {12,4,11,5,11,6,11,7,12,8,13,9,14,9,
					14,3,13,3,16,4,18,6,15,6,17,5,17,6,17,7,16,8,-1};
	int diehard[] = {0,0,0,1,1,0,1,1,0,5,0,7,1,6,2,6,-1};
	int custom[] = {0,0,0,1,0,2,1,5,2,3,2,5,3,4,3,5,-1};
	
	int gSize = 40;
	Warden w(gSize);
	bool repeat = true;

	while(repeat)
	{
		AON wclear(stdscr);
		nocbreak();  //cancels earlier call to halfdelay()
		char menuchoice;

		printw("Starting seeds:\n");
		printw("1: gun, 2: glider, 3: spaceship, 4: flower, 5: diehard, 6: blinkerglider\n");
		printw("Enter a number 1 - 6, or any other character to quit: ");
		menuchoice = getch();

		switch (menuchoice)
		{
			case '1':
			        w.LoadSeed(gun, 0);
			        break;
			case '2':
			        w.LoadSeed(glider, 5);
			        break;
			case '3':
			        w.LoadSeed(spaceship, 5);
			        break;
			case '4':
			        w.LoadSeed(gsubset, 10);
			        break;
			case '5':
			        w.LoadSeed(diehard, 20);
			        break;
			case '6':
				w.LoadSeed(custom, 0);
				break;
			default:
				repeat = false;  //this might be overkill
				AON endwin();
				return 0;
		}

		getch();
		printw("\n\nPress enter to see the pattern, press enter again to start the animation\n");
		printw("press q to quit the running animation");
		getch();

		int alive = w.ShowCells();
		getch();

		//this causes getch() to abort after a short delay
		halfdelay(1);
		char ch = 't';
		while( (ch != 'q') && (alive > 0) )
		{
			alive = w.ShowCells();
			w.Tic();
			//usleep(100000);
			ch = getch();
		}
	}

	AON endwin();
	
	BR
	return 0;
}
