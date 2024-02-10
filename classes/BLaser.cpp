#include "BLaser.h"

BLaser::BLaser(float _x, float _y, float _s)
{
	x = _x;
	y = _y;
	speed = _s;
	tag = "bullet";
	setTexture();
	sprite.scale(2, 2);
	boundingBox.setRadius(3);
	boundingBox.setOrigin(boundingBox.getRadius(), boundingBox.getRadius());
}

void BLaser::setTexture()
{
	if (!texture.loadFromFile("assets/blaser.png"))
		printf("cannot load Bullet texture");

	sprite.setTexture(texture);
}

void BLaser::movement()
{
	y -= speed;
	sprite.setPosition(x - 32, y - 32);
	boundingBox.setPosition(x, y);
}