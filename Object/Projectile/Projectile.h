#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();
	Projectile(sf::Vector2f pos, sf::Vector2f vel);
	Projectile(float posX, float posY, sf::Vector2f vel);
	Projectile(sf::Vector2f, sf::Vector2f, sf::Vector2f);
	Projectile(float, float, sf::Vector2f, sf::Vector2f);
	Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player); //The end all be all of
	//Projectile constructors
	Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short dela);
	//Adds delay

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
private:
	short delay = 0;
};