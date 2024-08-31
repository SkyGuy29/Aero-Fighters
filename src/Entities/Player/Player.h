#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class Player :
    public Entity, public ICollidable
{
};