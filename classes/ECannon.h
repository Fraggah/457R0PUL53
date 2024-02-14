#pragma once
#include "Enemy.h"

class ECannon : public Enemy
{
    size_t currentWaypointIndex;
    std::vector<sf::Vector2f> waypoints = {
        {150, 500},
        {300, 500},
        {450, 500},
        {600, 500},
        {750, 500},
        {1900, 1900},

    };
    bool reachedFirstWaypoint = false;
    bool lstart;
    float positionX;
    sf::Clock stop;
    void setTexture();
public:
    ECannon(bool _l, int _wp);
    void movement() override;
};

