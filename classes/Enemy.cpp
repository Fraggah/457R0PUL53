#include "Enemy.h"

Enemy::Enemy() : currentWaypointIndex(0)
{
    tag = "enemy";
    boundingBox.setRadius(32);
    boundingBox.setOrigin(boundingBox.getRadius(), boundingBox.getRadius());
}
