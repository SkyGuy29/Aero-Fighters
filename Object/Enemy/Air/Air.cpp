#include "Air.h"

Air::Air(short id, sf::Vector2u winSize, std::vector<Object*>* objects)
{
	this->id = id;
	type = AIR;

	switch (id)
	{
	case 0:
		//Fly straight down in formation of 6
		health = 1;
		setSize(15, 25);
		setRandColor();

		switch (numLikeMe(objects) % 6)
		{
		case 0:
			setPos(sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x , winSize.y * -0.25f));
			break;
		case 1:
			setPos(objects->at(objects->size() - 1)->getPos()
						+ sf::Vector2f(-0.05f * winSize.y, -0.1f * winSize.y));
			break;
		case 2:
		case 4:
		case 5:
			setPos(objects->at(objects->size() - 1)->getPos()
				+ sf::Vector2f(0.1f * winSize.y, 0));
			break;
		case 3:
			setPos(objects->at(objects->size() - 1)->getPos()
				+ sf::Vector2f(-0.15f * winSize.y, -0.1f * winSize.y));
			break;
		}

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