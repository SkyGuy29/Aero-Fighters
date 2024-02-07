#pragma once

#include <vector>

#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player();
	Player(sf::Vector2f pos, sf::Vector2u winSize);
	Player(float posX, float posY, sf::Vector2u winSize);

	void shoot();

	void update(sf::Vector2u winSize);


private:
	std::vector<Projectile*> projs;

	float vel = 5.f;
	short cooldownVal = 2, country = -1;
};

