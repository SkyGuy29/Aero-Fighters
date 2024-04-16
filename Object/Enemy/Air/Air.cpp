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
	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
	setSpriteNum(rand() % 20);
}

void Air::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	enemyUpdate(winSize, objects);
	//Do things here only if time is moving
	if(time)
	{
		switch (id)
		{
		case 0: //Default plane for the hangars
			setSpriteNum(15);
			break;
		case 1: //turning plane
			setSpriteNum(15);
			//change orientation for animation
			if (pos.y >= 0.1f * winSize.y)
			{
				if (left)
					vel.x -= 0.1;
				else
					vel.x += 0.1;
			}
			break;
		case 2: //flip and turn around
			setSpriteNum(17);
			//change orientation for animation
			if (pos.y >= 0.4f * winSize.y)
				vel.y -= 0.75;
			break;
		case 3: //mini chopper
			setSpriteNum(2);
			if (left)
			{
				if (pos.x < 0.1 * winSize.x)
					vel.x *= 0.9;
				else
				{
					vel.x += 0.1;
					vel.y += 0.4;
				}
			}
			else
				if (pos.x > 0.9 * winSize.x)
					vel.x *= 0.9;
				else
				{
					vel.x -= 0.1;
					vel.y += 0.4;
				}
			break;
		}
	}
}