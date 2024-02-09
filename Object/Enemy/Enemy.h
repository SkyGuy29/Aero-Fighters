#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Enemy : public Object
{
public:
	Enemy(short);

	int getHealth() const;

	void update(sf::Vector2u winSize);
private:
	int health = 1;
};

