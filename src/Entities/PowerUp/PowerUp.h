#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Player/Player.h"


// TODO
class PowerUp final :
	public Entity, public ICollidable
{
public:
	//:	Entity(spawnPos, id) {}
	PowerUp(sf::Vector2f spawnPos, EntityID id);
	~PowerUp() override = default;

	void interceptBarrier();
	
    
	TickData tick() override;

	const CollisionType collidesWith(ICollidable* other) const noexcept override;

	sf::FloatRect getBounds() const noexcept override
	{
		return sprite->getGlobalBounds();
	}
private:
	sf::Vector2f vel = sf::Vector2f(1, 1);
	short bounces = 0;
};

//to do, implement collides with into entity management interface. talk with ricky about this.