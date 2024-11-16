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

	virtual const CollisionType collidesWith(ICollidable* other) const
	{
		throw std::runtime_error("Default method called - ICollidable::collidesWith");
	}

	[[nodiscard]] virtual const sf::IntRect& getBounds() const
	{
		throw std::runtime_error("Default method called - ICollidable::getBounds");
	}
};

