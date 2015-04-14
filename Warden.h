#ifndef WARDEN_H
#define WARDEN_H

#include <vector>
#include "cell.h"

#ifndef AON
#define AON if(ANIMATE)
#endif

#define GRID_SIZE 4
#define SQUARE_GRID true

class Cell;

class Warden
{
friend class Cell;
public:
	
	Warden();								//constructor initializes theGrid with a 2d loop
	Warden(int g);
	void Tic();								//call the aging method on all cells
	int ShowCells();						//call the display/print method on all cells
	void LoadSeed(std::vector<Point> seed);	//load a vector of points for seed values
	void LoadSeed(std::vector<Point> seed, Point offset);
	void LoadSeed(Point seed[], int size);
	void LoadSeed(int seed[], int offset);
	int AliveCount() { return aliveList.size(); }
	void ListAlive();
	int getGSize();
private:
	int gridSize;
	std::vector<Cell> theGrid;				//all the cells, regardless of state
	std::vector<Cell *> aliveList;			//pointers to the cells that are alive
	std::vector<Cell *> birthList;			//pointers to the cells that are being born
	std::vector<Cell *> deathList;			//pointers to the cells that are dying

	void Birth(Cell *c);					//adds the cell to the aliveList
	void Death(Cell *c);					//removes " " " " "

};

#endif
