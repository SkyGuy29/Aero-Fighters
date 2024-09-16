#include "Player_new.h"


Player_new::Player_new(sf::Vector2f pos, sf::Vector2f vel,
	EntityID ID, int* backgroundSpeed, unsigned char orientation = 0) :
	Entity(pos, ID, orientation), IHasHealth(ID)
{
	if (players.size() == 0)
		players.resize(2);

	if (players[0] == nullptr)
		players[0] = this;
	else if (players[1] == nullptr)
		players[1] = this;
	else
		throw std::out_of_range("Generating too many players! Check Player_new.cpp::Player_new().");
}


void Player_new::tick()
{
	
}