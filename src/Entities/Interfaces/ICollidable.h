#pragma once

class ICollidable
{
public:
	virtual const bool CollidesWith(ICollidable* other) const noexcept = 0;
	virtual const sf::IntRect& getBounds() const noexcept = 0;
};

