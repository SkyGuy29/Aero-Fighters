#pragma once
#include "../Enemy.h"


class Air final : public Enemy
{
public:
    // Constructor
    Air(short id, bool left, float* backgroundDist, int startMark, 
		sf::Vector2f winSize, std::vector<Object*>* objects, sf::Vector2f pos, 
		sf::Vector2f vel);

    // Ticking Function
    void update(sf::Vector2f winSize, std::vector<Object*>* objects, 
    bool time) override;
private:
    // Child Chopper blades?
    Object* chopperBlades = nullptr;
};