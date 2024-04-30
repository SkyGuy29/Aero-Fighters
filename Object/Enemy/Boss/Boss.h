#pragma once
#include "../Enemy.h"

class Boss :
    public Enemy
{
public:
    Boss(short id, bool left, sf::Vector2f pos, 
       sf::Vector2f vel, std::vector<Object*>* objects);

    void update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);
private:
    Boss* bossPiece1;
    Boss* bossPiece2;
    short pattern = 0;
    short cooldown2 = 250;
    short cooldown3 = 0;
};

