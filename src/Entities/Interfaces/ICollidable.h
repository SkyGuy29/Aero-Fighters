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

	virtual const CollisionType CollidesWith(ICollidable* other) const noexcept
	{
		throw std::runtime_error("Default method called - ICollidable::CollidesWith");
	}
	virtual const sf::IntRect& getBounds() const noexcept
	{
		throw std::runtime_error("Default method called - ICollidable::getBounds");
	}
};

