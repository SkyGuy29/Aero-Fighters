#pragma once

#include "../Object.h"
#include <iostream>

class Projectile : public Object
{
public:
	Projectile();
	Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, short sprit); 
	Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, short dela, short sprit);
	//Adds delay

	void update(sf::Vector2u winSize, std::vector<Object*>* objects, bool time);
private:
	short delay = 0;
	sf::Vector2f tempSize;
};