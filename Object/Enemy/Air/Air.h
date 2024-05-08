#pragma once
#include "../Enemy.h"

class Air : public Enemy
{
public:
    Air(short id, bool left, float* backgroundDist, int startMark, 
    sf::Vector2u winSize, std::vector<Object*>* objects, sf::Vector2f pos, 
    sf::Vector2f vel);

    void update(sf::Vector2u winSize, std::vector<Object*>* objects, 
    bool time);
private:
    Object* chopperBlades = nullptr;
};