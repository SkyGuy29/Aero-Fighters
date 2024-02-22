#include "Air.h"

Air::Air(short id, sf::Vector2u winSize, std::vector<Object*>* objects)
{
	this->id = id;
	type = AIR;

	switch (id)
	{
	case 0:
		//Fly straight down
		health = 1;
		setSize(15, 25);
		setRandColor();
		if (objects->at(objects->size() - 1)->getType() == AIR
			&& objects->at(objects->size() - 1)->getId() == 0)
		{
			setPos(objects->at(objects->size() - 1)->getPos()
				+ sf::Vector2f(0, -0.25f * winSize.y));
		}
		else
			setPos(sf::Vector2f(winSize.x * 0.5f, winSize.y * -0.25f));
		setVel(0, 4);
		break;
	}
}

void Air::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	int t;

	enemyUpdate(winSize, objects);

	if (targetP1)
		t = 0;
	else
		t = 1;

	
}