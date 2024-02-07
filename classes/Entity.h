#pragma once
#include <string>

class Entity
{
protected:
	int x;
	int y;
public:
	void setX(int _x);
	void setY(int _y);
	int getX();
	int getY();
};

