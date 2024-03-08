#include "Land.h"

Land::Land(short id, bool left, float* backgroundSpeed, sf::Vector2u winSize, std::vector<Object*>* objects,
	sf::Vector2f pos, sf::Vector2f vel) : Enemy(id, left, pos, vel)
{
	type = LAND;

	this->backgroundSpeed = backgroundSpeed;

	health = 1;
	setSize(15, 25);
	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
	setRandColor();
}

void Land::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	enemyUpdate(winSize, objects);

	setPos(getPos().x, getPos().y + *backgroundSpeed);
}