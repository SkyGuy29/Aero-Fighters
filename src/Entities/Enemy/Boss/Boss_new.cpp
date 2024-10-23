#include "Boss_new.h"

Entity::TickData Boss_new::tick()
{
	// Perform basic movement & animation
	Enemy_new::tick();

	for (auto& child : children)
	{
		child.tick();
	}
}
