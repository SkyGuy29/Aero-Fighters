#pragma once
#include <stdexcept>
#include "ReturnData.h"
#include "SpacingElement.h"
#include "../EntityData/ProjectilePrototype.h"

/**
 * Holds static data tables where individual elements can
 * have multiple data members, The array can ONLY be
 * initialized as a compile-time constant, placing it in
 * the programs binary during compilation.
 * 
 * @tparam RAW_TYPE The type that is stored internally.
 * @tparam TOTAL_ELEMENTS The total accessible elements.
 * @tparam TOTAL_UNIQUE_OBJECTS The total objects needed to be stored
 *								under raw data, this includes all
 *								sub-elements that make up the array.
 *
 * @warning Can only be initialized as a compile-time constant.
 */
template<typename RAW_TYPE, unsigned char TOTAL_ELEMENTS, unsigned char TOTAL_UNIQUE_OBJECTS>
class VariableArray
{
public:

	/**
	 * Constexpr constructor for constructing as a compile-time constant
	 *
	 *	@param rawData A reference to the internal object array.
	 *	@param spacings A reference to the internal spacing array.
	 */
	constexpr VariableArray(
		const RAW_TYPE(&rawData)[TOTAL_UNIQUE_OBJECTS],
		const SpacingElement(&spacings)[TOTAL_ELEMENTS]
							) : SPACING(spacings), DATA(rawData) {}

	/**
	 * Array accessor method for retrieving
	 * sub-array location & bounds information
	 * 
	 * @param index The element being accessed.
	 * @return ReturnData holding sub-array information.
	 */
	const ReturnData<RAW_TYPE> at(unsigned char index) const
	{
		// If we are accessing an element out of the bounds of the array
		if (index < 0 || index > TOTAL_ELEMENTS)
			throw std::out_of_range("Invalid Element Specified!");

		// Return reference to array index & the number of elements it holds.
		return ReturnData<RAW_TYPE>(
			(RAW_TYPE&)DATA[SPACING[index].STARTING_INDEX],
			SPACING[index].ENDING_INDEX - SPACING[index].STARTING_INDEX + 1
		);
	}


private:
	// Internal object array
	const RAW_TYPE(&DATA)[TOTAL_UNIQUE_OBJECTS];

	// Internal object array element bound data
	const SpacingElement(&SPACING)[TOTAL_ELEMENTS];
};