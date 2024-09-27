#pragma once
#include <cstdint>
#include <vector>

class AttackPrototype
{
public:
	AttackPrototype(const uint8_t SPAWN_INDEX) : SPAWN_INDEX(SPAWN_INDEX) {}


	//void spawn(std::vector<Entity*>& projectiles)
	//{
	//
	//}

private:
	const uint8_t SPAWN_INDEX;
};
