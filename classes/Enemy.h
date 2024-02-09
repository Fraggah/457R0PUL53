#pragma once
#include "DynamicEntity.h"

class Enemy : public DynamicEntity
{
    size_t currentWaypointIndex;
public:
    Enemy();
    void movement() override = 0;
};

