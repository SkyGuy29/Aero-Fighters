#include "Collectable.h"

Collectable::Collectable(short id)
{
	this->id = id;
	type = COLLECTABLE;
	setSize(15, 30);
	pos.y = 0;
	pos.x = 100;
	if (id == 0)
		vel = sf::Vector2f(0, 1);
	else
		vel = sf::Vector2f(.707, .707);
	setRandColor();
}

Collectable::Collectable(short id, sf::Vector2f position)
{
	this->id = id;
	type = COLLECTABLE;
	setSize(15, 30);
	pos = position;
	if (id == 0)
		vel = sf::Vector2f(0, 1);
	else
		vel = sf::Vector2f(.707, .707);
	setRandColor();
}

Collectable::Collectable(short id, float xPosition, float yPosition)
{
	this->id = id;
	type = COLLECTABLE;
	setSize(15, 30);
	pos.x = xPosition;
	pos.y = yPosition;
	if (id == 0)
		vel = sf::Vector2f(0, 1);
	else
		vel = sf::Vector2f(.707, .707);
	setRandColor();
}

void Collectable::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	if (outOfBounds(winSize) && (id == 0))
		del = true;
	else if (outOfBounds(winSize))
	{
		if (pos.x - size.x / 2 <= 0 || pos.x + size.x >= winSize.x)
			vel.x *= -1;
		if (pos.y - size.y / 2 <= 0 || pos.y + size.y >= winSize.y)
			vel.y *= -1;
	}
	for (int index = 0; index < objects->size(); index++)
	{
		if ((objects->at(index)->getType() == PLAYER) && (intersect(objects->at(index))))
			del = true;
	}
	
	objectUpdate(winSize, objects);
}