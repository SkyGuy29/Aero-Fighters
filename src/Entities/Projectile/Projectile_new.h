#pragma once
#include "../../Utility/EntityID.h"
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class Projectile_new :
	public Entity, public ICollidable
{
public:
	Projectile_new() = default;
	Projectile_new& operator=(const EntityDataStorage::ProjectilePrototype rhs)
	{
		// @TODO ADD CODE HERE
	}


private:
};