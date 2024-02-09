#include "EDoubleCannon.h"

EDoubleCannon::EDoubleCannon() : currentWaypointIndex(0)
{
    x = -50;
    y = 0;
    speed = 4;
    tag = "enemy";
    setTexture();
    sprite.scale(2, 2);
}

void EDoubleCannon::setTexture()
{
    if (!texture.loadFromFile("assets/enemy.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);
}

void EDoubleCannon::movement()
{
    // Calcula la direcci�n hacia el waypoint actual
    float dx = waypoints[currentWaypointIndex].x - x;
    float dy = waypoints[currentWaypointIndex].y - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Si el enemigo est� lo suficientemente cerca del waypoint actual, pasa al siguiente waypoint
    if (distance < 1.0) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
        return; // Salir de la funci�n para evitar actualizar la posici�n del enemigo hasta la pr�xima iteraci�n
    }

    // Normaliza la direcci�n y aplica velocidad para mover el enemigo
    dx /= distance;
    dy /= distance;
    x += dx * speed;
    y += dy * speed;

    sprite.setPosition(x, y);
    boundingBox.setPosition(x + boundingBox.getRadius(), y + boundingBox.getRadius());
}