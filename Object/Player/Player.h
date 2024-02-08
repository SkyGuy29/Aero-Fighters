#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player();

	void shoot();

	void update(sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Projectile*> projs;

	short country = -1;
};

