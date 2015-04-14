#ifndef CELL_H
#define CELL_H
#include "Point.h"
#include "Warden.h"
#include <vector>

#define DMESG(x) if(DBG) std::cout << #x << " ";

#ifndef DBG
#define DBG false
#endif

enum State {alive, dead};

class Warden;

class Cell
{
public:
	Cell(Point initialPoint) : myPoint(initialPoint) {}
	Cell(int x, int y);
	State getState() { return myState; }
	Point getPoint() { return myPoint; }
	void Print();
	void pPrint();
	void Age(Warden &w);
	int countAliveNeighbors(const Warden& w);
	std::vector<Point> listNeighbors(); 
private:
	Point myPoint;

	//are the next two even necessary?
	State myState;
	State newState;
};

#endif  //include guard
