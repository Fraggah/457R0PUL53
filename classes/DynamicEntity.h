#pragma once
#include "Entity.h"

class DynamicEntity : public Entity
{	
public:
	DynamicEntity();
	sf::IntRect textureRect1{0, 0, 16, 16};
	sf::IntRect textureRect2{16, 0, 16, 16};
	sf::IntRect textureRect3{32, 0, 16, 16};
	size_t type = 0;
	int lifes;
	int points;
	sf::CircleShape boundingBox;
	sf::CircleShape boundingBox2;
	sf::CircleShape boundingBox3;
	float speed = 0;
	float speedx = 0;
	sf::Sprite sprite;
	sf::Texture texture;
	virtual void movement() = 0;
	sf::Clock clock;
	sf::Clock animationClock;
	float animationTimer = 0.0f;
	float animationSwitchTime = 0.2f;
	int animationState = 0;
	bool PL;
	bool PR;
};

