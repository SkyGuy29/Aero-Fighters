#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f pos, size = sf::Vector2f(100, 200);

	sf::RectangleShape sprite = sf::RectangleShape(size);
};

