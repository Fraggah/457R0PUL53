#include "Bullet.h"

Bullet::Bullet(float _x, float _y, float _s)
{
	x = _x;
	y = _y;
	speed = _s;
	tag = "bullet";
	setTexture();
	sprite.scale(0.3,0.3);
}

void Bullet::setTexture()
{
	if (!texture.loadFromFile("assets/player.png"))
		printf("cannot load Bullet texture");

	sprite.setTexture(texture);
}

void Bullet::movement()
{
	speed += acceleration;
	y -= speed;
	sprite.setPosition(x, y);
}