#include "cell.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

Cell::Cell(int x, int y)
{
	this->myPoint = Point(x, y);

}

vector<Point> Cell::listNeighbors()
{
	Point p = this->myPoint;
	vector<Point> v;

	//std::cout << "point: " << p << " all neighbors: ";

	for(int i = -1; i <= 1; i++)
	{	
		for (int j = -1; j <= 1; j++)
		{
			if (!(i == 0 && j == 0))
			{
				Point neighbor = p + Point(i, j);
				v.push_back(neighbor);
				//std::cout << neighbor << " ";
			}
		}
	}
	//std::cout << "\n";
	return v;
}


int Cell::countAliveNeighbors(const Warden &w)
{
	int count = 0;
	vector<Point> neighbors = listNeighbors();

	//std::cout << "\npoint: " << this->myPoint << " alive neighbors: ";
	//loop through the alive list (cells)
	for (vector<Cell*>::const_iterator i = w.aliveList.begin(); i != w.aliveList.end(); ++i)
	{
		for (vector<Point>::iterator n = neighbors.begin(); n != neighbors.end(); ++n)
		{
			
			//some weird stuff is going on on the next line:
			//n is an iterator, pointing to a Point, so it needs
			//to be derefrenced.  On the RHS, i is an iterator for
			//aliveList, which is a vector of Cell pointers, so it
			//need to be double dereferenced with two asterisks,
			//plus there needs to be parens, to indicate that
			//we're dereferencing *i, and not *i.myPoint, i.e.
			//myPoint is not a pointer.  Whew!
			if (*n == (**i).myPoint) 
			{
				//std::cout << " " << *n;
				count++;
			}
		}
	}
	//std::cout << " alive neighbor count: " << count << " ";
	return count;
}

/********************************************************************************************
** Rules:
** Any live cell with fewer than two live neighbours dies, as if caused by under-population.
** Any live cell with two or three live neighbours lives on to the next generation.
** Any live cell with more than three live neighbours dies, as if by overcrowding.
** Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
********************************************************************************************/
void Cell::Age(Warden &w)
{
	//DMESG(aging)
	int count = countAliveNeighbors(w);
	//std::cout << "\nalive neighbors: " << count << "\n";

	if (count == 3)
	{
		DMESG(I am alive!)
		//std::cout << " " << myPoint << "\n" << w.AliveCount() << " cells alive ";
		//cell becomes alive
		w.Birth(this);
		//std::cout << w.AliveCount() << " cells alive ";
	}

	if ( (count < 2) || (count > 3) )
	{
		DMESG(goodbye cruel world!)
		//cell dies
		w.Death(this);
		//std::cout << w.AliveCount() << " cells alive ";
	}

	//need to add a condition for staying alive?
	//
}

void Cell::Print()
{
	//do we need to change the state members here?
	myPoint.cPrint();
}

void Cell::pPrint()
{
	std::cout << myPoint << " ";

}
