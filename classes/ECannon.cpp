#include "ECannon.h"

ECannon::ECannon(bool _l, int _wp) : currentWaypointIndex(_wp)
{
    type = 2;
    x = -50;
    y = -50;
    speed = 10;
    lstart = _l;
    tag = "enemy";
    setTexture();
    sprite.scale(4, 4);
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
    // Calcula la direcci�n hacia el waypoint actual
    float dx = waypoints[currentWaypointIndex].x - x;
    float dy = waypoints[currentWaypointIndex].y - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Si el enemigo est� lo suficientemente cerca del waypoint actual, pasa al siguiente waypoint
    if (distance < 5.0) {
        if (!reachedFirstWaypoint) {
            // Si es la primera vez que llega al primer waypoint, frena y reinicia el temporizador
            stop.restart();
            reachedFirstWaypoint = true;
            speed = 0;
            return; // Salir de la funci�n para evitar actualizar la posici�n del enemigo hasta la pr�xima iteraci�n
        }
        else if (stop.getElapsedTime() >= sf::seconds(2)) {
            // Si ha pasado un segundo desde que lleg� al primer waypoint, restablece la velocidad y pasa al siguiente waypoint
            speed = 16;
            currentWaypointIndex = 5;
            reachedFirstWaypoint = false; // Reiniciar la bandera
        }
        return; // Salir de la funci�n para evitar actualizar la posici�n del enemigo hasta la pr�xima iteraci�n
    }

    // Normaliza la direcci�n y aplica velocidad para mover el enemigo
    dx /= distance;
    dy /= distance;
    x += dx * speed;
    y += dy * speed;

    sprite.setPosition(x, y);
    boundingBox.setPosition(x + boundingBox.getRadius(), y + boundingBox.getRadius());

    // Restablecer la velocidad de animaci�n si ha pasado el tiempo de conmutaci�n
    if (animationTimer >= animationSwitchTime) {
        if (sprite.getTextureRect() == textureRect1) {
            sprite.setTextureRect(textureRect2);
        }
        else {
            sprite.setTextureRect(textureRect1);
        }
        animationTimer = 0.0f; // Reiniciar el temporizador de animaci�n
    }
}