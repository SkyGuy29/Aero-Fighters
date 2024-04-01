#include "Enemy.h"

Enemy::Enemy(short id, bool left, sf::Vector2f pos, sf::Vector2f vel)
{
	this->id = id;
	this->left = left;
	this->pos = pos;
	this->vel = vel;
}

int Enemy::getHealth() const
{
	return health;
}

void Enemy::enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects, bool time)
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
		if(rand() % 20 == 0)
			objects->push_back(new Collectable(rand() % 4, pos));
	    objects->push_back(new Explosion(pos, 0));
		//Crashes when an enemy dies
	}
}