
namespace FieaGameEngine
{

	inline size_t AdditiveHash(const uint8_t* ptr, size_t size)
	{

		size_t hash = 12;
		for (size_t i = 0; i < size; ++i)
		{
			hash += ptr[i];
		}

		return hash;
	}


	template <typename _Type>

	inline size_t DefaultHash<_Type>::operator()(const _Type type)
	{
		return AdditiveHash(reinterpret_cast<const uint8_t*>(&type), sizeof(_Type));
	}
;
	
	template<>
	inline size_t DefaultHash<std::string>::operator()(std::string type)
	{
			return AdditiveHash(reinterpret_cast<const uint8_t*>(type.c_str()), sizeof(type.size()));
	}
	
	template<>
	inline size_t DefaultHash<const std::string>::operator()(const std::string type)
	{
		return AdditiveHash(reinterpret_cast<const uint8_t*>(type.c_str()), sizeof(type.size()));
	}
	

	template<>
	inline size_t DefaultHash<std::wstring>::operator()(std::wstring type)
	{
		return AdditiveHash(reinterpret_cast<const uint8_t*>(type.c_str()), sizeof(type.size()));
	}
	

	template<>
	inline size_t DefaultHash<const std::wstring>::operator()(const std::wstring type)
	{
		return AdditiveHash(reinterpret_cast<const uint8_t*>(type.c_str()), sizeof(type.size()));
	}

	template<>
	inline size_t DefaultHash<char*>::operator()(char* type)
	{
		return AdditiveHash(reinterpret_cast<const uint8_t*>(type), sizeof(strlen(type)));
	}

	template<>
	inline size_t DefaultHash<const char*>::operator()(const char* type)
	{
		return AdditiveHash(reinterpret_cast<const uint8_t*>(type), sizeof(strlen(type)));
	}


}




