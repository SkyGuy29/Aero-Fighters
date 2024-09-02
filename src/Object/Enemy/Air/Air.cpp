#include "Air.h"

Air::Air(const short id, bool left, float* backgroundDist, int startMark,
    sf::Vector2f winSize, std::vector<Object*>* objects, sf::Vector2f pos,
    sf::Vector2f vel, const bool levelEditor) : Enemy(id, left, sf::Vector2f(-100, -100),
    sf::Vector2f(0, 0), levelEditor)
{
	type = AIR;

	this->startMark = startMark;
	this->backgroundDist = backgroundDist;

	if (startMark == -1)
		entered = true;

	spawnPos = pos;
	spawnVel = vel;

	health = 1;
	
	// Default air entity size is 32x32
	setSize(32, 32);

	switch (id)
	{
	case 0: //baby copter
		setSpriteNum(0);
		setOrientation(8);
		chopperBlades = new Air(3, left, backgroundDist, startMark, winSize, 
		objects, pos, vel, levelEditor); //Creates the top
		objects->push_back(chopperBlades);
		break;
	case 3: //chopper blades
		setSpriteNum(19);
		health = 999;
		break;
	case 1: //big plane
		setSpriteNum(14);
		setSize(80, 80);
		health = 15;
		break;
	case 2: //spinny planes
		setSpriteNum(15);
		break;
	}

	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}

void Air::update(const sf::Vector2f winSize, std::vector<Object*>* objects, 
	const bool time)
{
	//Do things here only if time is moving
	if(time != 0)
	{
		switch (id)
		{
			//ENGLAND
		case 0: //baby copter
			if (shouldDelete())
				chopperBlades->flagDelete();
		case 3: //chopper blades
			if (entered)
			{
				vel.y *= 0.95f;
			}
		}
	enemyUpdate(winSize, objects);	
	}
}