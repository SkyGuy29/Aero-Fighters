#include "Air.h"

Air::Air(short id, bool left, float* backgroundDist, int startMark, sf::Vector2u winSize, std::vector<Object*>* objects,
	sf::Vector2f pos, sf::Vector2f vel) : Enemy(id, left, sf::Vector2f(-100, -100), sf::Vector2f(0, 0))
{
	type = AIR;

	this->startMark = startMark;
	this->backgroundDist = backgroundDist;

	if (startMark == -1)
		entered = true;

	spawnPos = pos;
	spawnVel = vel;

	health = 1;
	setSize(32, 32);

	switch (id)
	{
	case 0: //baby copter
		setSpriteNum(0);
		break;
	case 1: //big plane
		setSpriteNum(14);
		setSize(80, 80);
		break;
	case 2: //spinny planes
		setSpriteNum(15);
		break;
	}

	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}

void Air::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	enemyUpdate(winSize, objects);
	//Do things here only if time is moving
	if(time != 0)
	{
		switch (id)
		{
			//ENGLAND
		case 0: //baby copter
			if (entered)
			{
				vel.y *= 0.95;
			}
		}
	}
}