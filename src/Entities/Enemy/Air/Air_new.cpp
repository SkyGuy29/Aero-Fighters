#include "Air_new.h"


Air_new::Air_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, int* backgroundSpeed, unsigned char orientation = 0) :
	Enemy_new(pos, vel, ID, backgroundSpeed, orientation)
{
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