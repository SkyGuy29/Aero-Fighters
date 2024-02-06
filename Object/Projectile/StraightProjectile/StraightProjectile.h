#pragma once

#include "../Projectile.h"

class StraightProjectile : public Projectile
{
public:
	StraightProjectile(sf::Vector2f pos, float angle, float speed);

	void update(sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};