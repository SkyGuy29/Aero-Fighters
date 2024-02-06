#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();

	void update(sf::Vector2u winSize);

	bool shouldDelete();

protected:
	float angle, speed;

	bool del = false;

	const float PI = 3.14159, TO_RAD = PI / 180.f, TO_DEG = 180.f / PI;
};