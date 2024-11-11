#pragma once
#include "../Projectile.h"


// target closest enemy; 3 hits til death?
// possibly pass a stack of enemies to target?
class Missile : public Projectile
{
public:
	Missile(ProjectilePrototype prototype, Entity* owner, Entity* target)
		: Projectile(prototype, owner)
	{
		this->target = target;
	}

	void move() override;
private:
	Entity* target;
	int magnitude; // Do something with this andrew


	void normalize(sf::Vector2f newVel);
};

