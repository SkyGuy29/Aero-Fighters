#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();

	void update(sf::Vector2u winSize);

protected:
	const float PI = 3.14159, TO_RAD = PI / 180.f, TO_DEG = 180.f / PI;
};