#include "EntityBoom.h"

EntityBoom::EntityBoom(float _x, float _y, bool _isp)
{
    tag = "explosion";
	x = _x;
	y = _y;
    isplayer = _isp;
    setTexture();
    sprite.scale(2, 2);
}

void EntityBoom::setTexture()
{
    if (isplayer)
    {
        if (!texture.loadFromFile("assets/playerboom.png"))
            printf("cannot load Enemy texture");
    }
    else {
        if (!texture.loadFromFile("assets/enemyboom.png"))
            printf("cannot load Enemy texture");
    }


    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void EntityBoom::movement()
{
    sprite.setPosition(x, y);

    animationTimer += animationClock.restart().asSeconds(); // Actualizar el temporizador de animación

    if (animationTimer >= animationSwitchTime) 
    {
        animationState++;
        if (sprite.getTextureRect() == textureRect1) 
        {
            sprite.setTextureRect(textureRect2);
        }
        else
        {
            sprite.setTextureRect(textureRect3);
        }
        animationTimer = 0;
    }
}