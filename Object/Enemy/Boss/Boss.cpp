#include "Boss.h"


Boss::Boss(short id, bool left, sf::Vector2f pos, sf::Vector2f vel,
std::vector<Object*>* objects) : Enemy::Enemy(id, left, pos, vel)
{
	type = BOSS;
	switch (id)
	{
	case 0: //England Boss
		setSize(32, 32);
		bossPiece1 = new Boss(1, left, pos, vel, objects);
		bossPiece2 = new Boss(2, left, pos, vel, objects);
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
}

void Boss::update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
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
		break;
	case 1: //England Boss Left Wing

		break;
	case 2: //England Boss Right Wing
		
		break;
	}
}