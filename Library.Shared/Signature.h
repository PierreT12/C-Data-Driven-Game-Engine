#pragma once
#include "Datum.h"

namespace FieaGameEngine
{
	struct Signature
	{
		std::string _name{ nullptr };
		DatumTypes _type { DatumTypes::UNKNOWN };
		size_t _size { 0 };
		size_t _offset{ 0 };
	};


}
