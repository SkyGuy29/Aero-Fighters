#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player();

	void shoot(std::vector<Object*>& objects);

	void special(std::vector<Object*>& objects, sf::Vector2u winSize);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	short specialCharge = 2;
	short powerLevel = 0;
	int invincibility = 0;
};

