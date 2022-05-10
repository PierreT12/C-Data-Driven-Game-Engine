#include "pch.h"
#include "ActionCreate.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionCreate)


	ActionCreate::ActionCreate() :
		Action(ActionCreate::TypeIdClass()) {}

	std::string ActionCreate::ToString() const
	{
		return std::string("ActionCreate!! :D");
	}

	bool ActionCreate::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<ActionCreate>();

		if (object == nullptr)
		{
			return equals;
		}



		if (_name == object->_name &&
			_actionClass == object->_actionClass &&
			Action::Equals(object))
		{
			equals = true;
		}

		return equals;
	}

	void ActionCreate::Update(const GameState& /*gamestate*/)
	{
		Vector<Action*>& createQueue = GameState::GetCreateQueue();

		createQueue.PushBack(this);
	}

	ActionCreate* ActionCreate::Clone() const
	{
		return new ActionCreate(*this);
	}

	const std::string& ActionCreate::GetActionClass() const
	{
		return _actionClass;
	}

	void ActionCreate::SetActionClass(const std::string& actionClass)
	{
		_actionClass = std::move(actionClass);
	}

	const Vector<Signature> ActionCreate::GetSignature()
	{
		return Vector<Signature>{
			{ "Name", DatumTypes::STRING, 1, offsetof(ActionCreate, _name) },
			{ "Class Name", DatumTypes::STRING, 1, offsetof(ActionCreate, _actionClass) }
		};
	}

}

