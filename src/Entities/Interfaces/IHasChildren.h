#pragma once
#include "../Entity.h"

// Declares child holder for entities that have children.
// Is currently only used by enemies.
// Should be derived from as private.
class IHasChildren
{
protected:
	inline IHasChildren(Entity* children, unsigned char count) noexcept :
		children({children, count}) {}

	// This is a struct and not a class because custom functions may need to be
	// ran directly on the children; this is only a child holder.
	struct Children
	{
		// A dynamnic array of entities
		Entity* child = nullptr;

		// The total number of children
		unsigned char count = 0;

		void Tick()
		{
			// For every child, tick.
			for (unsigned char i = 0; i < count; i++)
				child[i].Tick();
		}

		// Destroys the children of the parent entity
		~Children()
		{
			delete[] child;
		}
	};

	// This entities child entities
	Children children;
};