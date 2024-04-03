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

	void update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);

	void move(sf::Vector2u winSize);

	bool getTime();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Projectile* movingProjectile = nullptr;
	bool isPlayerTwo;
	short timer = 0;
	short country = -1;
	short specialCharge = 2;
	short powerLevel = 0;
	short invincibility = 0;
	short sideAnimation = 0;
	short cooldownSecondary = 0;
	short cooldownTime = 0;
};

