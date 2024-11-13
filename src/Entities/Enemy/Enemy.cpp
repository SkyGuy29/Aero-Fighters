#include "Enemy.h"  


Enemy::Enemy(sf::Vector2f pos, sf::Vector2f vel,
             EntityID ID, unsigned int line) :
	Entity(pos, ID), IHasHealth(ID)
{
	this->line = line;
}


Enemy::~Enemy()
{

}

Entity::TickData Enemy::tick()
{
	if (hasSpawned())
	{
		move();
		// Process next animation frame - subject to change
		nextFrame(3);

		if (curCooldown > 0)
			--curCooldown;
	}
	return TickData();
}

Entity::TickData Enemy::attack()
{
	// Map IDs to attacks here, return information.
	return TickData();
}
