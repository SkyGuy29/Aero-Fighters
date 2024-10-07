#include "EntityData.h"
#include "EntityData.h"

// Initialize the EntityDataTable here
EntityDataStorage::EntityData const EntityDataStorage::EntityDataTable[] = {
    {
        Vec2f{ 0, 0 }, // X, Y
        0, // Health
        0, // Base Cooldown
        0  // CHILD_DATA
    }
    // Add other values if necessary
};

//VariableArray<EntityDataStorage::ProjectilePrototype, 0/*Total Elements*/, 0/*Total Unique Objects*/> const EntityDataStorage::AttackData =
/*{
    {
        ProjectilePrototype { // Example case
        	{0, 0},
        	{0, 0},
        	EntityID::TILE_ROOFUS_ENGLAND
        },
        // Insert more entries here
    }, //EntityDataStorage::ProjectilePrototype
    {
        VariableArray<ProjectilePrototype, 0, 0>::SpacingElement {
            0,
            20
		}
    }, //VariableArray<EntityDataStorage::ProjectilePrototype,0,0>::SpacingElement
};*/