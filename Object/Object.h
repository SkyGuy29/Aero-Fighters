#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
	virtual void update(sf::Vector2u winSize);

	bool shouldDelete();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool intersect();

	short id, rotation, cooldown;

	bool del;

	sf::Vector2f pos, size, velocity;

	sf::RectangleShape sprite;
};