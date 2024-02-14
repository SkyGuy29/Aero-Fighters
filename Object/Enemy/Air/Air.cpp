#include "Air.h"

Air::Air(short id)
{
	this->id = id;
	type = AIR;

	switch (id)
	{
	case 0:
		health = 100;
		setSize(25, 50);
		setRandColor();
		break;
	}
}

void Air::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	if (outOfBounds(winSize))
		del = true;

	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getType() == PLAYER_PROJECTILE && this->intersect(objects->at(i)))
		{
			health--;
			objects->at(i)->setDelete();
			setRandColor();
		}
		if (health <= 0)
			del = true;
	}
}