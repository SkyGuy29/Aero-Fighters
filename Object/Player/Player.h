#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player();

	void shoot(std::vector<Projectile*>& projs);

	void special();

	void update(sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	short country = -1;
};

