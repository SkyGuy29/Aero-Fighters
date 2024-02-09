#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Enemy : public Object
{
public:
	Enemy(short);

	int getHealth() const;

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
private:
	int health = 1;
};

