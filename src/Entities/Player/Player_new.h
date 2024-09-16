#pragma once
#include "../Entity.h"
#include "../Interfaces/ICollidable.h"
#include "../Interfaces/IHasHealth.h"

class Player_new :
    public Entity, public IHasHealth
{
public:
    Player_new(sf::Vector2f pos, sf::Vector2f vel,
        EntityID ID, int* backgroundSpeed, unsigned char orientation = 0);

    void tick();
    void setHealth(short h) { health = h; };

    static std::vector<Player_new*>& getPlayers() { return players; }
private:
    static std::vector<Player_new*> players;
};