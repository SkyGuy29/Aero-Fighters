#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Enemy : public Object
{
public:
	int getHealth() const;

protected:
	int health;
};

