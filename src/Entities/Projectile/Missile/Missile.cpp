#include "Missile.h"
#include <cmath>

using PI = std::numbers::pi_v;

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
	double normalizationFactor = magnitude / hypot<double>(vel.x, vel.y);

	
	if (newVel.x != 0)
	{
		if ( atan(newVel.y / newVel.x) * 180.f/3.14159f)
		{
			vel = {
				static_cast<float>(vel.x * normalizationFactor),
				static_cast<float>(vel.y * normalizationFactor)
			};
		}
	}
}
