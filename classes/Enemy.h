#pragma once
#include "DynamicEntity.h"

class Enemy : public DynamicEntity
{
    size_t currentWaypointIndex;
    int lifes;
public:
    Enemy();
    int getLifes() { return lifes; }
    void movement() override = 0;
};

