#include "Player.h"

Player::Player(float _x, float _y, float _s) 
{
	x = _x;
	y = _y;
	speed = _s;
	setTexture();
	sprite.scale(2, 2);
	boundingBox.setRadius(20);
	boundingBox.setOrigin(boundingBox.getRadius(), boundingBox.getRadius());
}

void Player::setTexture()
{
	if (!texture.loadFromFile("assets/player.png"))
		printf("Player texture cannot load");

	sprite.setTexture(texture);
}

void Player::movement()
{
	if (up)
	{
		y -= speed;
	}
	if (down)
	{
		y += speed;
	}
	if (left)
	{
		x -= speed;
	}
	if (right)
	{
		x += speed;
	}
	sprite.setPosition(x, y);
	boundingBox.setPosition(x+boundingBox.getRadius() +12, y + boundingBox.getRadius() +12);
}