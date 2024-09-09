#include "../Enemy_new.h"
#include "../../Entity.h"
#pragma once


class Land : public Enemy
{
public:
	Land(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, int* backgroundSpeed, unsigned char orientation = 0) :
		Enemy(pos, vel, ID, backgroundSpeed, orientation) {}

	void tick(EntityHolder& entities) override;
private:
	short rotateTimer = 0;
};