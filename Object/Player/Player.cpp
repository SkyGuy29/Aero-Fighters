#include "Player.h"

Player::Player()
{
}

Player::Player(sf::Vector2f position)
{
	pos = position;
	sprite.setPosition(pos - size / 2.f);
}

int Player::getScore() const
{
	return score;
}

int Player::getLives() const
{
	return lives;
}

bool Player::isAlive() const
{
	return alive;
}

void Player::move(sf::Vector2f offset, sf::Vector2u winSize)
{
	pos += offset * speed;

	if (pos.x - size.x / 2.f < 0)
		pos.x = size.x / 2.f;
	else if (pos.x + size.x / 2.f > winSize.x)
		pos.x = winSize.x - size.x / 2.f;

	if (pos.y - size.y / 2.f < 0)
		pos.y = size.y / 2.f;
	else if (pos.y + size.y / 2.f > winSize.y)
		pos.y = winSize.y - size.y / 2.f;

	sprite.setPosition(pos - size / 2.f);
}

void Player::shoot(std::vector<Projectile*>& prog)
{
}