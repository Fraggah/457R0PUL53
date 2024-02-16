#include "EAssault.h"

EAssault::EAssault(int _x, float _sx)
{
    type = 3;
    x = _x;
    y = -50;
    speed = 14;
    speedx = _sx;
    lifes = 1;
    tag = "enemy";
    setTexture();
    sprite.scale(4, 4);
}

void EAssault::setTexture()
{
    if (!texture.loadFromFile("assets/16/eassault.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void EAssault::movement()
{
    y += speed;
    x += speedx;

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