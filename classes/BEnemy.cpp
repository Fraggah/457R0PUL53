#include "BEnemy.h"

BEnemy::BEnemy(float _x, float _y, float _s)
{
	x = _x;
	y = _y;
	speed = _s;
	tag = "enemybullet";
	setTexture();
	sprite.scale(2, -2);
	boundingBox.setRadius(3);
	boundingBox.setOrigin(boundingBox.getRadius(), boundingBox.getRadius());
}

void BEnemy::setTexture()
{
	if (!texture.loadFromFile("assets/bsimple.png"))
		printf("cannot load Bullet texture");

	sprite.setTexture(texture);
}

void BEnemy::movement()
{
	y += speed;
	sprite.setPosition(x - 32, y + 32);
	boundingBox.setPosition(x, y);
}