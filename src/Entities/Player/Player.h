#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"
#include "../../ControllerStuff.hpp"


class Player :
    public Entity, public IHasHealth
{
public:
    enum PlayerCountry
    {
	    AMERICA,
        JAPAN,
        SWEDEN,
        ENGLAND
    };
	Player(sf::Vector2f pos, PlayerCountry country, bool isPlayerTwo);

    void reset();
    TickData tick() override;
    bool getTime() { return false; }
    void setHealth(short h) { health = h; };
    void increasePower();
    void increaseSpecial();
private:
    //power level goes up to 3, 4 total levels -Phoenix
    unsigned int powerLevel = 0, 
        //special uses are probably 2, Ray said don't quote me on that though -Phoenix
        special = 2;
};