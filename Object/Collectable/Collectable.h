#pragma once

#include "../Object.h"

class Collectable : public Object
{
public:
	Collectable(short);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
};

