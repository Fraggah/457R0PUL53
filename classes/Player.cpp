#include "Player.h"

Player::Player(int x, int y, int s) 
{
	posX = x;
	posY = y;
	speed = s;
	setTexture();
}

void Player::setTexture()
{
	if (!texture.loadFromFile("assets/player.png"))
		printf("Player texture cannot load");

	sprite.setTexture(texture);
}

void Player::movement()
{
	sprite.setPosition(posX, posY);
}