#pragma once
#include "Enemy.h"

class EBossBullet : public Enemy
{
    void setTexture();
public:
    EBossBullet(float _x, float _y, float _sx, float _sy);
    void movement() override;
};

