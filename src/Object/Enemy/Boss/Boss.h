#pragma once
#include "../Enemy.h"
using ProjectileType = Projectile::ProjectileType;


class Boss final :
    public Enemy
{
public:
    Boss(short id, bool left, sf::Vector2f pos, sf::Vector2f vel,
        std::vector<Object*>* objects, bool levelEditor);

    void update(sf::Vector2f winSize, std::vector<Object*>* objects, 
        bool time) override;
private:
    Boss* bossPiece1 = nullptr;
    Boss* bossPiece2 = nullptr;
    Boss* bossPiece3 = nullptr;
    short pattern = 0;
    short cooldown2 = 250;
    short cooldown3 = 0;
};

