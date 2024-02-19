#include "EBomber.h"

EBomber::EBomber(size_t _wp)
{
    type = 4;
    currentWaypointIndex = _wp;
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
    points = 1000;
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
    if (stop.getElapsedTime() < sf::seconds(0.3))
    {
        speed = 10;
    }
    else if (stop.getElapsedTime() > sf::seconds(0.3) && stop.getElapsedTime() < sf::seconds(2.3))
    {
        speed = 0;
    }
    else if (stop.getElapsedTime() > sf::seconds(2.3))
    {
        speed = -10;
    }

    y += speed;

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