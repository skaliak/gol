#ifndef POINT_H
#define POINT_H

#ifndef ANIMATE
#define ANIMATE true
#endif

#define MAX_BOUND 50

#include <iostream>

class Point
{
private:
	int bound, x, y;
	static const char PIXEL = '#';
public:
	//constructors
	Point() : bound(MAX_BOUND) {}
	Point(int a, int b) : bound(MAX_BOUND), x(a), y(b) {} 
	Point(int a, int b, int boundary) : bound(boundary), x(a), y(b) {}
	

	void cPrint();  //this uses ncurses

	//operators
	Point const operator+(Point const& rhs);
	//Point const operator-(Point const& rhs);
	bool operator==(Point const& rhs);
	friend std::ostream &operator<<(std::ostream &out, Point p);
};


#endif
