#include "DynamicEntity.h"

DynamicEntity::DynamicEntity()
{
	boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
	boundingBox.setOutlineColor(sf::Color(255, 255, 255));
	boundingBox.setOutlineThickness(2);
	boundingBox2.setFillColor(sf::Color(0, 0, 0, 0));
	boundingBox2.setOutlineColor(sf::Color(255, 0, 0));
	boundingBox2.setOutlineThickness(2);
	boundingBox3.setFillColor(sf::Color(0, 0, 0, 0));
	boundingBox3.setOutlineColor(sf::Color(0, 255, 0));
	boundingBox3.setOutlineThickness(2);
}

