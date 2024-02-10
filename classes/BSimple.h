#pragma once
#include "Bullet.h"

class BSimple : public Bullet
{
	float acceleration = 0.3;
	void setTexture();

public:
	BSimple(float _x, float _y, float _s);
	void movement() override;
};

