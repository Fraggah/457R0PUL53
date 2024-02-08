#include "Player.h"

Player::Player(float _x, float _y, float _s) 
{
	x = _x;
	y = _y;
	speed = _s;
	setTexture();
	sprite.scale(3, 3);
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
}