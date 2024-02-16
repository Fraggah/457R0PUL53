#include "BSimple.h"

BSimple::BSimple(float _x, float _y, float _s)
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

void BSimple::setTexture()
{
	if (!texture.loadFromFile("assets/bsimple.png"))
		printf("cannot load Bullet texture");

	sprite.setTexture(texture);
}

void BSimple::movement()
{
	speed += acceleration;
	y -= speed;
	sprite.setPosition(x - 32, y - 32);
	boundingBox.setPosition(x, y);
}