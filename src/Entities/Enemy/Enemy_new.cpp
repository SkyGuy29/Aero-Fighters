#include "Enemy_new.h"  


Enemy_new::Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, unsigned int line) :
	Entity(pos, ID), IHasHealth(ID), line(line)
{

}


void Enemy_new::tick()
{
	if (hasSpawned())
		move();
	if (hasSpawned() || getLevelEditor())
	{
		// Process next animation frame - subject to change
		nextFrame(3);

		// Default sprite size for an enemy is 32x32

	}
}
