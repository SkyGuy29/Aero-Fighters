#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"
#include "../../ControllerStuff.hpp"


// TODO add controls, update player, etc.
class Player :
    public Entity, public IHasHealth, public ICollidable
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

    void move();
    void reset();
    TickData shoot();
    TickData fireSpecial();
    TickData tick() override;
    bool getTime() { return false; }
    void setHealth(short h) { health = h; };
    void increasePower();
    void increaseSpecial();

    sf::IntRect getBounds() const noexcept override
    {
        return sf::IntRect(getPosition().x + 10, getPosition().y + 16, 20, 32);
    }

private:
    //power level goes up to 3, 4 total levels -Phoenix
    unsigned int powerLevel = 0, 
        //special uses are probably 2, Ray said don't quote me on that though -Phoenix
        special = 2;
    unsigned int cooldownSecondary = 0, invincibility = 0;
    bool isPlayerTwo = false;
};