#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"
//#include "../../Utility/EntityData/EntityData.hpp"

// TODO add to this class
// tile entities are like enemies but a. dont move b. are non-collidable (they shoot though)
class TileEntity :
    public Entity, public IHasHealth
{
public:
    TileEntity(EntityPrototype* prototype);

    TickData tick() override;
};