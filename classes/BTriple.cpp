#include "BTriple.h"

BTriple::BTriple(float _x, float _y, float _sx, float _sy)
{
	x = _x;
	y = _y;
	speed = _sy;
	speedx = _sx;
	tag = "bullet";
	setTexture();
	sprite.scale(3, 3);
	boundingBox.setRadius(6);
	boundingBox.setOrigin(boundingBox.getRadius(), boundingBox.getRadius());
}

void BTriple::setTexture()
{
	if (!texture.loadFromFile("assets/btriple.png"))
		printf("cannot load Bullet texture");

	sprite.setTexture(texture);
}

void BTriple::movement()
{
	y -= speed;
	x += speedx;
	sprite.setPosition(x - 48, y - 48);
	boundingBox.setPosition(x, y);
}