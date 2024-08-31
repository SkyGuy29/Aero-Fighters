#pragma once
#include "Enemy.h"
#include "../Interfaces/ICollidable.h"

class EnemyCollidable :
    public Enemy, public ICollidable
{
};