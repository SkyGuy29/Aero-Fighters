#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Enemy : public Object
{
public:
	int getHealth() const;

	void enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects);

protected:
	int health;
	bool entered = false;
};

