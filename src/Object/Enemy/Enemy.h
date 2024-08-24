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

	void enemyUpdate(sf::Vector2f winSize, std::vector<Object*>* objects);
protected:
	int health, startMark;
	bool entered = false;
	bool left;

	sf::Vector2f spawnPos, spawnVel;
};

