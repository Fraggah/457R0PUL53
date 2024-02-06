#pragma once
#include "DynamicEntity.h"
#include <SFML/Graphics.hpp>

class Player : public DynamicEntity
{
protected:
	sf::Texture texture;
	void setTexture();
public:
	Player(int x, int y, int s);
	int getX() { return posX; }
	int getY() { return posY; }
	void movement();
};

