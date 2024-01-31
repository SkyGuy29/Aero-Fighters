#pragma once

#include "Projectile.h"

class Player : public sf::Drawable
{
public:
	Player();
	Player(sf::Vector2f position);

	int getScore() const;

	int getLives() const;

	bool isAlive() const;

	void move(sf::Vector2f offset, sf::Vector2u winSize);

	void shoot(std::vector<Projectile*>& prog);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f pos, size = sf::Vector2f(100, 200);
	float speed = 5.f;

	sf::RectangleShape sprite = sf::RectangleShape(size);

	int score = 0, lives = 0;

	bool alive = true;
};

