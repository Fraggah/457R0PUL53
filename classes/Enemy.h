#pragma once
#include "DynamicEntity.h"

class Enemy : public DynamicEntity
{
protected:
    size_t currentWaypointIndex;
    Enemy();
    void movement() override = 0;
};

