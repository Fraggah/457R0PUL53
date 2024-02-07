#include "Player.h"

Player::Player(int _x, int _y, int _s) 
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
	else if (down)
	{
		y += speed;
	}
	else if (left)
	{
		x -= speed;
	}
	else if (right)
	{
		x += speed;
	}
	sprite.setPosition(x, y);
}