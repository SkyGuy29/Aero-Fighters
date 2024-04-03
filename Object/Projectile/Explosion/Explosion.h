#pragma once
#include "../Projectile.h"
class Explosion : public Projectile
{
public:
	Explosion(sf::Vector2f pos, int type);

	void update(sf::Vector2u winSize, std::vector<Object*>*, bool time);
};

