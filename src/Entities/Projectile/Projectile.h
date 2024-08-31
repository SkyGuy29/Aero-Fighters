#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class Projectile :
	public Entity, public ICollidable
{

};