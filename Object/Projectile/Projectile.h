#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();
	Projectile(sf::Vector2f pos, sf::Vector2f vel);
	Projectile(float posX, float posY, sf::Vector2f vel);

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
};