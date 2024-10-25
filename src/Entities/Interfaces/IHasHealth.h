#pragma once
#include "../../Utility/EntityData/EntityDataStorage.h"

class IHasHealth
{
public:
	unsigned short getHealth() const noexcept
	{
		return health;
	}
	void damage() { health--; }

protected:
	IHasHealth(EntityID ID) :
		health(EntityDataStorage::getData(ID).health) {}

	unsigned short health;
};