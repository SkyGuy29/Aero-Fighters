#include "Enemy_new.h"  


Enemy_new::Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, unsigned char orientation) :
	Entity(pos, ID, orientation), IHasHealth(ID)
{

}


void Enemy_new::tick()
{
	if (hasSpawned() || getLevelEditor())
	{
		// Process next animation frame - subject to change
		nextFrame(3);

		// Default sprite size for an enemy is 32x32

	}
}
