#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Enemy : public Object
{
public:
	Enemy();

	int getHealth() const;

private:
	int health = 1;
};

