#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"
//#include "../../Utility/EntityData/EntityData.hpp"

// TODO add to this class
// tile entities are like enemies but a. dont move b. are non-collidable (they shoot though)
class TileEntity :
    public Entity, public IHasHealth, public ICollidable
{
public:
    TileEntity(EntityPrototype* prototype);

    TickData tick() override;

    const CollisionType collidesWith(ICollidable* other) const override
    {
        if (other->getBounds().intersects(getBounds()))
            return CollisionType::HIT;
        return CollisionType::MISS;
    }

    sf::FloatRect getBounds() const override
    {
        return sprite->getGlobalBounds();
    }
};