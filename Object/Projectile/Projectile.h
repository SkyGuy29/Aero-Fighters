#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();
	Projectile(sf::Vector2f pos, float angle, float vel);
	Projectile(float posX, float posY, float angle, float vel);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
};