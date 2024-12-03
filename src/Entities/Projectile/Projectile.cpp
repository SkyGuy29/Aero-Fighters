#include "Projectile.h"


Projectile::Projectile(ProjectilePrototype prototype, Entity* owner, Entity* target)
	: Entity(owner->getPosition() + prototype.SPAWN_POS, prototype.ID)
{ 
	// The projectile's velocity is set as it's spawned to move towards the nearest player
	if (prototype.FLAGS & 1 && target != nullptr)
	{
		float dx = target->getPosition().x - owner->getPosition().x;
		float dy = target->getPosition().y - owner->getPosition().y;
		
		//vel.x = dx/hypotf(dx,dy);
		//vel.y = dy/hypotf(dx,dy);
	}
	else
	{
		vel.x = prototype.SPAWN_VELOCITY.x;
		vel.y = prototype.SPAWN_VELOCITY.y;
	}

	this->owner = owner;
	ownerType = prototype.OWNER;
	float spawnX = prototype.SPAWN_POS.x + owner->getPosition().x;
	float spawnY = prototype.SPAWN_POS.y + owner->getPosition().y;
	setPosition(sf::Vector2f(spawnX, spawnY));
}


Entity::TickData Projectile::tick()
{
	move();
	return TickData();
}