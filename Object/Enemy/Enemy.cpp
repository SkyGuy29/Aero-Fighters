#include "Enemy.h"

int Enemy::getHealth() const
{
	return health;
}

int Enemy::numLikeMe(std::vector<Object*>* objects)
{
	int count = 0;

	while (objects->at(objects->size() - count - 1)->getType() == type
		&& objects->at(objects->size() - count - 1)->getId() == id)
	{
		count++;
	}

	return count;
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
			setRandColor();
		}
		
	}
	if (health <= 0 && del == false)
	{
		del = true;
	    objects->push_back(new Collectable(rand() % 4, pos));
		//Crashes when an enemy dies
	}
}