#include "pch.h"
#include "TypeRegistry.h"


namespace FieaGameEngine
{
	TypeRegistry* TypeRegistry::_instance;

	TypeRegistry* TypeRegistry::GetInstance()
	{
		if (!_instance)
		{
			_instance = new TypeRegistry();
		}

		return _instance;
	}

	void TypeRegistry::AddEntry(const std::pair<size_t, Vector<Signature>>& pair)
	{
		_pairs.Insert(pair);
	}

	Vector<Signature>& TypeRegistry::Get(size_t key)
	{
		auto [it, found, index] = _pairs.Find(key);

		assert(found);

		return (*it).second;
	}




	TypeRegistry::TypeRegistry():
		_pairs(10, DefaultHash<size_t>())
	{}

}
