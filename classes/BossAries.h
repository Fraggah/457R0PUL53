#pragma once
#include "DynamicEntity.h"

class BossAries : public DynamicEntity
{
    sf::IntRect textureRect1{0, 0, 64, 64};
    sf::IntRect textureRect2{64, 0, 64, 64};
    size_t currentWaypointIndex;
    std::vector<sf::Vector2f> waypoints = {
        {70, 100},
        {700, 100},
        {700,500},
        {70,500}
    };
	void setTexture();
    float offset = -30;
public:
    BossAries();
    float animationSwitchTime = 2.f;
	void movement();
};

