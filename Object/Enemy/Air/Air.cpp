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
		sprite.setSize(sf::Vector2f(15, 25));
		setRandColor();

		switch (numLikeMe(objects) % 6)
		{
		case 0:
			setPos(sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, winSize.y * -0.25f));
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
		}

		setVel(0, 4);
		break;
	case 1: //turn left
	case 2: //turn right
		health = 1;
		setSize(15, 25);
		sprite.setSize(sf::Vector2f(15, 25));
		setRandColor();
		setPos(sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, winSize.y * -0.25f));

		setVel(0, 4);
		break;
	case 3: // Flip backwards formation of 4
		health = 1;
		setSize(15, 25);
		sprite.setSize(sf::Vector2f(15, 25));
		setRandColor();

		switch (numLikeMe(objects) % 4)
		{
		case 0:
			setPos(sf::Vector2f((rand() % 60 + 20) / 100. * winSize.x, winSize.y * -0.25f));
			break;
		case 1:
		case 2:
		case 3:
			setPos(objects->at(objects->size() - 1)->getPos()
				+ sf::Vector2f(-0.05f * winSize.y, -0.1f * winSize.y));
		}

		setVel(1, 7);
		break;
	case 4: //mini chopper left
		health = 1;
		setSize(15, 25);
		sprite.setSize(sf::Vector2f(15, 25));
		setRandColor();
		setPos(0 * winSize.x, 0.15 * winSize.y);

		setVel(4, 0);
		break;
	}
}

void Air::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	enemyUpdate(winSize, objects);

	switch (id)
	{
	case 1: //turn left
		if (pos.y >= 0.1f * winSize.y)
			vel.x -= 0.1;
		break;
	case 2: //turn right
		if (pos.y >= 0.1f * winSize.y)
			vel.x += 0.1;
		break;
	case 3: //flip and turn around
		if (pos.y >= 0.4f * winSize.y)
			vel.y -= 0.75;
		break;
	case 4: //mini chopper left
		if (vel.x > 0)
			vel.x -= 0.1 * pos.x;
		else
		{
			//vel.x += 0.1;
			vel.y += 0.4;
		}
		break;
	}
}