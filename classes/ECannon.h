#pragma once
#include "Enemy.h"

class ECannon : public Enemy
{
    size_t currentWaypointIndex;
    std::vector<sf::Vector2f> waypoints = {
        {150, 450},
        {300, 450},
        {450, 450},
        {600, 450},
        {750, 450},
        {1900, 1900},
    };
    bool reachedFirstWaypoint = false;
    bool lstart;
    sf::Clock stop;
    void setTexture();
public:
    ECannon(bool _l, int _wp);
    void movement() override;
};

