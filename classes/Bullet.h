#pragma once
#include "DynamicEntity.h"

class Bullet : public DynamicEntity
{
	sf::Texture texture;
	void setTexture();
public:
	Bullet(int _x, int _y, int _s);
	void movement() override;
};

