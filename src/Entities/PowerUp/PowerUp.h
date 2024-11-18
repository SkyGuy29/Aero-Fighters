#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"


// TODO
class PowerUp final :
	public Entity, public ICollidable
{
public:
	PowerUp(sf::Vector2f spawnPos, EntityID id) :	Entity(spawnPos, id) {};
	~PowerUp() override = default;
    TickData tick() override;


	sf::IntRect getBounds() const noexcept override
	{
		return sprite->getTextureRect();
	}
};

