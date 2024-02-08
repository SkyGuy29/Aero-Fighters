#include "Collectable.h"

Collectable::Collectable(short id)
{
	this->id = id;
	setSize(15, 30);
	pos.y = 0;
	pos.x = 100;
	setRandColor();
}


int Collectable::getType()
{
	return 3;
}


void Collectable::update(sf::Vector2u winSize)
{
	pos.y++;
	sprite.setPosition(pos);
	if (outOfBounds(winSize))
		del = true;
}

void Collectable::intersect(Object* targetPtr)
{
	if ((abs(pos.x - targetPtr->getPos().x) <= (size.x / 2 + targetPtr->getSize().x / 2))
		&& (abs(pos.y - targetPtr->getPos().y) <= (size.y / 2 + targetPtr->getSize().y / 2)))
	{
		if (targetPtr->getType() == 0)
			del = true;
	}
}