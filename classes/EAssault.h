#pragma once
#include "Enemy.h"

class EAssault : public Enemy
{
    size_t currentWaypointIndex;
    void setTexture();
public:
    EAssault(int _x, float _sx);
    void movement() override;
};


