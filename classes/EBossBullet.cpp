#include "EBossBullet.h"

EBossBullet::EBossBullet(float _x, float _y, float _sx, float _sy)
{
    x = _x;
    y = _y;
    speed = _sy;
    speedx = _sx;
    lifes = 1;
    points = 50;
    tag = "enemy";
    setTexture();
    sprite.setOrigin(8,8);
    sprite.scale(4, 4);
}

void EBossBullet::setTexture()
{
    if (!texture.loadFromFile("assets/16/bossbullet.png"))
        printf("cannot load Enemy texture");

    sprite.setTexture(texture);

    sprite.setTextureRect(textureRect1);
}

void EBossBullet::movement()
{
    y += speed;
    x += speedx;

    sprite.setPosition(x+32, y+32);
    boundingBox.setPosition(x + boundingBox.getRadius(), y + boundingBox.getRadius());
    sprite.rotate(6);
}