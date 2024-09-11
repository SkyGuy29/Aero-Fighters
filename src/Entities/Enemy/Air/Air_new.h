#include "../Enemy_new.h"
#pragma once


class Air_new : public Enemy_new
{
public:
	Air_new(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, int* backgroundSpeed, unsigned char orientation = 0);

	void tick() override;
private:

};

