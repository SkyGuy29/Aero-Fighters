#pragma once
#include "Enemy_new.h"
#include "../Interfaces/ICollidable.h"

class EnemyCollidable :
    public Enemy, public ICollidable
{
};