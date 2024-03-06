#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"
#include "../Collectable/Collectable.h"

class Enemy : public Object
{
public:
	int getHealth() const;
	int numLikeMe(std::vector<Object*>* objects);

	void enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects);

protected:
	int health;
	bool entered = false;
	bool left;
};

