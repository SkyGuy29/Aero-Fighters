#include "../Enemy_new.h"
#pragma once
#define PI 3.14159


class Land_new : public Enemy_new
{
public:
	Land_new(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, float* backgroundSpeed, unsigned char orientation = 0) :
		Enemy_new(pos, vel, ID, backgroundSpeed, orientation) {}

	void tick() override;
private:
	short rotateTimer = 0;
	// the player the enemy targets (0/1) -> (player one/player two)
	bool targetP1 = 0;
};