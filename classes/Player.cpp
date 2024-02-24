#include "Player.h"

Player::Player(float _x, float _y, float _s) 
{
	x = _x;
	y = _y;
	speed = _s;
	lifes = 3;
	points = 0;
	setTexture();
	sprite.scale(4, 4);
	boundingBox.setRadius(24);
	boundingBox.setOrigin(boundingBox.getRadius(), boundingBox.getRadius());
}

void Player::setTexture()
{
	if (!texture.loadFromFile("assets/16/player.png"))
		printf("Player texture cannot load");

	sprite.setTexture(texture);

	sprite.setTextureRect(textureRect1);
}

void Player::movement()
{
	if (up && y > 4)
	{
		y -= speed;
	}
	if (down && y < 894)
	{
		y += speed;
	}
	if (left && x > 0)
	{
		x -= speed;
	}
	if (right && x < 960)
	{
		x += speed;
	}
	sprite.setPosition(x, y);
	boundingBox.setPosition(x+boundingBox.getRadius() + 7, y + boundingBox.getRadius() +12);

	animationTimer += animationClock.restart().asSeconds(); // Actualizar el temporizador de animación

	if (animationTimer >= animationSwitchTime) {
		if (sprite.getTextureRect() == textureRect1) {
			sprite.setTextureRect(textureRect2);
		}
		else {
			sprite.setTextureRect(textureRect1);
		}
		animationTimer = 0.0f; // Reiniciar el temporizador
	}
}