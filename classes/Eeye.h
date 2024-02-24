#pragma once
#include "Enemy.h"

class Eeye : public Enemy
{
    void setTexture();
public:
    Eeye(int _x);
    void movement() override;
};


