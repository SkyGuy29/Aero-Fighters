#pragma once
#include <stdexcept>
#include <SFML/Graphics/Rect.hpp>

class ICollidable
{
public:
	virtual ~ICollidable() = default;

	enum class CollisionType : unsigned char
	{
		HIT,
		MISS,
		CHILD
	};

	// these should be overriden
	virtual const CollisionType collidesWith(ICollidable* other) const
	{
		throw std::runtime_error("Default method called - ICollidable::collidesWith");
	}

	[[nodiscard]] virtual sf::IntRect getBounds() const
	{
		throw std::runtime_error("Default method called - ICollidable::getBounds");
	}
};

