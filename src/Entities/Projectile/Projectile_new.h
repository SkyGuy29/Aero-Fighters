#pragma once
#include "../../Utility/EntityID.h"
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class Projectile_new :
	public Entity, public ICollidable
{
	Projectile_new() = default;
};