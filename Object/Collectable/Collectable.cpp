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

void Collectable::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	pos.y++;
	sprite.setPosition(pos);
	if (outOfBounds(winSize))
		del = true;
	for (int index = 0; index < objects->size(); index++)
	{
		if ((objects->at(index)->getType() == 0) && (intersect(objects->at(index))))
			del = true;
	}
}