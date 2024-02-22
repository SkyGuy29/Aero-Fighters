#pragma once
#include "../Enemy.h"
class Air :
    public Enemy
{
public:
    Air(short id, sf::Vector2u winSize, std::vector<Object*>* objects);

    void update(sf::Vector2u winSize, std::vector<Object*>* objects);
private:
    bool targetP1 = true;
};