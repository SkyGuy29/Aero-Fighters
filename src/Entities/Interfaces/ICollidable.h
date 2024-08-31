#pragma once

#include "../Entity.h"

class ICollidable
{
public:
	virtual inline const bool CollidesWith(Entity& other) noexcept = 0;
private:
	struct Vec2UC
	{
		unsigned char x, y;
	};

	Vec2UC bounds;
};

