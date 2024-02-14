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
    // Calcula la dirección hacia el waypoint actual
    float dx = waypoints[currentWaypointIndex].x - x;
    float dy = waypoints[currentWaypointIndex].y - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Si el enemigo está lo suficientemente cerca del waypoint actual, pasa al siguiente waypoint
    if (distance < 5.0) {
        if (!reachedFirstWaypoint) {
            // Si es la primera vez que llega al primer waypoint, frena y reinicia el temporizador
            stop.restart();
            reachedFirstWaypoint = true;
            speed = 0;
            return; // Salir de la función para evitar actualizar la posición del enemigo hasta la próxima iteración
        }
        else if (stop.getElapsedTime() >= sf::seconds(2)) {
            // Si ha pasado un segundo desde que llegó al primer waypoint, restablece la velocidad y pasa al siguiente waypoint
            speed = 16;
            currentWaypointIndex = 5;
            reachedFirstWaypoint = false; // Reiniciar la bandera
        }
        return; // Salir de la función para evitar actualizar la posición del enemigo hasta la próxima iteración
    }

    // Normaliza la dirección y aplica velocidad para mover el enemigo
    dx /= distance;
    dy /= distance;
    x += dx * speed;
    y += dy * speed;

    sprite.setPosition(x, y);
    boundingBox.setPosition(x + boundingBox.getRadius(), y + boundingBox.getRadius());

    // Restablecer la velocidad de animación si ha pasado el tiempo de conmutación
    if (animationTimer >= animationSwitchTime) {
        if (sprite.getTextureRect() == textureRect1) {
            sprite.setTextureRect(textureRect2);
        }
        else {
            sprite.setTextureRect(textureRect1);
        }
        animationTimer = 0.0f; // Reiniciar el temporizador de animación
    }
}