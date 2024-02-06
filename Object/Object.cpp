#include "Object.h"


void Object::update(sf::Vector2u winSize)
{
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

bool Object::shouldDelete()
{
	return false;
}