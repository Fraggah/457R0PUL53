#pragma once
#include "DynamicEntity.h"

class PEnergyShield : public DynamicEntity
{
	void setTexture();
	sf::IntRect textureRect1{0, 0, 32, 32};
	sf::IntRect textureRect2{32, 0, 32, 32};
	sf::IntRect textureRect3{64, 0, 32, 32};
public:
	PEnergyShield(float _s);
	bool left = false;
	bool up = false;
	bool right = false;
	bool down = false;
	void movement();
};

