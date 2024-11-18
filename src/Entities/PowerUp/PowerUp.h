#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"


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


	sf::IntRect getBounds() const noexcept override
	{
		return sprite->getTextureRect();
	}
private:
	sf::Vector2f vel;
	short bounces = 0;
};

