#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	float x;
	float y;
public:
	std::string tag = "default";
	bool is_active = true;
	void setX(float _x);
	void setY(float _y);
	float getX();
	float getY();
};

