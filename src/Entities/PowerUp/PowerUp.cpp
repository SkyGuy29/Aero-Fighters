#include "PowerUp.h"


PowerUp::PowerUp(sf::Vector2f spawnPos, EntityID id)
{

}


void PowerUp::interceptBarrier()
{
    sf::Vector2f pos = getPosition();
    if (pos.x < 0 || pos.x > getWinSize().x)
    {
        (vel.x *= -1);
        bounces++;
    }
    if (pos.y < 0 || pos.y > getWinSize().y)
    {
        (vel.y *= -1);
        bounces++;
    }
    return ;
}


Entity::TickData PowerUp::tick()
{
    return TickData();
}
