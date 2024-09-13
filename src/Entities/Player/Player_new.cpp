#include "Player_new.h"


Player_new::Player_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, int* backgroundSpeed, unsigned char orientation = 0) :
	Entity(pos, ID, orientation), IHasHealth(ID)
{

}


void Player_new::tick()
{
	
}