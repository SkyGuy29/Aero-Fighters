#include "Enemy.h"

Enemy::Enemy(const short id, const bool left, const sf::Vector2f pos, const sf::Vector2f vel, bool levelEditor)
{
	this->id = id;
	this->left = left;
	this->pos = pos;
	this->vel = vel;
	this->levelEditor = levelEditor;
}

int Enemy::getHealth() const
{
	return health;
}

void Enemy::enemyUpdate(const sf::Vector2f winSize, std::vector<Object*>* objects)
{
	texInit = false;
	objectUpdate(winSize, objects);
	nextFrame(3);

	if (!entered && (!outOfBounds(winSize) || levelEditor))
		entered = true;

	//Delete an enemy when it goes off screen
	if (outOfBounds(winSize) && entered)
		del = true;

	//
	// Go to spawn place
	// If the enemy has not yet entered the screen,
	// Knows the backgrounds position,
	// and the background is showing the enemies spawn position
	if (!entered && backgroundDist != nullptr && *backgroundDist <= startMark)
	{
		// Spawn the enemy by setting its position and velocity
		pos = spawnPos;
		if(!levelEditor)
			vel = spawnVel;
	}

	//Am I being shot?
	// For every entity
	for (int i = 0; i < objects->size(); i++)
	{
		// If the entity is a players projectile, is colliding with me, is not hidden, and is active
		if (objects->at(i)->getType() == PLAYER_PROJECTILE 
			&& this->intersect(objects->at(i)) && type != HIDDEN
			&& entered)
		{
			// Decrement my health
			health--;
		}
	}


	// Generates Collectable items when an enemy dies, presumably dropped items. - ricky
	// If i'm dead, not scheduled to be deleted, and not hidden
	if (health <= 0 && del == false && type != HIDDEN)
	{
		// Drop powerups based on my specific type
		switch (id)
		{
			// If i'm a boss
		case 1:
			// If i'm an Air Boss
			if (type == AIR)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;

		// If i'm a boss child entity
		case 2:
			// If i'm a land boss child entity
			if(type == LAND)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;

		//If i'm an explosion
		case 8:
			// If i'm a land explosion
			if(type == LAND)
				objects->push_back(new Collectable(0, pos, backgroundSpeed));
			del = true;
			break;

		// Otherwise do nothing
		default:
			del = true;
			break;
		}

		// Then spawn an explosion on my position
		objects->push_back(new Explosion(pos, 0));
	}
}