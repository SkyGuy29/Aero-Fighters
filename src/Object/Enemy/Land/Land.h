#pragma once
#include "../Enemy.h"
using ProjectileType = Projectile::ProjectileType;


class Land final : public Enemy
{
public:
    Land(short id, bool left, float* backgroundSpeed, sf::Vector2f winSize, 
    std::vector<Object*>* objects, sf::Vector2f pos, sf::Vector2f vel);

    void update(sf::Vector2f winSize, std::vector<Object*>* objects, 
		bool time) override;

private:
    Object* topPart = nullptr;
    bool target;
    float angle, magnitude;
    sf::Vector2f projVelocity, distance;
};