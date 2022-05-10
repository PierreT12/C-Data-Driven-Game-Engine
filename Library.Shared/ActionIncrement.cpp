#include "pch.h"
#include "ActionIncrement.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement)

	ActionIncrement::ActionIncrement() :
		Action(ActionIncrement::TypeIdClass()) {}

	ActionIncrement::ActionIncrement(IdType typeID) :
		Action(typeID) {}

	std::string ActionIncrement::ToString() const
	{
		return std::string("ActionIncrement!! :D");
	}

	bool ActionIncrement::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<ActionIncrement>();

		if (object == nullptr)
		{
			return equals;
		}



		if (_target == object->_target &&
			_step == object->_step &&
			Action::Equals(object))
		{
			equals = true;
		}

		return equals;
	}

	void ActionIncrement::Update(const GameState& /*gamestate*/)
	{
		if (_changedName)
		{
			_targetDatum = Search(_target);
			_changedName = false;
		}

		if (_targetDatum != nullptr && _targetDatum->Type() == DatumTypes::FLOAT)
		{
			for (size_t index = 0; index < _targetDatum->Size(); ++index)
			{
				_targetDatum[index].Get<float>() += _step;
			}
		}
	}


	void ActionIncrement::SetTarget(const std::string& target)
	{
		_target = std::move(target);
		_changedName = true;
	}

	void ActionIncrement::SetStep(float step)
	{
		_step = step;

	}

	const std::string& ActionIncrement::GetTarget() const
	{
		return _target;
	}

	float ActionIncrement::GetStep() const
	{
		return _step;
	}

	ActionIncrement* ActionIncrement::Clone() const
	{
		return new ActionIncrement(*this);
	}

	const Vector<Signature> ActionIncrement::GetSignature()
	{
		return Vector<Signature>{ 
			{ "Name", DatumTypes::STRING, 1, offsetof(ActionIncrement, _name) },
			{ "Target", DatumTypes::STRING, 1, offsetof(ActionIncrement, _target) },
			{ "Step", DatumTypes::FLOAT, 1, offsetof(ActionIncrement, _step) }};
	}

}