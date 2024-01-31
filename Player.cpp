#include "Player.h"

Player::Player()
{
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

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
