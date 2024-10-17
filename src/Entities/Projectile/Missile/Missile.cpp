#include "Missile.h"
#include <cmath>


void Missile::move()
{
	vel = {
		getPosition().x - target->getPosition().x,
		getPosition().y - target->getPosition().y
	};
	normalize();
}

void Missile::normalize()
{
	double normalizationFactor = magnitude / hypot<double>(vel.x, vel.y);

	vel = {
		static_cast<float>(vel.x * normalizationFactor),
		static_cast<float>(vel.y * normalizationFactor)
	};
}
