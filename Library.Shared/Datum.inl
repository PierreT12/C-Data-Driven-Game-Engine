#include "Datum.h"
namespace FieaGameEngine
{


	template<typename _Type>
	inline _Type& Datum::Get(const size_t index)
	{
		static_assert(false, "Please use a valid Datum Type.");
	}

	template<>
	inline int32_t& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::INT, index);
		return _data.i[index];
	}

	template<>
	inline float& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::FLOAT, index);
		return _data.f[index];
	}

	template<>
	inline glm::vec4& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::VEC4, index);
		return _data.vec[index];
	}

	template<>
	inline glm::mat4& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::MAT4, index);
		return _data.mat[index];
	}

	template<>
	inline std::string& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::STRING, index);
		return _data.s[index];
	}

	template<>
	inline RTTI*& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::POINTER, index);
		return _data.r[index];
	}

	template<>
	inline Scope& Datum::Get(const size_t index)
	{
		GetHelper(DatumTypes::TABLE, index);
		return *_data.t[index];
	}


	template<typename _Type>
	inline _Type& Datum::Get(const size_t index) const
	{
		static_assert(false, "Please use a valid Datum Type.");
	}

	template<>
	inline int32_t& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::INT, index);
		return _data.i[index];
	}

	template<>
	inline float& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::FLOAT, index);
		return _data.f[index];
	}

	template<>
	inline glm::vec4& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::VEC4, index);
		return _data.vec[index];
	}

	template<>
	inline glm::mat4& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::MAT4, index);
		return _data.mat[index];
	}

	template<>
	inline std::string& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::STRING, index);
		return _data.s[index];
	}

	template<>
	inline RTTI*& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::POINTER, index);
		return _data.r[index];
	}

	template<>
	inline Scope& Datum::Get(const size_t index) const
	{
		GetHelper(DatumTypes::POINTER, index);
		return *_data.t[index];
	}

	template<typename _Type>
	inline _Type& Datum::Front()
	{
		static_assert(false, "Please use a valid Datum Type.");
	}

	template<>
	inline int32_t& Datum::Front()
	{
		FrontBackHelper(DatumTypes::INT);

		return *(_data.i);
	}


	template<>
	inline float& Datum::Front()
	{
		FrontBackHelper(DatumTypes::FLOAT);

		return *(_data.f);
	}

	template<>
	inline glm::vec4& Datum::Front()
	{
		FrontBackHelper(DatumTypes::VEC4);

		return *(_data.vec);
	}

	template<>
	inline glm::mat4& Datum::Front()
	{
		FrontBackHelper(DatumTypes::MAT4);

		return *(_data.mat);
	}

	template<>
	inline std::string& Datum::Front()
	{
		FrontBackHelper(DatumTypes::STRING);

		return *(_data.s);
	}

	template<>
	inline RTTI*& Datum::Front()
	{
		FrontBackHelper(DatumTypes::POINTER);

		return *(_data.r);
	}


	template<>
	inline Scope& Datum::Front()
	{
		FrontBackHelper(DatumTypes::TABLE);

		return **(_data.t);
	}




	template<typename _Type>
	inline const _Type& Datum::Front() const
	{
		static_assert(false, "Please use a valid Datum Type.");
	}

	template<>
	inline const int32_t& Datum::Front() const
	{
		FrontBackHelper(DatumTypes::INT);

		return *(_data.i);
	}


	template<>
	inline const float& Datum::Front()  const
	{
		FrontBackHelper(DatumTypes::FLOAT);

		return *(_data.f);
	}

	template<>
	inline const glm::vec4& Datum::Front()  const
	{
		FrontBackHelper(DatumTypes::VEC4);

		return *(_data.vec);
	}

	template<>
	inline const glm::mat4& Datum::Front()  const
	{
		FrontBackHelper(DatumTypes::MAT4);

		return *(_data.mat);
	}

	template<>
	inline const std::string& Datum::Front()  const
	{
		FrontBackHelper(DatumTypes::STRING);

		return *(_data.s);
	}


	template<>
	inline RTTI* const & Datum::Front()  const
	{
		FrontBackHelper(DatumTypes::POINTER);

		return *(_data.r);
	}

	template<>
	inline const Scope& Datum::Front()  const
	{
		FrontBackHelper(DatumTypes::TABLE);

		return **(_data.t);
	}




	template<typename _Type>
	inline _Type& Datum::Back()
	{
		static_assert(false, "Please use a valid Datum Type.");
	}

	template<>
	inline int32_t& Datum::Back()
	{
		FrontBackHelper(DatumTypes::INT);

		return *(_data.i + _size - 1);
	}


	template<>
	inline float& Datum::Back()
	{
		FrontBackHelper(DatumTypes::FLOAT);

		return *(_data.f + _size - 1);
	}

	template<>
	inline glm::vec4& Datum::Back()
	{
		FrontBackHelper(DatumTypes::VEC4);

		return *(_data.vec + _size - 1);
	}

	template<>
	inline glm::mat4& Datum::Back()
	{
		FrontBackHelper(DatumTypes::MAT4);

		return *(_data.mat + _size - 1);
	}

	template<>
	inline std::string& Datum::Back()
	{
		FrontBackHelper(DatumTypes::STRING);

		return *(_data.s + _size - 1);
	}

	template<>
	inline RTTI*& Datum::Back()
	{
		FrontBackHelper(DatumTypes::POINTER);

		return *(_data.r + _size - 1);
	}


	template<>
	inline Scope& Datum::Back()
	{
		FrontBackHelper(DatumTypes::TABLE);

		return **(_data.t + _size - 1);
	}


	template<typename _Type>
	inline const  _Type& Datum::Back() const
	{
		static_assert(false, "Please use a valid Datum Type.");
	}

	template<>
	inline const int32_t& Datum::Back() const
	{
		FrontBackHelper(DatumTypes::INT);

		return *(_data.i + _size - 1);
	}


	template<>
	inline const float& Datum::Back() const
	{
		FrontBackHelper(DatumTypes::FLOAT);

		return *(_data.f + _size - 1);
	}

	template<>
	inline const glm::vec4& Datum::Back() const
	{
		FrontBackHelper(DatumTypes::VEC4);

		return *(_data.vec + _size - 1);
	}

	template<>
	inline const glm::mat4& Datum::Back() const
	{
		FrontBackHelper(DatumTypes::MAT4);

		return *(_data.mat + _size - 1);
	}

	template<>
	inline const std::string& Datum::Back() const
	{
		FrontBackHelper(DatumTypes::STRING);

		return *(_data.s + _size - 1);
	}

	template<>
	inline RTTI* const & Datum::Back() const
	{
		FrontBackHelper(DatumTypes::POINTER);

		return *(_data.r + _size - 1);
	}


	template<>
	inline const Scope& Datum::Back() const
	{
		FrontBackHelper(DatumTypes::TABLE);

		return **(_data.t + _size - 1);
	}

}