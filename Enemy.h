#pragma once

#include "Projectile.h"

class Enemy : public sf::Drawable
{
public:
	Enemy();

	int getHealth() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int health = 1;
};

