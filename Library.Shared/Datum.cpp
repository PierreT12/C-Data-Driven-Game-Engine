#pragma once
#include "pch.h"
#include "Datum.h"
#include <typeinfo>
#include <functional>
#include <stdexcept>

namespace FieaGameEngine
{

	//Lookup Table
	const size_t Datum::DatumSizeTypes[] =
	{	
		0,				//Unknown
		sizeof(int32_t),  //Int
		sizeof(float),  //Float
		sizeof(glm::vec4), //Vector
		sizeof(glm::mat4),//Matrix
		sizeof(std::string), //String
		sizeof(RTTI*),//RTTI
		sizeof(Scope*)//Scope
	};


	//Lookup Table
	const Datum::FromStringFunc Datum::DatumFromString[] =
	{
		nullptr,				//Unknown
		&Datum::SetFromStringInt,  //Int
		&Datum::SetFromStringFloat,  //Float
		&Datum::SetFromStringVec4, //Vector
		&Datum::SetFromStringMat4,//Matrix
		&Datum::SetFromStringString //String
	};


	//Lookup Table
	const Datum::PushBackFromStringFunc Datum::DatumPushBackFromString[] =
	{
		nullptr,				//Unknown
		&Datum::PushBackFromStringInt,  //Int
		&Datum::PushBackFromStringFloat,  //Float
		&Datum::PushBackFromStringVec4, //Vector
		&Datum::PushBackFromStringMat4,//Matrix
		&Datum::PushBackFromStringString //String
	};


	//Lookup Table
	const Datum::ToStringFunc Datum::DatumToString[] =
	{
		nullptr,				//Unknown
		&Datum::ToStringInt,  //Int
		&Datum::ToStringFloat,  //Float
		&Datum::ToStringVec4, //Vector
		&Datum::ToStringMat4,//Matrix
		&Datum::ToStringString, //String
		&Datum::ToStringRTTI //RTTI
	};



	//Lookup Table
	const Datum::CompareFunc Datum::DatumCompare[] =
	{
		nullptr,				//Unknown
		&Datum::ComparePrim,  //Int
		&Datum::ComparePrim,  //Float
		&Datum::ComparePrim, //Vector
		&Datum::ComparePrim,//Matrix
		&Datum::CompareStrings, //String
		&Datum::ComparePointers,//RTTI
		&Datum::ComparePointers
	};



	Datum::Datum(int32_t other):
		_type{DatumTypes::INT}
	{
		PushBack(other);
	}

	Datum::Datum(float other):
		_type{DatumTypes::FLOAT}
	{
		PushBack(other);
	}

	Datum::Datum(const glm::vec4& other) :
		_type{ DatumTypes::VEC4 }
	{
		PushBack(other);
	}

	Datum::Datum(const glm::mat4& other) :
		_type{ DatumTypes::MAT4 }
	{
		PushBack(other);
	}

	Datum::Datum(const std::string& other) :
		_type{ DatumTypes::STRING }
	{
		PushBack(other);
	}

	Datum::Datum(RTTI* other) :
		_type{ DatumTypes::POINTER}
	{
		PushBack(other);
	}

	Datum::Datum(Scope& other):
		_type{ DatumTypes::TABLE }
	{
		PushBack(other);
	}

	Datum::Datum(DatumTypes type, size_t capacity) :
		_type{type}
	{
		Reserve(capacity);
	
	}

	Datum::~Datum()
	{

		if (_isExternal)
		{
			_data.v = nullptr;
		}
		else
		{
			if (_type == DatumTypes::STRING)
			{
				ClearList();
			}


			free(_data.v);
		}

		
	}

	Datum::Datum(const Datum& other):
		_type{other._type},
		_isExternal{other._isExternal}
	{

		if (!other._isExternal && _type != DatumTypes::UNKNOWN)
		{
			Reserve(other._capacity);

			if (_type == DatumTypes::STRING)
			{
				for (; _size < other._size;)
				{	
					PushBack(other._data.s[_size]);
				}
			}
			else 
			{
				memcpy(_data.v, other._data.v, (_capacity* DatumSizeTypes[static_cast<size_t>(_type)]));

				_size = other._size;
			}

			
		}
		else
		{
			_capacity = other._capacity;
			_size = other._size;
			_data.v = other._data.v;

		}
	
	}




	Datum::Datum(Datum&& rhs) noexcept:
		_capacity{rhs._capacity},
		_size{rhs._size},
		_type{rhs._type},
		_isExternal{rhs._isExternal},
		_data{rhs._data}
	{
		rhs._capacity = 0;
		rhs._size = 0;
		rhs._type = DatumTypes::UNKNOWN;
		rhs._isExternal = false;
		rhs._data.v = nullptr;

		
	}


	Datum& Datum::operator=(const Datum& other)
	{
		if (other._type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		_type = other._type;

		if (!_isExternal)
		{
			ClearList();
		}
		
		if (other._isExternal)
		{
			_isExternal = true;
			_data.v = other._data.v;

			_size = other._size;
			_capacity = other._capacity;
		}
		else
		{
			Reserve(other._capacity);

			if (_type == DatumTypes::STRING)
			{
				for (; _size < other._size;)
				{
					PushBack(other._data.s[_size]);
				}
			}
			else
			{
				memcpy(_data.v, other._data.v, (_capacity * DatumSizeTypes[static_cast<size_t>(_type)]));

				_size = other._size;
			}
			
			_isExternal = false;
		}

		

		return *this;
	}

	Datum& Datum::operator=(Datum&& rhs) noexcept
	{
		if (this != &rhs)
		{
			this->~Datum();
			_capacity = rhs._capacity;
			_size = rhs._size;
			_type = rhs._type;
			_isExternal = rhs._isExternal;
			_data = rhs._data;

			rhs._capacity = 0;
			rhs._size = 0;
			rhs._type = DatumTypes::UNKNOWN;
			rhs._isExternal = false;
			rhs._data.v = nullptr;

		}
		
		return *this;
	}

	void FieaGameEngine::Datum::ScalarAssignmentHelper(DatumTypes type)
	{
		if (_type != DatumTypes::UNKNOWN && _type != type)
		{
			throw std::runtime_error("Cannot change a Datum's Type");
		}

		if (_type == DatumTypes::UNKNOWN)
		{
			_type = type;
		}
	}


	Datum& Datum::operator=(int32_t other)
	{
		ScalarAssignmentHelper(DatumTypes::INT);
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(float other)
	{
		ScalarAssignmentHelper(DatumTypes::FLOAT);
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& other)
	{
		ScalarAssignmentHelper(DatumTypes::VEC4);
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& other)
	{
		ScalarAssignmentHelper(DatumTypes::MAT4);
		PushBack(other);

		return *this;
	}


	Datum& Datum::operator=(const std::string& other)
	{
		ScalarAssignmentHelper(DatumTypes::STRING);
		PushBack(other);

		return *this;
	}

	Datum& Datum::operator=(RTTI* other)
	{
		ScalarAssignmentHelper(DatumTypes::POINTER);
		PushBack(other);

		return *this;
	}

	Datum& Datum::operator=(Scope& other)
	{
		ScalarAssignmentHelper(DatumTypes::TABLE);
		PushBack(other);

		return *this;
	}

	Scope& Datum::operator[](size_t index)
	{
		return Get<Scope>(index);
	}


	DatumTypes Datum::Type() const
	{
		return _type;
	}

	bool Datum::IsExternal() const
	{
		return _isExternal;
	}

	void Datum::SetType(const DatumTypes& type)
	{
		if (_type != type)
		{
			if (type == DatumTypes::UNKNOWN)
			{
				throw std::runtime_error("Cannont set type to Unknown. :{");
			}
			_type = type;
		}

	}

	size_t Datum::Size() const
	{
		return _size;
	}

	void Datum::Resize(size_t newSize)
	{
		if (_type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		if (_isExternal)
		{
			throw std::runtime_error("Cannont modify storage of an external Datum. :{");
		}

		if (newSize < _size)
		{
			for (; _size != newSize;)
			{
				PopBack();
			}
		}
		else
		{
			Reserve(newSize);
			
			if (_type == DatumTypes::STRING)
			{
				for (; _size != newSize;)
				{
					std::string* temp = (_data.s + _size);

					temp = new (_data.s + _size) std::string();
					++_size;
				}
			}
			else
			{
				uint8_t* dataTemp = reinterpret_cast<uint8_t*>(_data.v);

				memset((dataTemp + _size), 0, (_size * DatumSizeTypes[static_cast<size_t>(_type)]));
			}
			_size = newSize;

			
		}

		_capacity = _size;
	}

	void Datum::Reserve(size_t capacity)
	{
		if (_type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		if (_isExternal)
		{
			throw std::runtime_error("Cannont modify storage of an external Datum. :{");
		}

		if (capacity > _capacity)
		{
			size_t size = DatumSizeTypes[static_cast<size_t>(_type)];
			assert(size != 0);
			void* reallocate = realloc(_data.v, capacity * size);
			_data.v = reallocate;
			_capacity = capacity;
			
		}

	}

	void Datum::ClearList()
	{
		//if (_type == DatumTypes::UNKNOWN)
		//{
		//	throw std::runtime_error("Not a Valid DatumType :{");
		//}

		while (_size > 0)
		{
			PopBack();
		}

	}

	void Datum::SetStorage(int32_t* externalData, size_t size)
	{
		SetStorage(DatumTypes::INT, externalData, size);
	}

	void Datum::SetStorage(float* externalData, size_t size)
	{
		SetStorage(DatumTypes::FLOAT, externalData, size);
	}


	void Datum::SetStorage(glm::vec4* externalData, size_t size)
	{
		SetStorage(DatumTypes::VEC4, externalData, size);

	}

	void Datum::SetStorage( glm::mat4* externalData, size_t size)
	{
		SetStorage(DatumTypes::MAT4, externalData, size);
	}

	void Datum::SetStorage( std::string* externalData, size_t size)
	{
		SetStorage(DatumTypes::STRING, externalData, size);
	}

	void Datum::SetStorage(RTTI** externalData, const size_t size)
	{
		SetStorage(DatumTypes::POINTER, externalData, size);
	}

	
	bool Datum::operator!=(const Datum& other) const
	{
		bool value = false;
		if (_type != other._type || _size != other._size || _isExternal != other._isExternal)
		{
			value = true;
		}
		else
		{
			auto temp = DatumCompare[static_cast<size_t>(_type)];

			value = (*this.*temp)(other._data);
		}

		return value;
	}

	bool Datum::operator==(const Datum& other) const
	{
		return (!operator!=(other));
	}



	void Datum::SetFromStringInt(const std::string& str, const size_t index)
	{
		Set(std::stoi(str), index);
	

	}

	void Datum::SetFromStringFloat(const std::string& str, const size_t index)
	{
		Set(std::stof(str), index);

	}

	void Datum::SetFromStringVec4(const std::string& str, const size_t index)
	{
		glm::vec4 temp;

		sscanf_s(str.c_str(), "%f %f %f %f", &temp.x, &temp.y, &temp.z, &temp.w);

		Set(temp, index);

	}

	void Datum::SetFromStringMat4(const std::string& str, const size_t index)
	{
		glm::mat4 temp;

		sscanf_s(str.c_str(), "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &temp[0].x, &temp[0].y, &temp[0].z, &temp[0].w,
			&temp[1].x, &temp[1].y, &temp[1].z, &temp[1].w,
			&temp[2].x, &temp[2].y, &temp[2].z, &temp[2].w,
			&temp[3].x, &temp[3].y, &temp[3].z, &temp[3].w);

		Set(temp, index);

	}

	void Datum::SetFromStringString(const std::string& str, const size_t index)
	{
		Set(str, index);
	}

	std::string Datum::ToString(const size_t index) const
	{
		auto temp = DatumToString[static_cast<size_t>(_type)];

		if (_type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		return (*this.*temp)(index);
	}

	void Datum::PushBackFromString(const std::string& str)
	{
		auto temp = DatumPushBackFromString[static_cast<size_t>(_type)];

		return (*this.*temp)(str);
	}

	void Datum::PushBackFromStringInt(const std::string& str)
	{
		PushBack(std::stoi(str));
	}

	void Datum::PushBackFromStringFloat(const std::string& str)
	{
		PushBack(std::stof(str));
	}

	void Datum::PushBackFromStringVec4(const std::string& str)
	{
		glm::vec4 temp;

		sscanf_s(str.c_str(), "%f %f %f %f", &temp.x, &temp.y, &temp.z, &temp.w);

		PushBack(temp);

	}

	void Datum::PushBackFromStringMat4(const std::string& str)
	{
		glm::mat4 temp;

		sscanf_s(str.c_str(), "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &temp[0].x, &temp[0].y, &temp[0].z, &temp[0].w,
			&temp[1].x, &temp[1].y, &temp[1].z, &temp[1].w,
			&temp[2].x, &temp[2].y, &temp[2].z, &temp[2].w,
			&temp[3].x, &temp[3].y, &temp[3].z, &temp[3].w);

		PushBack(temp);
	}

	void Datum::PushBackFromStringString(const std::string& str)
	{
		PushBack(str);
	}


	void Datum::SetFromString(const std::string& str, const size_t index)
	{
		auto temp = DatumFromString[static_cast<size_t>(_type)];

		return (*this.*temp)(str, index);
	}

	void Datum::PushBackHelper(DatumTypes type)
	{
		if (_isExternal)
		{
			throw std::runtime_error("Cannont modify storage of an external Datum. :{");
		}

		if (_type == DatumTypes::UNKNOWN)
		{
			_type = type;
		}

		if (_type != type)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}


		if (_size == _capacity)
		{
			size_t newSize = _capacity + 3;
			Reserve(newSize);
		}


	}


	void Datum::PushBack(const int32_t& data)
	{
		PushBackHelper(DatumTypes::INT);
		new (_data.i + _size) int32_t(data);
		++_size;
	}

	void Datum::PushBack(const float& data)
	{

		PushBackHelper(DatumTypes::FLOAT);
		new (_data.f + _size) float(data);
		++_size;

	}

	void Datum::PushBack(const glm::vec4& data)
	{
		PushBackHelper(DatumTypes::VEC4);
		new (_data.vec + _size) glm::vec4(data);
		++_size;

	}

	void Datum::PushBack(const glm::mat4& data)
	{
		PushBackHelper(DatumTypes::MAT4);
		new (_data.mat + _size) glm::mat4(data);
		++_size;

	}

	void Datum::PushBack(const std::string& data)
	{
		PushBackHelper(DatumTypes::STRING);
		new (_data.s + _size) std::string(data);
		++_size;
	}

	
	void Datum::PushBack(RTTI* const & data)
	{
		PushBackHelper(DatumTypes::POINTER);
		RTTI** temp = (_data.r + _size);
		*temp = data;
		++_size;
	}

	void Datum::PushBack(Scope& data)
	{
		PushBackHelper(DatumTypes::TABLE);
		Scope** temp = (_data.t + _size);
		*temp = &data;
		++_size;
	}

	void Datum::PopBack()
	{
		if (_type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}


		if (!_isExternal)
		{
			if (_size > 0)
			{
				if (_type == DatumTypes::STRING)
				{
					std::destroy_at(_data.s + (_size - 1));
				}
			}
			
		}

		--_size;

	}

	void Datum::Set(int32_t data, const size_t index)
	{

		if (_type != DatumTypes::INT)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}

		if (_size == 0)
		{
			Reserve(3);
		}

		if (index > _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		int32_t* temp = (_data.i + index);

		*temp = data;

		

	}


	void Datum::Set(float data, const size_t index)
	{
		if (_type != DatumTypes::FLOAT)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}

		if (_size == 0)
		{
			Reserve(3);
		}

		if (index > _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		float* temp = (_data.f + index);

		*temp = data;

		
	}

	void Datum::Set(const glm::vec4& data, const size_t index)
	{
		if (_type != DatumTypes::VEC4)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}

		if (_size == 0)
		{
			Reserve(3);
		}

		if (index > _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		glm::vec4* temp = (_data.vec + index);

		*temp = data;

		
	}

	void Datum::Set(const glm::mat4& data, const size_t index)
	{
		if (_type != DatumTypes::MAT4)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}

		if (_size == 0)
		{
			Reserve(3);
		}

		if (index > _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		glm::mat4* temp = (_data.mat + index);

		*temp = data;

		
	}

	void Datum::Set(const std::string& data, const size_t index)
	{
		if (_type != DatumTypes::STRING)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}
		if (_size == 0)
		{
			Reserve(3);
		}

		if (index > _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		char* temp = const_cast<char*>((_data.s + index)->c_str());

		char* datatemp = const_cast<char*>(data.c_str());
	
		strncpy_s(temp, data.size()+ 1, datatemp, _TRUNCATE);


		
	}

	void Datum::Set(RTTI* data, const size_t index)
	{
		if (_type != DatumTypes::POINTER)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}


		if (index >= _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		Reserve(_capacity + 1);

		memmove((_data.r + index + 1), (_data.r + index), (sizeof(RTTI*) * (_size - index)));

		RTTI** temp = (_data.r + _size);
		*temp = data;

		
	}

	void Datum::Set(Scope& data, const size_t index)
	{
		if (_type != DatumTypes::TABLE)
		{
			throw std::runtime_error("The Datum Type does not match what you are trying to pass through :{");
		}

		if (index >= _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

		Reserve(_capacity + 1);

		memmove((_data.t + index + 1), (_data.t + index), (sizeof(Scope*) * (_size - index)));

		Scope** temp = (_data.t + _size);
		*temp = &data;

		

	}

	std::string Datum::ToStringInt(const size_t index) const
	{
		return std::to_string(Get<int32_t>(index));
	}

	std::string Datum::ToStringFloat(const size_t index) const
	{
		return std::to_string(Get<float>(index));
	}

	std::string Datum::ToStringVec4(const size_t index) const
	{
		char temp[MaxChar];
		glm::vec4 vec = Get<glm::vec4>(index);
		snprintf(temp, MaxChar, "%f %f %f %f", vec.x, vec.y, vec.z, vec.w);
		return std::string(temp);
	}

	std::string Datum::ToStringMat4(const size_t index) const
	{
		char temp[MaxChar];
		glm::mat4 mat = Get<glm::mat4>(index);
		snprintf(temp, MaxChar, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", mat[0].x, mat[0].y, mat[0].z, mat[0].w,
			mat[1].x, mat[1].y, mat[1].z, mat[1].w,
			mat[2].x, mat[2].y, mat[2].z, mat[2].w,
			mat[3].x, mat[3].y, mat[3].z, mat[3].w );

		return std::string(temp);
	}

	std::string Datum::ToStringString(const size_t index) const
	{
		return Get<std::string>(index);
	}

	std::string Datum::ToStringRTTI(const size_t index) const
	{
		return Get<RTTI*>(index)->ToString();
	}



	void Datum::RemoveHelper(DatumTypes type) const
	{
		if (_isExternal)
		{
			throw std::runtime_error("Cannont modify storage of an external Datum. :{");
		}

		if (_type != type || _type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}


	}

	

	bool Datum::Remove(const int32_t data)
	{
		RemoveHelper(DatumTypes::INT);

		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}
		return removed;
	}

	bool Datum::Remove(const float data)
	{
		RemoveHelper(DatumTypes::FLOAT);

		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}
		return removed;
	}

	bool Datum::Remove(const glm::vec4& data)
	{
		RemoveHelper(DatumTypes::VEC4);
		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}
		return removed;
	}

	bool Datum::Remove(const glm::mat4& data)
	{
		RemoveHelper(DatumTypes::MAT4);

		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}
		return removed;
	}

	bool Datum::Remove(const std::string& data)
	{
		RemoveHelper(DatumTypes::STRING);

		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}
		return removed;
	}


	bool Datum::Remove(const RTTI* data)
	{
		
		RemoveHelper(DatumTypes::POINTER);
		assert(data);
		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}
		
		return removed;
	}

	bool Datum::Remove(Scope& data)
	{
		RemoveHelper(DatumTypes::TABLE);
		bool removed = false;
		if (_size > 0)
		{
			auto [index, found] = Find(data);
			if (found)
			{
				RemoveAt(index);
				removed = true;
			}
		}

		return removed;
	}

	void Datum::RemoveAt(size_t index)
	{
		if (_isExternal)
		{
			throw std::runtime_error("Cannont modify storage of an external Datum. :{");
		}

		if (_type == DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}


		if (index >= _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}


		if (_type == DatumTypes::STRING)
		{
			using namespace std;
			std::string* temp = (_data.s + index);

			temp->~string();
		}

		uint8_t* dataTemp = reinterpret_cast<uint8_t*>(_data.v);
		size_t size = DatumSizeTypes[static_cast<size_t>(_type)];
		memmove((dataTemp + (index * size)), (dataTemp + (((index + 1) * size))), (size * (_size - index)));
		--_size;

	}

	std::pair<size_t, bool> Datum::Find(const int32_t value) const
	{
		if (_type != DatumTypes::INT)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (value == _data.i[index])
			{
				found = true;
				break;
			}
		}

		return{ index, found };
	}

	std::pair<size_t, bool> Datum::Find(const float value) const
	{
		if (_type != DatumTypes::FLOAT)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (value == _data.f[index])
			{
				found = true;
				break;

			}
		}
		return{ index, found };
	}

	std::pair<size_t, bool> Datum::Find(const glm::vec4& value) const
	{
		if (_type != DatumTypes::VEC4)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (value == _data.vec[index])
			{
				found = true;
				break;

			}
		}
		return{ index, found };
	}

	std::pair<size_t, bool> Datum::Find(const glm::mat4& value) const
	{

		if (_type != DatumTypes::MAT4)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (value == _data.mat[index])
			{
				found = true;
				break;

			}
		}
		return{ index, found };
	}

	std::pair<size_t, bool> Datum::Find(const std::string& value) const
	{

		if (_type != DatumTypes::STRING)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (value == _data.s[index])
			{
				found = true;
				break;
			}
		}
		return{ index, found };
	}

	std::pair<size_t, bool> Datum::Find(const RTTI* value) const
	{
		if (_type != DatumTypes::POINTER)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		assert(value);

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (value == _data.r[index])
			{
				found = true;
				break;
			}
		}
		return{ index, found };
	}


	std::pair<size_t, bool> Datum::Find(Scope& value) const
	{
		if (_type != DatumTypes::TABLE)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		bool found = false;
		size_t index = 0;
		for (; index < _size; ++index)
		{
			if (&value == _data.t[index])
			{
				found = true;
				break;
			}
		}
		return{ index, found };
	}

	void Datum::SetStorage(DatumTypes type, void* externalData, size_t size)
	{
		if (_type != type && _type != DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		if (_type == DatumTypes::UNKNOWN)
		{
			_type = type;
		}

		assert(externalData);

		if (_type != DatumTypes::TABLE)
		{


			if (!_isExternal)
			{
				ClearList();

				_isExternal = true;
			}

			_data.v = externalData;
			_capacity = _size = size;

		}
	}


	void FieaGameEngine::Datum::GetHelper(DatumTypes type, size_t index) const
	{
		if (_type == DatumTypes::UNKNOWN || _type != type)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

		if (index >= _size)
		{
			throw std::out_of_range("The given index was out of range :{");
		}

	}

	void Datum::FrontBackHelper(DatumTypes type) const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Trying to return a null :{");
		}

		if (_type == DatumTypes::UNKNOWN || _type != type)
		{
			throw std::runtime_error("Not a Valid DatumType :{");
		}

	}
	bool Datum::ComparePrim(const DatumValues& otherdata) const
	{
		if (memcmp(_data.v, otherdata.v, (DatumSizeTypes[static_cast<size_t>(_type)] * _size)) != 0)
		{
			return true;
		}
		return false;
	}
	bool Datum::CompareStrings(const DatumValues& otherdata) const
	{
		bool notequal = false;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.s[i] != otherdata.s[i])
			{
				notequal = true;
				break;
			}
		}

		return notequal;
	}
	bool Datum::ComparePointers(const DatumValues& otherdata) const
	{
		bool notequal = false;
		for (size_t i = 0; i < _size; ++i)
		{
			//Check for a null and if they are the same address
			//if()

			if (!(_data.r[i]->Equals(otherdata.r[i])))
			{
				notequal = true;
				break;
			}
		}
		return notequal;
	}
}
