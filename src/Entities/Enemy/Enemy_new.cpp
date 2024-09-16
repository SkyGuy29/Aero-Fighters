#include "Enemy_new.h"  


Enemy_new::Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, float* backgroundSpeed, unsigned char orientation = 0) :
	backgroundSpeed(backgroundSpeed), Entity(pos, ID, orientation), IHasHealth(ID)
{
	enemies.push_back(this);
}


void Enemy_new::tick()
{
	nextFrame(3);

	if (!entered && (onScreen() || getLevelEdtior()))
		entered = true;

	//Delete an enemy when it goes off screen
	//if (!onScreen() && entered)
	//	delete this; Do in level

	// Go to spawn place
	// If the enemy has not yet entered the screen,
	// Knows the backgrounds position,
	// and the background is showing the enemies spawn position
	
	/*if (!entered)
	{
		// Spawn the enemy by setting its position and velocity
		sprite.setPosition(pos);
		if (!levelEditor)
			vel = spawnVel;
	}*/

	/*// Am I being shot? // move to collidab le
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
	}*/


	// Generates Collectable items when an enemy dies, presumably dropped items. - ricky
	// If i'm dead, not scheduled to be deleted, and not hidden
	/*if (health <= 0 && del == false && type != HIDDEN) // do in collidable
	{
		// Drop powerups based on my specific type
		switch (id)
		{
			// If i'm a ___
		case 1:
			// If i'm an Air ___
			if (type == AIR)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;

			// If i'm a ___
		case 2:
			// If i'm a land ___
			if (type == LAND)
				objects->push_back(new Collectable(1, pos, backgroundSpeed));
			del = true;
			break;

			//If i'm an ___
		case 8:
			// If i'm a land ___
			if (type == LAND)
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
	}*/
}
