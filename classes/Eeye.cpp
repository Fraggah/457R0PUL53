#include "Eeye.h"

Eeye::Eeye(int _x)
{
    type = 6;
    x = _x;
    y = -50;
    speed = 2;
    lifes = 100;
    points = 10000;
    tag = "enemy";
    setTexture();
    sprite.scale(4, 4);
    boundingBox.setRadius(24);
}

void Eeye::setTexture()
{
    if (!texture.loadFromFile("assets/16/eye.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void Eeye::movement()
{
    y += speed;

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
    if (lifes < 100)
    {
        sprite.setColor(sf::Color(rand()%255+1, rand() % 255 + 1, rand() % 255 + 1));
    }
}