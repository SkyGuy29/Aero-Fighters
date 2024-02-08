#pragma once

#include "../Object.h"

class Collectable : public Object
{
	Collectable();

	int getType();
	
	void intersect(Object*);

	void update();
};

