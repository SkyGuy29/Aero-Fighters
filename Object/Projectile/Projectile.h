#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();

protected:
	float angle, speed;
};