#include "Enemy.h"

Enemy::Enemy(short id)
{
	this->id = id;

	switch (id)
	{
	case 0:
		health = 1;
		break;
	}
}


int Enemy::getHealth() const
{
	return health;
}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}