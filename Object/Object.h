#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
	virtual void update(sf::Vector2u winSize);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f pos, size;

	sf::RectangleShape sprite;
};