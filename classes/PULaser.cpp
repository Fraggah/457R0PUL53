#include "PULaser.h"

PULaser::PULaser(float _x, float _y, int _type)
{
	x = _x;
	y = _y;
	type = _type;
	speed = 5;
	setTexture();
	sprite.scale(4, 4);
	boundingBox.setRadius(20);
}

void PULaser::setTexture()
{
	if (type == 1)
	{
		if (!texture.loadFromFile("assets/16/pulaser.png"))
			printf("Player texture cannot load");

		sprite.setTexture(texture);

		sprite.setTextureRect(textureRect1);
	}
	else if (type == 2)
	{
		if (!texture.loadFromFile("assets/16/putriple.png"))
			printf("Player texture cannot load");

		sprite.setTexture(texture);

		sprite.setTextureRect(textureRect1);
	}
	else if (type == 3)
	{
		if (!texture.loadFromFile("assets/16/pulife.png"))
			printf("Player texture cannot load");

		sprite.setTexture(texture);

		sprite.setTextureRect(textureRect1);
	}
	else if (type == 4)
	{
		if (!texture.loadFromFile("assets/16/puxblast.png"))
			printf("Player texture cannot load");

		sprite.setTexture(texture);

		sprite.setTextureRect(textureRect1);
	}
	else if (type == 5)
	{
		if (!texture.loadFromFile("assets/16/puenergy.png"))
			printf("Player texture cannot load");

		sprite.setTexture(texture);

		sprite.setTextureRect(textureRect1);
	}

}

void PULaser::movement()
{
	y += speed;

	sprite.setPosition(x, y);
	boundingBox.setPosition(x + 12, y+ 12);


	animationTimer += animationClock.restart().asSeconds(); // Actualizar el temporizador de animación

	if (animationTimer >= animationSwitchTime) {
		if (sprite.getTextureRect() == textureRect1) {
			sprite.setTextureRect(textureRect2);
		}
		else if (sprite.getTextureRect() == textureRect2) {
			sprite.setTextureRect(textureRect3);
		}
		else {
			sprite.setTextureRect(textureRect1);
		}
		animationTimer = 0.0f; // Reiniciar el temporizador
	}
}