#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"
#include "../Projectile/Explosion/Explosion.h"
#include "../Collectable/Collectable.h"

class Enemy : public Object
{
public:
	// Constructor
	Enemy(short, bool, sf::Vector2f, sf::Vector2f, bool);

	// Returns the enemies health
	int getHealth() const;

	// Enemy ticking function
	void enemyUpdate(sf::Vector2f winSize, std::vector<Object*>* objects, int& p1Score, int& p2Score);
protected:
	// Enemies health
	int health;

	// Starting Y position
	int startMark;
	// Has entered frame
	bool entered = false;
	bool levelEditor = false;
	// never used in base class
	bool left;

	sf::Vector2f spawnPos, spawnVel;
};

