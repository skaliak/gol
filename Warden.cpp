#include <vector>
#include <algorithm>
#include <iterator>
#include <curses.h>

#include "Warden.h"
#include "cell.h"

using std::find;
using std::vector;

Warden::Warden(int g)
{
	gridSize = g;
	//this needs to do a 2d loop to create all the cell objects and store them in theGrid
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			theGrid.push_back(Point(i,j, gridSize));
		}
	}

	//need some way of adding the seed cells
}

Warden::Warden()
{
	Warden(50);
}

void Warden::Birth(Cell *c)
{
	DMESG(cell being born)
	//add c to the aliveList, but check for duplicates first
	//duplicate checking can be done by using std::find from <algorithm>
	//this is wrong should be ==, not !=
	if (find(aliveList.begin(), aliveList.end(), c) == aliveList.end() )
	{
		//adding to the same list that's being searched will alter the outcome
		//aliveList.push_back(c);
		birthList.push_back(c);
		//change the cell's "state" member?
	}
	//throw an exception here?
}

void Warden::Death(Cell *c)
{
	//same as birth, but in reverse
	DMESG(cell dying)
	vector<Cell *>::iterator it = find(aliveList.begin(), aliveList.end(), c);

	if (it != aliveList.end())
	{
		//erasing from the same list that's being searched will alter the outcome
		//aliveList.erase(it);
		deathList.push_back(c);
		//change the cell's "state" member?
	}
}

void Warden::Tic()
{
	for (vector<Cell>::iterator i = theGrid.begin(); i != theGrid.end(); ++i)
	{
		//std::cout << ".";
		//i->pPrint();
		i->Age(*this);
	}

	//at the end of the procedure, make changes to the aliveList, based on the
	//birthList and deathList

	for (vector<Cell *>::iterator i = birthList.begin(); i != birthList.end(); ++i)
	{
		Cell *cell_ptr = &(**i);
		aliveList.push_back(cell_ptr); 
	}

	vector<Cell *>::iterator alive_it = aliveList.begin();

	while(alive_it != aliveList.end())
	{
		vector<Cell *>::iterator dead_it = find(deathList.begin(), deathList.end(), *alive_it);

		if (dead_it != deathList.end())
		{
			//deathList.push_back(c);

			alive_it = aliveList.erase(alive_it);
		}
		else
		{
			++alive_it;	
		}
	}

	//reset these at the end of the Tic
	birthList.clear();
	deathList.clear();
}

int Warden::ShowCells()
{
	//print all the alive cells to the screen
	//only needs to loop through aliveList, I guess
	//the print method is in the Point class
	wclear(stdscr);

	for (vector<Cell *>::iterator i = aliveList.begin(); i != aliveList.end(); ++i)
	{
		//for an explanation of why the weird (**i) is needed, see 
		//the definition of Cell::countAliveNeighbors()
		(**i).Print();
	}

	refresh();
	//return the number of alive cells so we can abort if there are no more alive
	return aliveList.size();
}

void Warden::ListAlive()
{
	std::cout << "\n";
	for (std::vector<Cell *>::iterator i = aliveList.begin(); i != aliveList.end(); ++i)
	{
		(**i).pPrint();
	}
	std::cout << "\n";
}

void Warden::LoadSeed(vector<Point> seed, Point offset)
{
	Point p;
	//clear the existing seed before loading the new one
	aliveList.clear();
	//load a predefined set of alive cells
	for (vector<Cell>::iterator grid_it = theGrid.begin(); grid_it != theGrid.end(); ++grid_it)
	{
		//this is a little more readable that the implementation in Birth()
		
		p = grid_it->getPoint() + offset;
		vector<Point>::iterator point_it = find(seed.begin(), seed.end(), p);

		if (point_it != seed.end())
		{
			//std::cout << "  grid point:";
			//grid_it->pPrint();
			//std::cout << "offset point:" << p;
			//using the pointer directly doesn't work.
			Cell *cell_ptr = &(*grid_it);
			aliveList.push_back(cell_ptr);  
		}
	}
}

void Warden::LoadSeed(vector<Point> seed)
{
	Point offset(0,0, gridSize);

	LoadSeed(seed, offset);
}

void Warden::LoadSeed(Point seed[], int size)
{
	vector<Point> v;
	for (int i = 0; i < size; ++i)
	{
		v.push_back(seed[i]);
	}
	LoadSeed(v);
}

void Warden::LoadSeed(int seed[], int offset)
{
	Point offsetPoint(-offset, -offset, gridSize);
	vector<Point> v;
	int i = 0;
	while(seed[i] != -1)
	{
		Point p(seed[i], seed[i + 1]);
		v.push_back(p);
		i += 2;
	}
	LoadSeed(v, offsetPoint);
}



