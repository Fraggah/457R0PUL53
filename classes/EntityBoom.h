#pragma once
#include "DynamicEntity.h"

class EntityBoom : public DynamicEntity
{
	void setTexture();
	bool isplayer;
public:
	EntityBoom(float _x, float _y, bool _isp);
	void movement();
};

