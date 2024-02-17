#pragma once
#include "DynamicEntity.h"

class PULaser : public DynamicEntity
{
	void setTexture();
public:
	PULaser(float _x, float _y, int _type);
	void movement();
};

