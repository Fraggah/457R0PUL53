#include "Bullet.h"

Bullet::Bullet(int _x, int _y, int _s)
{
	x = _x;
	y = _y;
	speed = _s;
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
	y -= speed;
	sprite.setPosition(x, y);
}