#pragma once
#include "Bullet.h"

class BEnemy : public Bullet
{
	void setTexture();
	float speedx;

public:
	BEnemy(float _x, float _y, float _sy, float _sx);
	void movement() override;
};

