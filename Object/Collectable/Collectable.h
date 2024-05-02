#pragma once

#include "../Object.h"

//creates an object that is collectible by the player.
//this consists of powerups and money.
class Collectable : public Object
{
public:
	Collectable(short, sf::Vector2f, float*);
	Collectable(short, float, float, float*);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);
private:
	float* backgroundSpeed;
};

