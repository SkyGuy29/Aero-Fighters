#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"

class Enemy :
    public Entity, public ICollidable
{
};