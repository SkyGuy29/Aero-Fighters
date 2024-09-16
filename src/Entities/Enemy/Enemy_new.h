#pragma once
#include "../Entity.h"
#include "../Interfaces/IHasHealth.h"

// Primarily used by 
class Enemy_new :
	public Entity, protected IHasHealth
{
public:
	Enemy_new(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, unsigned char orientation = 0);

	~Enemy_new() override;

	void tick() override;

	static std::vector<Enemy_new*>& getEnemies() { return enemies; };
protected:
	float* backgroundSpeed = nullptr;
	bool entered = false;
private:
	static std::vector<Enemy_new*> enemies;
};