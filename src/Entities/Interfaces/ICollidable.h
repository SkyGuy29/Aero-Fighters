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

	[[nodiscard]] virtual sf::IntRect getBounds() const
	{
		throw std::runtime_error("Default method called - ICollidable::getBounds");
	}
};

