#pragma once

/**
 * Holds the data returned when you access the array.
 * Not constructed as a compile-time constant since it is constructed at runtime.
 */
template<typename RAW_TYPE>
struct ReturnData
{
	ReturnData() = default;

	/**
	 * Private constructor for VariableArray to use.
	 *
	 * @param DATA A pointer to the first object in the element.
	 * @param COUNT The number of objects in the element;
	 *				the size of the sub-array.
	 */
	ReturnData(RAW_TYPE& DATA, unsigned char COUNT) : DATA(DATA), COUNT(COUNT) {}

	// The beginning of the sub-array
	const RAW_TYPE& DATA = RAW_TYPE();
	// The length of the sub-array
	const unsigned char COUNT = 0;
};