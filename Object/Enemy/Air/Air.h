#pragma once
#include "../Enemy.h"
class Air :
    public Enemy
{
public:
    Air(short id);

    void update(sf::Vector2u winSize, std::vector<Object*>* objects);
};