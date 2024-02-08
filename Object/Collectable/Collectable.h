#pragma once

#include "../Object.h"

class Collectable : public Object
{
public:
	Collectable(short);

	int getType();
	
	void intersect(Object*);

	void update(sf::Vector2u winSize);
};

