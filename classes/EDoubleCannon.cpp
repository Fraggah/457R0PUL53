#include "EDoubleCannon.h"

EDoubleCannon::EDoubleCannon(bool _l) : currentWaypointIndex(0)
{
    type = 1;
    speed = 5;
    lifes = 1;
    points = 100;
    left = _l;
    if (left)
    {
        x = -50;
        y = 0;
        waypoints = {
            {100, 100},
            {900, 100},
            {900, 200},
            {100, 200},
            {100, 300},
            {900, 300},
            {1200, 400},
        };
    }
    else
    {
        x = 1010;
        y = 0;
        waypoints = {
            {900, 100},
            {100, 100},
            {100, 200},
            {900, 200},
            {900, 300},
            {100, 300},
            {-150, 400},
        };
    }

    tag = "enemy";
    setTexture();
    sprite.scale(4, 4);
}

void EDoubleCannon::setTexture()
{
    if (!texture.loadFromFile("assets/16/edoublecannon.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void EDoubleCannon::movement()
{
    // Calcula la dirección hacia el waypoint actual
    float dx = waypoints[currentWaypointIndex].x - x;
    float dy = waypoints[currentWaypointIndex].y - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Si el enemigo está lo suficientemente cerca del waypoint actual, pasa al siguiente waypoint
    if (distance < 3.0) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
        return; // Salir de la función para evitar actualizar la posición del enemigo hasta la próxima iteración
    }

    // Normaliza la dirección y aplica velocidad para mover el enemigo
    dx /= distance;
    dy /= distance;
    x += dx * speed;
    y += dy * speed;

    sprite.setPosition(x, y);
    boundingBox.setPosition(x + boundingBox.getRadius(), y + boundingBox.getRadius());

    animationTimer += animationClock.restart().asSeconds(); // Actualizar el temporizador de animación

    if (animationTimer >= animationSwitchTime) {
        if (sprite.getTextureRect() == textureRect1) {
            sprite.setTextureRect(textureRect2);
        }
        else {
            sprite.setTextureRect(textureRect1);
        }
        animationTimer = 0.0f; // Reiniciar el temporizador
    }
}
