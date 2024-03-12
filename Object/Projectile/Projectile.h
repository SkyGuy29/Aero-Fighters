#pragma once

#include "../Object.h"

class Projectile : public Object
{
public:
	Projectile();
	Projectile(sf::Vector2f pos, sf::Vector2f vel);
	Projectile(float posX, float posY, sf::Vector2f vel);
	Projectile(sf::Vector2f, sf::Vector2f, sf::Vector2f);
	Projectile(float, float, sf::Vector2f, sf::Vector2f, int);
	Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, int sprit); 
	Projectile(float posX, float posY, sf::Vector2f vel,
	sf::Vector2f size, short ID, bool player, short cool, short dela, int sprit);
	//Adds delay

	void setTextureSprite(int sprit); //So that there is one place to put the sprite stuff.

	void update(sf::Vector2u winSize, std::vector<Object*>* objects);
private:
	short delay = 0;
	sf::Vector2f tempSize;
};