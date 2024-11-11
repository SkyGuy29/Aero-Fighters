#pragma once
#include "../Enemy.h"

class Boss : public Enemy
{
public:
	Boss();


	TickData tick() override;
	TickData attack() override;

	// The overridden collision method for enemies to handle children
	const CollisionType CollidesWith(ICollidable* other) const noexcept override
	{
		unsigned char c_index = 0;
		// Default to miss, only change if has collided in a different way
		CollisionType ret = CollisionType::MISS;

		if (other->getBounds().intersects(getBounds()))
			ret = CollisionType::HIT;

		while (ret != CollisionType::CHILD && c_index < children.size() && ret != CollisionType::HIT)
		{
			if (children.at(c_index).CollidesWith(other) == CollisionType::HIT)
			{
				child->damage();

				// Self collision takes precedence; manager damage the entity, parents damage children.
				ret = CollisionType::CHILD;
			}
		}

		return ret;
	}

private:
	std::vector<Enemy> children;

};
