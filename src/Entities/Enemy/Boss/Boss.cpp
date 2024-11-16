#include "Boss.h"

Entity::TickData Boss::tick()
{
	// Perform basic movement & animation
	Enemy::tick();

	for (auto& child : children)
	{
		child.tick();
	}

	return TickData();
}

Entity::TickData Boss::attack()
{
	return Enemy::attack();
}
