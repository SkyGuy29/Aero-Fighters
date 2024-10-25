#pragma once
#include "../Projectile_new.h"


// target closest enemy; 3 hits til death?
// possibly pass a stack of enemies to target?
class Missile : public Projectile_new
{
public:
	Missile(ProjectilePrototype prototype, Entity* owner, Entity* target)
		: Projectile_new(prototype, owner)
	{
		this->target = target;
	}

	void move() override;
private:
	Entity* target;
	int magnitude; // Do something with this andrew


	void normalize(sf::Vector2f newVel);
};

