#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player();
	Player(short c, bool playerOne);

	void shoot(std::vector<Object*>& objects);

	void special(std::vector<Object*>& objects, sf::Vector2u winSize);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Projectile* movingProjectile = nullptr;
	bool isPlayerTwo;
	short timer = 0;
	short country = -1;
	short specialCharge = 2;
	short powerLevel = 0;
	short invincibility = 0;
};

