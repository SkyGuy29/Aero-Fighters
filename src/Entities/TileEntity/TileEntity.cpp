#include "TileEntity.h"

TileEntity::TileEntity(EntityPrototype* prototype)
	: Entity(prototype->SPAWN_POS, prototype->ID), IHasHealth(prototype->ID)
{
}

Entity::TickData TileEntity::tick()
{
	return TickData();
}
