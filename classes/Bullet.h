#pragma once
#include "DynamicEntity.h"

class Bullet : public DynamicEntity
{
	sf::Texture texture;
	void setTexture();
	float acceleration = 0.3;

public:
	Bullet(float _x, float _y, float _s);
	void movement() override;
	sf::Clock clock;
};

