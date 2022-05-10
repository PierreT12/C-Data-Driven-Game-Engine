namespace FieaGameEngine
{
	template<typename _Type>
	HashMap<const std::string, const Factory<_Type>* const> Factory<_Type>::_hashMap{ 10,  DefaultHash<const std::string>() };

	template<typename _Type>
	inline const Factory<_Type>* const Factory<_Type>::Find(const std::string& key)
	{
		auto [it, found, index] = _hashMap.Find(key);

		if (!found)
		{
			return nullptr;
		}
		return (*it).second;
	}


	template<typename _Type>
	inline bool Factory<_Type>::AddFactory(Factory<_Type>& factory)
	{
		auto [it, inserted] = _hashMap.Insert(std::pair<std::string, Factory<_Type>*>(factory.ClassName(), &factory));
		return !inserted;
	}


	template<typename _Type>
	inline bool Factory<_Type>::RemoveFactory(Factory<_Type>& factory)
	{
		return _hashMap.Remove(factory.ClassName());
	}


	template<typename _Type>
	inline _Type* Factory<_Type>::Create(const std::string& className)
	{
		const Factory<_Type>* foundFactory = Find(className);

		if (foundFactory == nullptr)
		{
			throw std::runtime_error("Was unable to find the correct Factory :{");
		}

		return foundFactory->Create();
	}

	template<typename _Type>
	void Factory<_Type>::ClearList()
	{
		_hashMap.ClearList();
	}

	template<typename _Type>
	inline size_t Factory<_Type>::Size()
	{
		return _hashMap.Size();
	}

	template<typename _Type>
	inline bool Factory<_Type>::IsEmpty()
	{
		return _hashMap.IsEmpty();
	}


}