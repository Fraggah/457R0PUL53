#include "BossAries.h"

BossAries::BossAries()
{
    x = 100;
    y = -99;
    speed = 3;
    lifes = 100;
    tag = "boss";
    type = 10;
    setTexture();
    boundingBox.setRadius(120);
    boundingBox2.setRadius(32);
    boundingBox3.setRadius(120);
    sprite.scale(4, 4);
}

void BossAries::setTexture()
{
    if (!texture.loadFromFile("assets/16/bossaries.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void BossAries::movement()
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
    boundingBox3.setPosition(x + 10, y);
    boundingBox.setPosition(x +10, y + offset);
    boundingBox2.setPosition(x + 95, y +160 );

    animationTimer += animationClock.restart().asSeconds(); // Actualizar el temporizador de animación

    if (animationTimer >= animationSwitchTime) {
        if (sprite.getTextureRect() == textureRect1) {
            sprite.setTextureRect(textureRect2);
            offset = 0;
        }
        else {
            sprite.setTextureRect(textureRect1);
            offset = -30;
        }
        animationTimer = 0.0f; // Reiniciar el temporizador
    }
}