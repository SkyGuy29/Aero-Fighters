#include "Enemy.h"

Enemy::Enemy(short id)
{
	this->id = id;
	type = 1;

	switch (id)
	{
	case 0:
		health = 100;
		setSize(25, 50);
		setRandColor();
		break;
	}
}

int Enemy::getHealth() const
{
	return health;
}

void Enemy::update(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	if (outOfBounds(winSize))
		del = true;

	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getType() == 3 && this->intersect(objects->at(i)))
		{
			health--;
		}
		if (health <= 0)
			del = true;
	}
}