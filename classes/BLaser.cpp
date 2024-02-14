#include "BLaser.h"

BLaser::BLaser(float _x, float _y, float _s)
{
	x = _x;
	y = _y;
	speed = _s;
	tag = "bullet";
	setTexture();
	sprite.scale(3, 3);
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
	sprite.setPosition(x - 48, y - 48);
	boundingBox.setPosition(x, y);
}