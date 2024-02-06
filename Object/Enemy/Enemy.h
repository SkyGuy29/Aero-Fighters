#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Enemy : public Object
{
public:
	Enemy(short);

	int getHealth() const;

private:
	int health;
};

