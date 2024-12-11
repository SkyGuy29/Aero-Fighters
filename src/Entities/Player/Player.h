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
	Player(sf::Vector2f pos, PlayerCountry country, bool isPlayerTwo);

    void move();
    void reset();
    TickData shoot();
    TickData fireSpecial();
    TickData tick() override;
    bool getTime() { return false; }
    EntityObjectAction getEntityAction(bool ignoreDeletion = false) noexcept override;
    void setHealth(short h) { health = h; }
    void increasePower();
    void increaseSpecial();
    bool getIsPlayerTwo() const
    {
        return isPlayerTwo;
    }
    sf::FloatRect getBounds() const noexcept override
    {
        // TODO fix hitboxes (this is way off) make sure to update debug renderer
        return sprite->getGlobalBounds();
    }

    const CollisionType collidesWith(ICollidable* other) const override
    {
        if (other->getBounds().intersects(getBounds()))
            return CollisionType::HIT;
        return CollisionType::MISS;
    }
private:
    //power level goes up to 3, 4 total levels -Phoenix
    unsigned int powerLevel = 0, 
        //special uses are probably 2, Ray said don't quote me on that though -Phoenix
        special = 2;
    unsigned int cooldownSecondary = 0, invincibility = 0;
    bool isPlayerTwo = false;
    PlayerCountry country;
};