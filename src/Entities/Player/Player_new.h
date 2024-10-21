#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"
#include "../../ControllerStuff.hpp"


class Player_new :
    public Entity, public IHasHealth
{
public:
    Player_new(sf::Vector2f pos, EntityID ID,
        int* backgroundSpeed, unsigned char orientation = 0
    );

    void tick();
    void setHealth(short h) { health = h; };

private:

};