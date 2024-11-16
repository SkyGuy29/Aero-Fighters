#pragma once

template<typename RAW_TYPE, unsigned char TOTAL_ELEMENTS, unsigned char TOTAL_UNIQUE_OBJECTS>
class VariableArray;

/**
 * Holds the data returned when you access the array.
 * Not constructed as a compile-time constant since it is constructed at runtime.
 */
template<typename RAW_TYPE>
struct ReturnData
{
	// The beginning of the sub-array
	const RAW_TYPE& DATA;
	// The length of the sub-array
	const unsigned char COUNT;

	// Can only be constructed by the VariableArray
	ReturnData() = delete;
private:
	/**
	 * Private constructor for VariableArray to use.
	 *
	 * @param DATA A pointer to the first object in the element.
	 * @param COUNT The number of objects in the element;
	 *				the size of the sub-array.
	 */
	ReturnData(RAW_TYPE& DATA, unsigned char COUNT) : DATA(DATA), COUNT(COUNT) {}

	// Declare VariableArray as a friend so it can access the private constructor.
	template<typename RAW_TYPE_, unsigned char TOTAL_ELEMENTS, unsigned char TOTAL_UNIQUE_OBJECTS>
	friend class VariableArray;
};