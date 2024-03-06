#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"
#include "../Collectable/Collectable.h"

class Enemy : public Object
{
public:
	Enemy(short, bool, sf::Vector2f, sf::Vector2f);

	int getHealth() const;

	void enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects);

protected:
	int health;
	bool entered = false;
	bool left;
};

