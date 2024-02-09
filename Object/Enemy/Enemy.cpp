#include "Enemy.h"

Enemy::Enemy(short id)
{
	this->id = id;
	type = 1;

	switch (id)
	{
	case 0:
		health = 1;
		setSize(25, 50);
		break;
	}
}

int Enemy::getHealth() const
{
	return health;
}

void Enemy::update(sf::Vector2u winSize)
{
	if (outOfBounds(winSize))
		del = true;
}