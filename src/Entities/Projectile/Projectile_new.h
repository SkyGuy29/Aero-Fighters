#pragma once
#include "../../Utility/EntityID.h"
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../../Utility/EntityData/ProjectilePrototype.h"


class Projectile_new :
	public Entity, public ICollidable
{
public:
	Projectile_new(const ProjectilePrototype prototype, Entity* owner);

	void tick() override;
	virtual void move();
private:
	ProjectilePrototype::Owner ownerType;
	Entity* owner;
};