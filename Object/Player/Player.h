#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"
#include "../Projectile/StraightProjectile/StraightProjectile.h"

class Player : public Object
{
public:
	Player();
	Player(sf::Vector2f position);

	int getScore() const;

	int getLives() const;

	bool isAlive() const;

	void move(sf::Vector2f offset, sf::Vector2u winSize);

	void setPos(sf::Vector2f newPos);

	void shoot(std::vector<Projectile*>& proj);

	void update();

private:
	float speed = 5.f;

	int score = 0, lives = 0;

	int shootCoolDown = 0, shootCoolDownVal = 5;

	bool alive = true;
};

