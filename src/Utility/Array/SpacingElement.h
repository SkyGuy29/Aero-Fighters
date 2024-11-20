#pragma once

/**
 * Holds spacing information for a given element.
 */
struct SpacingElement
{
	// This elements starting index
	unsigned char STARTING_INDEX;
	// This elements ending index
	unsigned char ENDING_INDEX;

	/**
	 *
	 * @param STARTING_INDEX The index in the array where this element begins.
	 * @param ENDING_INDEX The index in the array where this element ends.
	 *
	 * @warning Can only be initialized as a compile-time constant.
	 */
	SpacingElement(
		unsigned char STARTING_INDEX = 0,
		unsigned char ENDING_INDEX = 0
	) : STARTING_INDEX(STARTING_INDEX), ENDING_INDEX(ENDING_INDEX) {}
};