#pragma once
#include "Bullet.h"

class BEnemy : public Bullet
{
	void setTexture();

public:
	BEnemy(float _x, float _y, float _s);
	void movement() override;
};

