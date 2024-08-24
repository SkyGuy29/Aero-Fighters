#pragma once

#include "../Object.h"

// creates an object that is collectible by the player.
// this consists of powerups and money.
class Collectable final : public Object
{
public:
	Collectable(short, sf::Vector2f, float*);
	Collectable(short, float, float, float*);

	void update(sf::Vector2f winSize, std::vector<Object*>* objects, 
		bool time) override;
private:
	float* backgroundSpeed;
};