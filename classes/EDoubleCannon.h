#pragma once
#include "Enemy.h"

class EDoubleCannon : public Enemy
{
    size_t currentWaypointIndex;
    std::vector<sf::Vector2f> waypoints = {
        {100, 100},
        {900, 100},
        {900, 200},
        {100, 200},
        {100, 300},
        {900, 300},
        {1200, 400},
    };
    bool left;
    void setTexture();
public:
    EDoubleCannon(bool _l);
    void movement() override;
};

