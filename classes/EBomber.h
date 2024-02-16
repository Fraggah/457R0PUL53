#pragma once
#include "Enemy.h"

class EBomber : public Enemy
{
    size_t currentWaypointIndex;
    std::vector<sf::Vector2f> waypoints = {
        {250, 100},
        {500, 100},
        {750, 100},
        {500, -150},

    };
    bool reachedFirstWaypoint = false;
    sf::Clock stop;
    void setTexture();
public:
    EBomber(int _wp);
    void movement() override;
};

