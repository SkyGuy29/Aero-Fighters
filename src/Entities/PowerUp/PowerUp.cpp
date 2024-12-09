#include "PowerUp.h"


void PowerUp::interceptBarrier()
{
    sf::Vector2f pos = getPosition();
    if (pos.x < 0 || pos.x > windowSize.width)
    {
        (vel.x *= -1);
        bounces++;
    }
    if (pos.y < 0 || pos.y > windowSize.height / 2.f)
    {
        (vel.y *= -1);
        bounces++;
    }
    return;
}


Entity::TickData PowerUp::tick()
{
    move();
    if (bounces < 9)
        interceptBarrier();

    return TickData();
}

const ICollidable::CollisionType PowerUp::collidesWith(ICollidable* other) const noexcept
{
    Player* playerCast = dynamic_cast<Player*>(other);

    if (playerCast == nullptr)
        return CollisionType::MISS;

    switch (this->ID)
    {
    case EntityID::POWERUP_MONEY:

        break;
    case EntityID::POWERUP_CHARGES:
        playerCast->increaseSpecial();
        break;
    case EntityID::POWERUP_LEVELS:
        playerCast->increasePower();
    }

    return CollisionType();
}
