#pragma once
#include "../Entity.h"


/// <summary>
/// Generic enemy spawner.
/// </summary>
class EnemySpawner : public Entity
{
public:
	EnemySpawner();

	void tick(EntityHolder& entities) override;
private:
	// needs to be initialized with EnemySpawner; the enemy that is spawned
	EntityID spawnedEnemy;
};

