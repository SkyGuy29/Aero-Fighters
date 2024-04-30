#include "Boss.h"


Boss::Boss(short id, bool left, float* backgroundDist, int startMark, sf::Vector2u winSize, std::vector<Object*>* objects,
	sf::Vector2f pos, sf::Vector2f vel) : Enemy(id, left, sf::Vector2f(-100, -100), sf::Vector2f(0, 0))
{
	type = BOSS;

	this->startMark = startMark;
	this->backgroundDist = backgroundDist;

	if (startMark == -1)
		entered = true;

	spawnPos = pos;
	spawnVel = vel;

	switch (id)
	{
	case 0: //England Boss
		setSize(32, 32);
		bossPiece1 = new Boss(1, left, backgroundDist, startMark, winSize, objects, pos, vel);
		bossPiece2 = new Boss(2, left, backgroundDist, startMark, winSize, objects, pos, vel);
		objects->push_back(bossPiece1);
		objects->push_back(bossPiece2);
		health = 100;
		break;
	case 1: //England Boss Left Wing
		setSize(32, 32);
		health = 50;
		break;
	case 2: //England Boss Right Wing
		setSize(32, 32);
		health = 50;
		break;
	}

	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}

void Boss::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
{
	switch (id)
	{
	case 0: //England Boss
		if (!cooldown)
		{
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(3, 0), 
			sf::Vector2f(10, 10), 1, false, 0, 15));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(3, 0),
			sf::Vector2f(10, 10), 1, false, 0, 30, 15));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(3, 0),
			sf::Vector2f(10, 10), 1, false, 0, 60, 15));
			cooldown = 300;
		}
		if (!cooldown2)
		{
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(5, 0),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(4.830, -1.294),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(4.83, 1.294),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(5, 0),
			sf::Vector2f(0, 0), 1, false, 0, 25, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(4.830, -1.294),
			sf::Vector2f(0, 0), 1, false, 0, 25, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(4.83, 1.294),
			sf::Vector2f(0, 0), 1, false, 0, 25, 11));
			cooldown2 = 250;
		}
		if (!cooldown3)
		{
			objects->push_back(new Projectile(pos.x + 8, pos.y, sf::Vector2f(4.830, 1.294),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(4.830, 1.294),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			objects->push_back(new Projectile(pos.x - 8, pos.y, sf::Vector2f(4.830, -1.294),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(4.830, -1.294),
			sf::Vector2f(0, 0), 1, false, 0, 11));
			cooldown3 = 200;
		}
		break;
	case 1: //England Boss Left Wing
		if(!cooldown)
			switch(pattern)
			{
			case 0:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(3, 0),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-3, 0),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(0, 3),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(0, -3),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 1;
				cooldown = 50;
				break;
			case 1:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.707, .707),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-0.707, .707),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-0.707, -0.707),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.707, -0.707),
				sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 2;
				cooldown = 50;
				break;
			case 2:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.866, .5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.866, .5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.866, -.5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.866, -.5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 3;
				cooldown = 50;
				break;
			case 3:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.966, .259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.966, .259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.966, -.259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.966, -.259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 0;
				cooldown = 200;
				break;
			}
		break;
	case 2: //England Boss Right Wing
		if(!cooldown)
			switch (pattern)
			{
			case 0:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(3, 0),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-3, 0),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(0, 3),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(0, -3),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 1;
				cooldown = 50;
				break;
			case 1:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.707, .707),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-0.707, .707),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-0.707, -0.707),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.707, -0.707),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 2;
				cooldown = 50;
				break;
			case 2:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.866, .5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.866, .5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.866, -.5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.866, -.5),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 3;
				cooldown = 50;
				break;
			case 3:
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.966, .259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.966, .259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(-.966, -.259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				objects->push_back(new Projectile(pos.x, pos.y, sf::Vector2f(.966, -.259),
					sf::Vector2f(14, 14), 6, false, 0, 13));
				pattern = 0;
				cooldown = 200;
				break;
			}
		break;
	enemyUpdate(winSize, objects);

	//Do things here only if time is moving
	if (time)
	{
		switch (id)
		{
		case 0: //England Boss
			if (!cooldown)
			{
				objects->push_back(new Projectile(pos.x, pos.y,
					sf::Vector2f(2.5, 2.5), sf::Vector2f(10, 10), 1,
					false, 0, 11));
				cooldown = 100;
			}
		case 1: //England Boss Left Wing
		case 2: //England Boss Right Wing
			vel.y *= 0.99;
		}
	}
}