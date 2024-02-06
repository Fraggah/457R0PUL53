#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class DynamicEntity : public Entity
{
protected:	
	float speed;
public:
	sf::Sprite sprite;
};

