#pragma once
#include "../EntityData.h"

class IHasHealth
{
public:
	unsigned short getHealth() const noexcept
	{
		return health;
	}

protected:
	IHasHealth(EntityID ID) :
		health(EntityDataStorage::getData(ID).health) {}

	unsigned short health;
};