#include "Projectile_new.h"


Projectile_new::Projectile_new(ProjectilePrototype prototype, Entity* owner)
	: Entity(owner->getPosition() + prototype.SPAWN_POS, prototype.ID)
{
	// The projectile's velocity is set as it's spawned to move towards the nearest player
	if (prototype.FLAGS & 1)
	{
		float dx = prototype.SPAWN_POS.x - owner->getPosition().x;
		float dy = prototype.SPAWN_POS.y - owner->getPosition().y;
		vel.x = dx*prototype.SPAWN_VELOCITY.x/hypotf(dx,dy);
		vel.y = dy*prototype.SPAWN_VELOCITY.y/hypotf(dx,dy);
	}
	else
	{
		vel.x = prototype.SPAWN_VELOCITY.x;
		vel.y = prototype.SPAWN_VELOCITY.y;
	}

	this->owner = owner;
	ownerType = prototype.OWNER;
}


void Projectile_new::move()
{
	setPosition(getPosition() + vel);
}