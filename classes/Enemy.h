#pragma once
#include "DynamicEntity.h"

class Enemy : public DynamicEntity
{
    sf::Texture texture;
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
public:
    Enemy();
    void setTexture();
    void movement();
};

