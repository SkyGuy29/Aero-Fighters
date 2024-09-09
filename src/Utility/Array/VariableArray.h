#pragma once
#include <stdexcept>

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
	 * Holds spacing information for a given element.
	 *
	 * @warning Can only be initialized as a compile-time constant.
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
		constexpr SpacingElement(
			unsigned char STARTING_INDEX,
			unsigned char ENDING_INDEX
		) : STARTING_INDEX(STARTING_INDEX), ENDING_INDEX(ENDING_INDEX) {}
	};

	/**
	 * Holds the data returned when you access the array.
	 * Not constructed as a compile-time constant since it is constructed at runtime.
	 */
	struct ReturnData
	{
		// The beginning of the sub-array
		const RAW_TYPE* DATA;
		// The length of the sub-array
		const unsigned char COUNT;

		// Can only be constructed by the VariableArray
		ReturnData() = delete;

	private:
		/**
		 * Private constructor for VariableArray to use.
		 *
		 * @param DATA* A pointer to the first object in the element.
		 * @param COUNT The number of objects in the element;
		 *				the size of the sub-array.
		 */
		ReturnData(RAW_TYPE& DATA, unsigned char COUNT) : DATA(DATA), COUNT(COUNT) {}

		// Declare VariableArray as a friend so it can access the private constructor.
		friend VariableArray;
	};

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
	const ReturnData at(unsigned char index) const
	{
		// If we are accessing an element out of the bounds of the array
		if (index < 0 || index > TOTAL_ELEMENTS)
			throw std::out_of_range("Invalid Element Specified!");

		// Return reference to array index & the number of elements it holds.
		return ReturnData(
			DATA[SPACING[index].STARTING_INDEX],
			SPACING[index].ENDING_INDEX - SPACING[index].STARTING_INDEX + 1
		);
	}


private:
	// Internal object array
	const RAW_TYPE(&DATA)[TOTAL_UNIQUE_OBJECTS];

	// Internal object array element bound data
	const SpacingElement(&SPACING)[TOTAL_ELEMENTS];
};
