#pragma once

#include <vector>

#include "../Projectile/Projectile.h"
#include "../Projectile/Explosion/Explosion.h"
#include "../Collectable/Collectable.h"

class Player : public Object
{
public:
	Player();
	Player(short c, bool playerOne, float* bgSpeed);

	void shoot(std::vector<Object*>& objects);

	void special(std::vector<Object*>& objects, sf::Vector2u winSize);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);

	void move(sf::Vector2u winSize);

	bool getTime();

	void setHealth(short);

	short getHealth();

	short getSpecialCharge();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Projectile* movingProjectile = nullptr;
	bool isPlayerTwo;
	short timerDeath = 0;
	short country = -1;
	short specialCharge = 2;
	short powerLevel = 3;
	short invincibility = 0;
	short sideAnimation = 0;
	short cooldownSecondary = 0;
	short cooldownTime = 0;
};

