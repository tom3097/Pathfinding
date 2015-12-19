#include "Field.h"


Field::Field() : allowed(true), G(-1), H(-1), F(-1)
{

}


Field::Field(Coords _coords, bool _allowed) : coords(_coords), allowed(_allowed), G(-1), H(-1), F(-1), parent(nullptr)
{

}


Field::~Field()
{

}


void Field::reset()
{ 
	G = H = F = 0; 
	parent = nullptr;
}


void Field::setCoords(Coords _coords) 
{ 
	coords.setXY(_coords.getX(), _coords.getY());
}


void Field::setAllowed(bool flag) 
{ 
	allowed = flag; 
}


void Field::setParent(Field *_parent) 
{ 
	parent = _parent; 
}


void Field::updateGHF(unsigned newG, unsigned newH) 
{ 
	G = newG; 
	H = newH; 
	F = newG + newH; 
}


void Field::updateGHF(unsigned newG) 
{ 
	G = newG; 
	F = newG + H; 
}


void Field::updateGF(unsigned newG) 
{ 
	G = newG; 
	F = newG; 
}


Coords Field::getCoords() const
{ 
	return coords; 
}


bool Field::getAllowed() const 
{ 
	return allowed; 
}


unsigned Field::getF() const 
{ 
	return F; 
}


unsigned Field::getG() const 
{ 
	return G; 
}


Field* Field::getParent() 
{ 
	return parent; 
}


bool Field::operator== (const Field& _field) const 
{ 
	return coords == _field.getCoords() && allowed == _field.getAllowed(); 
}


bool Field::operator!= (const Field& _field) const 
{ 
	return !(*this == _field); 
}