#include "Boss.h"

Entity::TickData Boss::tick()
{
	// Perform basic movement & animation
	Enemy::tick();

	//attack area
	Boss::attack();

	for (auto& child : children)
	{
		child.tick();
	}

	return TickData();
}

Entity::TickData Boss::attack()
{
	//if () //this got left unfinished, the urge to put if (false) again... -Christian
	//	vel.y -= getBackgroundSpeed();
	return Enemy::attack();
}
