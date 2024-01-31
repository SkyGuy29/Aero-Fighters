#pragma once

#include "Projectile.h"

class Player : public sf::Drawable
{
public:
	Player();

	int getScore() const;

	int getLives() const;

	bool isAlive() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int score = 0, lives = 0;

	bool alive = true;
};

