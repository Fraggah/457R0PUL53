#pragma once
#include "Bullet.h"

class BLaser : public Bullet
{
	void setTexture();

public:
	BLaser(float _x, float _y, float _s);
	void movement() override;
};

