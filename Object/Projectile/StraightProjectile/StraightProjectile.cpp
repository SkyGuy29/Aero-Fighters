#include "StraightProjectile.h"

StraightProjectile::StraightProjectile(sf::Vector2f pos, float angle, float speed)
{
	this->pos = pos;
	this->angle = angle;
	this->speed = speed;
	size = sf::Vector2f(5, 10);

	sprite.setOrigin(size / 2.f);
	sprite.setPosition(pos);
	sprite.setSize(size);
	sprite.rotate(angle);
}

void StraightProjectile::update(sf::Vector2u winSize)
{
	pos.x += speed * std::sin(angle * TO_RAD);
	pos.y -= speed * std::cos(angle * TO_RAD);
	sprite.setPosition(pos);

	if (pos.x > winSize.x || pos.y > winSize.y || pos.x < 0 || pos.y < 0)
		del = true;
}

void StraightProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}