#pragma once
#include "../Enemy.h"
class Land :
    public Enemy
{
public:
    Land(short id, bool left, float* backgroundSpeed, sf::Vector2u winSize, std::vector<Object*>* objects,
        sf::Vector2f pos, sf::Vector2f vel);

    void update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);

private:
    Object* topPart = nullptr;
    float* backgroundSpeed = nullptr;
    bool target;
    float angle, magnitude;
    sf::Vector2f projVelocity, distance;
};