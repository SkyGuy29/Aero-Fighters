#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player(std::vector<Projectile*>*);

	void shoot();

	void special();

	void update(sf::Vector2u winSize);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Projectile*> projs;

	short country = -1;
};

