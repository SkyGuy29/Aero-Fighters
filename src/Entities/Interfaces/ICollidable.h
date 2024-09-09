#pragma once
#include "../Entity.h"

class Entity;

class ICollidable
{
public:
	virtual const bool CollidesWith(Entity* other) noexcept = 0;

protected:
	struct Vec2UC
	{
		unsigned char x, y;
	};

	Vec2UC bounds;
};

