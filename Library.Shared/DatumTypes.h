#pragma once

namespace FieaGameEngine
{
	enum class DatumTypes
	{
		UNKNOWN,
		INT,
		FLOAT,
		VEC4,
		MAT4,
		STRING,
		POINTER,
		TABLE,

		BEGIN = INT,
		END = TABLE

	};
}