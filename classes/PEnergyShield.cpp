#include "PEnergyShield.h"

PEnergyShield::PEnergyShield(float _s)
{
	tag = "shield";
	speed = _s;
	setTexture();
	sprite.scale(4, 4);
	boundingBox.setRadius(64);
	clock.restart();
}

void PEnergyShield::setTexture()
{
	if (!texture.loadFromFile("assets/16/energyshield.png"))
		printf("Player texture cannot load");

	sprite.setTexture(texture);

	sprite.setTextureRect(textureRect1);
}

void PEnergyShield::movement()
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
	boundingBox.setPosition(x + boundingBox.getRadius() + 7, y + boundingBox.getRadius() + 12);

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
