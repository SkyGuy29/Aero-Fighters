#include "Missile.h"
#include <cmath>
#include <numbers>

#define DEG 180.f / std::numbers::pi_v<long double>

void Missile::move()
{
	sf::Vector2f newVel = {
		getPosition().x - target->getPosition().x,
		getPosition().y - target->getPosition().y
	};

	normalize(newVel);
}

void Missile::normalize(sf::Vector2f newVel)
{
	double normalizationFactor = magnitude / std::hypot<double>(vel.x, vel.y);
	float degreesNew = atan(newVel.y / newVel.x) * DEG;
	float degreesOld = atan(vel.y / vel.x)       * DEG;
	
	if (newVel.x != 0)
	{
		if (degreesOld - degreesNew > 180 && degreesOld - degreesNew < 360)
		{
			vel = {
				static_cast<float>(vel.x * normalizationFactor),
				static_cast<float>(vel.y * normalizationFactor)
			};
		}
	}
}
