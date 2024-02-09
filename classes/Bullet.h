#pragma once
#include "DynamicEntity.h"

class Bullet : public DynamicEntity
{
	void setTexture();
	float acceleration = 0.3;

public:
	Bullet(float _x, float _y, float _s);
	void movement() override;
};

