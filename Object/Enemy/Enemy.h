#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"
#include "../Projectile/Explosion/Explosion.h"
#include "../Collectable/Collectable.h"

class Enemy : public Object
{
public:
	Enemy(short, bool, sf::Vector2f, sf::Vector2f);

	int getHealth() const;

	void enemyUpdate(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);

protected:
	int health;
	bool entered = false;
	bool left;
};

