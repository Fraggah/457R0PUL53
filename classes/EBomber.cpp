#include "EBomber.h"

EBomber::EBomber(int _wp) : currentWaypointIndex(_wp)
{
    type = 4;
    if (_wp == 0)
    {
        x = 250;
        y = -50;
    }
    else if (_wp == 1)
    {
        x = 500;
        y = -50;
    }
    else if (_wp == 2)
    {
        x = 750;
        y = -50;
    }
    lifes = 2;
    speed = 10;
    tag = "enemy";
    setTexture();
    sprite.scale(4, 4);
}

void EBomber::setTexture()
{
    if (!texture.loadFromFile("assets/16/ebomber.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void EBomber::movement()
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
            currentWaypointIndex = 3;
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


    if (lifes == 1)
    {
        sprite.setColor(sf::Color::Red);
    }

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