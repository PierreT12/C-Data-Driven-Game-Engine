#include "pch.h"
#include "ActionBlockSwitch.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionBlockSwitch)

	ActionBlockSwitch::ActionBlockSwitch() :
		ActionBlock(ActionBlockSwitch::TypeIdClass()) {}

	ActionBlockSwitch::ActionBlockSwitch(IdType typeID) :
		ActionBlock(typeID) {}


	std::string ActionBlockSwitch::ToString() const
	{
		return std::string("ActionBlockSwitch!! :D");
	}

	ActionBlockSwitch* ActionBlockSwitch::Clone() const
	{
		return new ActionBlockSwitch(*this);
	}

	const std::string& ActionBlockSwitch::GetSwitchValue() const
	{
		return _value;
	}

	void ActionBlockSwitch::SetSwitchValue(const std::string& string)
	{
		_value = std::move(string);
	}

	bool ActionBlockSwitch::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As< ActionBlockSwitch>();

		if (object == nullptr)
		{
			return equals;
		}


		if (_value == object->_value && ActionBlock::Equals(object))
		{
			equals = true;
		}

		return equals;
	}

	void ActionBlockSwitch::Update(const GameState& gamestate)
	{
		Datum* value = Find("Switch");
		
		if (value != nullptr)
		{
			std::string& valueString = value->Get<std::string>();

			Scope* cases = &Search("Case")->Get<Scope>();

			Datum* foundCase = cases->Find(valueString.c_str());
			if (foundCase != nullptr)
			{
				assert(foundCase->Get<Scope>().Is(Action::TypeIdClass()));

				Action* action = static_cast<Action*>(&foundCase->Get<Scope>());

				action->Update(gamestate);
			}
		}
	}

	const Vector<Signature> ActionBlockSwitch::GetSignature()
	{
		return Vector<Signature>{ 
			{ "Name", DatumTypes::STRING, 1, offsetof(ActionBlockSwitch, _name) },
			{ "Switch", DatumTypes::STRING, 1, offsetof(ActionBlockSwitch, _value) },
			{ "Case", DatumTypes::TABLE, 0, 0 }
		};
	}
}


