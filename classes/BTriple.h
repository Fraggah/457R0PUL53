#pragma once
#include "Bullet.h"

class BTriple : public Bullet
{
	void setTexture();
	float speedx;

public:
	BTriple(float _x, float _y, float _sx, float _sy);
	void movement() override;
};

