#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class DynamicEntity : public Entity
{	
public:
	float speed = 0;
	sf::Sprite sprite;
	virtual void movement() = 0;
};

