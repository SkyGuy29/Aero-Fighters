#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player(int country);

	void shoot(std::vector<Object*>& objects);

	void special(std::vector<Object*>& objects, sf::Vector2u winSize);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);

	void setCountry(short);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	short country = 0;
	short specialCharge = 2;
	short powerLevel = 0;
	int invincibility = 0;
};

