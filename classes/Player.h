#pragma once
#include "DynamicEntity.h"
#include <SFML/Graphics.hpp>

class Player : public DynamicEntity
{
private:
	sf::Texture texture;
	void setTexture();
public:
	Player(float _x, float _y, float _s);
	bool left  = false;
	bool up    = false;
	bool right = false;
	bool down  = false;
	void movement() override;
};

