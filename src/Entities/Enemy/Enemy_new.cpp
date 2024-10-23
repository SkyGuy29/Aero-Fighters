#include "Enemy_new.h"  


Enemy_new::Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, unsigned int line) :
	Entity(pos, ID), IHasHealth(ID)
{
	this->line = line;
}


Entity::TickData Enemy_new::tick()
{
	if (hasSpawned())
	{
		move();
		// Process next animation frame - subject to change
		nextFrame(3);

		if (curCooldown > 0)
			--curCooldown;
	}
}

Entity::TickData Enemy_new::attack()
{
	// Map IDs to attacks here, return information.
}
