#include "pch.h"
#include "Action.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action)


	Action::Action():
		Attributed(Action::TypeIdClass()) {}

	Action::Action(IdType typeID) :
		Attributed(typeID) {}

	std::string Action::ToString() const
	{
		return std::string("Action!! :D");
	}

	bool Action::Equals(const RTTI* rhs) const
	{
		bool equals = false;

		if (rhs == nullptr)
		{
			return equals;
		}


		if (this == rhs)
		{
			equals = true;
		}

		auto* object = rhs->As<Action>();

		if (object == nullptr)
		{
			return equals;
		}



		if (_name == object->_name && Scope::Equals(object))
		{
			equals = true;
		}

		return equals;
	}

	const std::string& Action::GetObjectName() const
	{
		return _name;
	}

	void Action::SetObjectName(const std::string& name)
	{
		_name = std::move(name);
	}

}