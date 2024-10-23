#pragma once

class ICollidable
{
public:
	enum class CollisionType : unsigned char
	{
		HIT,
		MISS,
		CHILD
	};

	virtual const CollisionType CollidesWith(ICollidable* other) const noexcept = 0;
	virtual const sf::IntRect& getBounds() const noexcept = 0;
};

