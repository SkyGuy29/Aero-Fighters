#include "Explosion.h"

Explosion::Explosion(sf::Vector2f pos, int type)
{
	this->pos = pos;
	this->type = EXPLOSION;
	this->vel = {0, 0};
	setSize(32, 32);
	setPos(pos);
	sprite.setSize(sf::Vector2f(32, 32));
	sprite.setOrigin(sf::Vector2f(32, 32) / 2.f);
}

void Explosion::update(sf::Vector2u winSize, std::vector<Object*>*)
{
	nextFrame();
	if (anDone)
		del = true;
}
