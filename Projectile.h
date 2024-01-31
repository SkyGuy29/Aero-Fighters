#pragma once

#include <SFML/Graphics.hpp>

class Projectile : public sf::Drawable
{
public:
	Projectile();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f pos;
	float angle, speed;
};

