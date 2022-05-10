#pragma once
#include <cstdint>

namespace FieaGameEngine
{
	/// <summary>
	/// Additive Hash Free Function
	/// </summary>
	// <param name="ptr"> Takes in pointer to the bytes assoicated with this object</param>
	//<param name = "size"> The size of the object< / param>
	/// <returns> Hashed value </returns>
	size_t AdditiveHash(const uint8_t* ptr, size_t size);

	/// <summary>
	/// Template Default Hash Struct
	/// </summary>
	template <typename _Type>
	struct DefaultHash
	{
		/// <summary>
		/// Functor for hashing
		/// </summary>
		/// <param name="type"> Takes in most data types, execpt for complex user types, and some types that use pointers</param>
		/// <returns> Hashed value </returns>
		size_t operator()(const _Type type);
	};




}
#include "DefaultHash.inl"