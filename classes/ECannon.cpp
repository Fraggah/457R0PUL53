#include "ECannon.h"

ECannon::ECannon(bool _l, int _wp) 
{
    type = 2;
    currentWaypointIndex = _wp;
    lstart = _l;
    if (lstart)
    {
        x = -50;
        y = -50;
    }
    else
    {
        x = 1024 + 50;
        y = -50;
    }
    speed = 10;
    lifes = 1;
    points = 250;
    tag = "enemy";
    setTexture();
    sprite.setScale(4, 4);
}

void ECannon::setTexture()
{
    if (!texture.loadFromFile("assets/16/ecannon.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void ECannon::movement()
{
    // Calcula la dirección hacia el waypoint actual
    float dx = waypoints[currentWaypointIndex].x - x;
    float dy = waypoints[currentWaypointIndex].y - y;
    float distance = sqrt(dx * dx + dy * dy);


    if (distance < 5.0) {
        if (!reachedFirstWaypoint) {
            stop.restart();
            reachedFirstWaypoint = true;
            speed = 0;
        }
        else if (stop.getElapsedTime() >= sf::seconds(2)) {
            speed = 16;
            currentWaypointIndex = 5;
            reachedFirstWaypoint = false;
        }
    }

    dx /= distance;
    dy /= distance;
    x += dx * speed;
    y += dy * speed;

    sprite.setPosition(x, y);
    boundingBox.setPosition(x + boundingBox.getRadius(), y + boundingBox.getRadius());

    if (PL) {
        sprite.setTextureRect(textureRect3);

    }
    else if (PR)
    {
        sprite.setTextureRect(textureRect2);

    }
    else {
        sprite.setTextureRect(textureRect1);

    }
}