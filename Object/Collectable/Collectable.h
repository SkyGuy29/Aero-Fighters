#pragma once

#include "../Object.h"

class Collectable : public Object
{
public:
	Collectable(short, sf::Vector2f);
	Collectable(short, float, float);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
};

