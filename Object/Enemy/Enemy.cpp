#include "Enemy.h"

int Enemy::getHealth() const
{
	return health;
}

void Enemy::enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	objectUpdate(winSize, objects);

	if (!entered && !outOfBounds(winSize))
		entered = true;

	if (outOfBounds(winSize) && entered)
		del = true;

	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getType() == PLAYER_PROJECTILE && this->intersect(objects->at(i)))
		{
			health--;
			objects->at(i)->setDelete();
			setRandColor();
		}
		if (health <= 0)
			del = true;
	}
}