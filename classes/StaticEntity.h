#pragma once
#include "Entity.h"

class StaticEntity : public Entity
{
protected:
	sf::IntRect textureRect1{0, 0, 32, 32};
	sf::IntRect textureRect2{32, 0, 32, 32};
	sf::IntRect textureRect3{64, 0, 32, 32};
	sf::Texture texture;
	sf::Clock animationClock;
	float animationTimer = 0.0f;
	float animationSwitchTime = 0.3f;
public:
	sf::Sprite sprite;
};

