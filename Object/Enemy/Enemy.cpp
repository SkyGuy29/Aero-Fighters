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

void Enemy::enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects)
{
	texInit = false;
	objectUpdate(winSize, objects);
	nextFrame(3);

	if (!entered && !outOfBounds(winSize))
		entered = true;

	if (outOfBounds(winSize) && entered)
		del = true;

	//Go to spawn place
	if (!entered && backgroundDist != nullptr && *backgroundDist <= startMark)
	{
		pos = spawnPos;
		vel = spawnVel;
	}

	//Am I being shot?
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getType() == PLAYER_PROJECTILE 
			&& this->intersect(objects->at(i)) && type != HIDDEN
			&& entered)
		{
			health--;
		}
		
	}
	if (health <= 0 && del == false && type != HIDDEN)
	{
		switch (id)
		{
		case 1:
			if (type == AIR)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;
		case 2:
			if(type == LAND)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;
		case 8:
			if(type == LAND)
				objects->push_back(new Collectable(0, pos, backgroundSpeed));
			del = true;
			break;
		default:
			del = true;
			break;
		}
		objects->push_back(new Explosion(pos, 0));
	}
}