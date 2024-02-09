#include "Collectable.h"

Collectable::Collectable(short id)
{
	this->id = id;
	type = 2;
	setSize(15, 30);
	pos.y = 0;
	pos.x = 100;
	setRandColor();
}

void Collectable::update(sf::Vector2u winSize)
{
	pos.y++;
	sprite.setPosition(pos);
	if (outOfBounds(winSize))
		del = true;
}