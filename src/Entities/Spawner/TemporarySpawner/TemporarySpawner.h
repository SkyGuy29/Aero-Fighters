#pragma once
#include "../EnemySpawner.h"


/// <summary>
/// Once this is on screen, it will be deleted and spawn a wave of enemies at it's position.
/// Used for air/moving land/water enemies.
/// Shows as a white square in the level editor.
/// </summary>
class TemporarySpawner : public EnemySpawner
{
public:
	void tick() override;
private:
};

