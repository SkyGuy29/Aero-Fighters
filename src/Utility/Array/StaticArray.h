#pragma once
#include <stdexcept>

/**
 * Holds static data tables. The array can ONLY be
 * initialized as a compile-time constant, placing it in
 * the programs binary during compilation.
 *
 * @tparam RAW_TYPE The type that is stored internally.
 * @tparam LENGTH The total accessible elements.
 *
 * @warning Can only be initialized as a compile-time constant.
 */
template<typename RAW_TYPE, unsigned char LENGTH>
class StaticArray
{
public:

	/**
	 * Holds the data returned when you access the array.
	 * Not constructed as a compile-time constant since it is constructed at runtime.
	 */
	struct ReturnData
	{
		// The requested element.
		const RAW_TYPE& DATA;

		// Can only be constructed by the StaticArray
		ReturnData() = delete;

	private:
		/**
		 * Private constructor for StaticArray to use.
		 *
		 * @param DATA& A Const reference to the element.
		 */
		ReturnData(const RAW_TYPE& DATA) : DATA(DATA) {}

		// Declare StaticArray as a friend so it can access the private constructor.
		friend StaticArray;
	};

	/**
	 * Constexpr constructor for constructing as a compile-time constant
	 *
	 *	@param rawData A const reference to the internal object array.
	 */
	constexpr StaticArray(
		const RAW_TYPE(&rawData)[LENGTH]
	) : DATA(rawData) {}

	/**
	 * Array accessor method for retrieving a specified element.
	 *
	 * @param index The element being accessed.
	 * @return ReturnData holding the element.
	 */
	const ReturnData at(unsigned char index) const
	{
		// If we are accessing an element out of the bounds of the array
		if (index >= LENGTH)
			throw std::out_of_range("Invalid Element Specified!");

		// Return reference to array element.
		return ReturnData(
			DATA[index]
		);
	}


private:
	// Internal object array
	const RAW_TYPE(&DATA)[LENGTH];
};