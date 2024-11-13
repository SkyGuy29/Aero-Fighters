#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
//#include "../../Utility/EntityData/EntityData.hpp"

// TODO add to this class
class TileEntity :
    public Entity, public ICollidable
{
public:
    TileEntity(EntityPrototype* prototype);

    TickData tick() override;

    const CollisionType collidesWith(ICollidable* other) const override;
    const sf::IntRect& getBounds() const override;
};