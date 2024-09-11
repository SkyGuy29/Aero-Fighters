#pragma once
#include "../Projectile.h"
class Explosion final : public Projectile
{
public:
	Explosion(sf::Vector2f pos, int type);

	void update(sf::Vector2f winSize, std::vector<Object*>*, bool time, int& p1Score, int& p2Score) override;

	float backgroundSpeed = 1.f;
};

