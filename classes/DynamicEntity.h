#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class DynamicEntity : public Entity
{	
public:
	DynamicEntity();
	size_t type = 0;
	sf::CircleShape boundingBox;
	float speed = 0;
	sf::Sprite sprite;
	sf::Texture texture;
	virtual void movement() = 0;
	sf::Clock clock;
};

//type 1(player) 2(Cannon) 3(DoubleCannon) 4(Assualt) 5(Bomber)