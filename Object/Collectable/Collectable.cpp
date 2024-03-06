#include "Collectable.h"

Collectable::Collectable(short id)
{
	this->id = id;
	type = COLLECTABLE;
	setSize(15, 20);
	sprite.setSize(sf::Vector2f(15, 20));
	sprite.setOrigin(sprite.getSize() / 2.f);
	pos.y = 0;
	pos.x = 100;
	if (id == 0)
		vel = sf::Vector2f(0, 1);
	else
		vel = sf::Vector2f(3.535, 3.535);
	setColor();
}

Collectable::Collectable(short id, sf::Vector2f position)
{
	this->id = id;
	type = COLLECTABLE;
	setSize(15, 20);
	sprite.setSize(sf::Vector2f(15, 20));
	sprite.setOrigin(sprite.getSize() / 2.f);
	pos = position;
	if (id == 0)
		vel = sf::Vector2f(0, 1);
	else
		vel = sf::Vector2f(3.535, 3.535);
	setColor();
}

Collectable::Collectable(short id, float xPosition, float yPosition)
{
	this->id = id;
	type = COLLECTABLE;
	setSize(15, 20);
	sprite.setSize(sf::Vector2f(15, 20));
	sprite.setOrigin(sprite.getSize() / 2.f);
	pos.x = xPosition;
	pos.y = yPosition;
	if (id == 0)
		vel = sf::Vector2f(0, 10);
	else
		vel = sf::Vector2f(3.535, 3.535);
	setColor();
}

void Collectable::setColor()
{
	switch (id)
	{
	case 0:
		sprite.setFillColor(sf::Color::Yellow);
		break;
	case 1:
		sprite.setFillColor(sf::Color::Blue);
		break;
	case 2:
		sprite.setFillColor(sf::Color::Black);
		break;
	default:
		sprite.setFillColor(sf::Color::Green);
		break;
	}
}

void Collectable::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	if (outOfBounds(winSize) && (id == 0))
		del = true;
	else if ((pos.y >= 240 || pos.y <= 30 || outOfBounds(winSize))
			&& id != 0)
	{
		if (pos.x <= 0)
		{
			pos.x = 0;
			vel.x *= -1;
		}
		else if (pos.x >= winSize.x)
		{
			pos.x = winSize.x;
			vel.x *= -1;
		}
		if (pos.y <= 30)
		{
			pos.y = 30;
			vel.y *= -1;
		}
		else if (pos.y >= 240)
		{
			pos.y = 240;
			vel.y *= -1;
		}
	}
	for (int index = 0; index < objects->size(); index++)
	{
		if ((objects->at(index)->getType() == PLAYER) && (intersect(objects->at(index))))
			del = true;
	}
	
	objectUpdate(winSize, objects);
}