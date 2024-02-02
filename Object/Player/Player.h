#pragma once

#include "../Object.h"
#include "../Projectile/Projectile.h"

class Player : public Object
{
public:
	Player();
	Player(sf::Vector2f position);

	int getScore() const;

	int getLives() const;

	bool isAlive() const;

	void move(sf::Vector2f offset, sf::Vector2u winSize);

	void shoot(std::vector<Projectile*>& prog);

private:
	float speed = 5.f;

	int score = 0, lives = 0;

	bool alive = true;
};

