#include "Coords.h"


Coords::Coords(): x(-1), y(-1) 
{

}


Coords::Coords(int _x, int _y) : x(_x), y(_y) 
{

}


Coords::~Coords() 
{

}


void Coords::setX(int _x) 
{ 
	x = _x; 
}


void Coords::setY(int _y) 
{ 
	y = _y; 
}


void Coords::setXY(int _x, int _y)
{
	x = _x;
	y = _y;
}


int Coords::getX() const 
{ 
	return x; 
}


int Coords::getY() const 
{ 
	return y; 
}


bool Coords::operator== (const Coords& _coords) const 
{ 
	return x == _coords.getX() && y == _coords.getY(); 
}