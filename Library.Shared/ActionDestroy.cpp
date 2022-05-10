#include "pch.h"
#include "ActionDestroy.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDestroy)

		ActionDestroy::ActionDestroy() :
		Action(ActionDestroy::TypeIdClass()) {}

	bool ActionDestroy::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<ActionDestroy>();

		if (object == nullptr)
		{
			return equals;
		}



		if (_actionToDelete == object->_actionToDelete && Action::Equals(object))
		{
			equals = true;
		}

		return equals;
	}

	void ActionDestroy::Update(const GameState& /*gamestate*/)
	{
		Vector<Action*>& destroyQueue = GameState::GetDestroyQueue();

		destroyQueue.PushBack(this);
	}

	const std::string ActionDestroy::GetActionToDestroy() const
	{
		return _actionToDelete;
	}

	void ActionDestroy::SetActionToDestroy(const std::string& actionName)
	{
		_actionToDelete = std::move(actionName);
	}

	ActionDestroy* ActionDestroy::Clone() const
	{
		return new ActionDestroy(*this);
	}


	std::string ActionDestroy::ToString() const
	{
		return std::string("ActionDestroy!! :D");
	}

	const Vector<Signature> ActionDestroy::GetSignature()
	{
		return Vector<Signature>{
			{ "Name", DatumTypes::STRING, 1, offsetof(ActionDestroy, _name) },
			{ "Action To Destory", DatumTypes::STRING, 1, offsetof(ActionDestroy, _actionToDelete) }
		};
	}

}


