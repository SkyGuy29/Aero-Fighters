#pragma once
#include "../Enemy.h"

class Boss : public Enemy
{
public:
	Boss();


	TickData tick() override;
	TickData attack() override;
	//Boss(short id, bool left, sf::Vector2f pos, sf::Vector2f vel,
		//std::vector<Object*>* objects, bool levelEditor);

	//void update(sf::Vector2f winSize, std::vector<Object*>* objects,
		//bool time, int& p1Score, int& p2Score) override;

	// The overridden collision method for enemies to handle children
	const CollisionType collidesWith(ICollidable* other) const noexcept override
	{
		unsigned char c_index = 0;
		// Default to miss, only change if has collided in a different way
		CollisionType ret = CollisionType::MISS;

		if (other->getBounds().intersects(getBounds()))
			ret = CollisionType::HIT;

		while (ret != CollisionType::CHILD && c_index < children.size() && ret != CollisionType::HIT)
		{
			if (children.at(c_index).collidesWith(other) == CollisionType::HIT)
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
	//Boss* bossPiece1 = nullptr;
	//Boss* bossPiece2 = nullptr;
	//Boss* bossPiece3 = nullptr;
	short pattern = 0;
	short cooldown2 = 250;
	short cooldown3 = 0;
	short timer = 0;
};
