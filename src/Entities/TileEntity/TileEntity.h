#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class TileEntity :
    public Entity, public ICollidable
{
};

