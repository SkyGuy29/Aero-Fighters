#include "Explosion.h"


Explosion::Explosion(const sf::Vector2f pos, const int type)
{
	this->pos = pos;
	this->type = EXPLOSION;
	this->vel = {0, 0};
	switch (type)
	{
	case 0:
		setSize(48, 48);
		setSpriteNum(0);
		break;
	case 1:
		setSize(47, 37);
		setSpriteNum(1);
		break;
	case 2:
		setSize(78, 80);
		setSpriteNum(2);
		break;
	case 3:
		setSize(38, 41);
		setSpriteNum(3);
		break;
	}
	setPos(pos);
	sprite.setSize(size);
	sprite.setOrigin(size / 2.f);
}


void Explosion::update(sf::Vector2f winSize, std::vector<Object*>*, bool time)
{
	nextFrame(2);
	sprite.move(0, backgroundSpeed);
	if (anDone)
		del = true;
}
