#include "pch.h"
#include "ActionBlock.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionBlock)

	ActionBlock::ActionBlock() :
		Action(ActionBlock::TypeIdClass()) {}

	ActionBlock::ActionBlock(IdType typeID) :
		Action(typeID) {}


	std::string ActionBlock::ToString() const
	{
		return std::string("ActionBlock!! :D");
	}

	bool ActionBlock::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<ActionBlock>();

		if (object == nullptr)
		{
			return equals;
		}



		if (Action::Equals(object))
		{
			equals = true;
		}

		return equals;
	}

	void ActionBlock::Update(const GameState& gamestate)
	{
		Scope* actionBlockScope = &Search("Actions")->Get<Scope>();
		
		if (actionBlockScope != nullptr)
		{

			for (size_t index = 0; index < actionBlockScope->Size(); ++index)
			{
				Scope* actionScope = &actionBlockScope->operator[](index).Get<Scope>();
				assert(actionScope->Is(Action::TypeIdInstance()));

				Action* child = static_cast<Action*>(actionScope);
				if (child != nullptr)
				{
					child->Update(gamestate);
				}

			}
		}

	}

	ActionBlock* ActionBlock::Clone() const
	{
		return new ActionBlock(*this);
	}

	const Vector<Signature> ActionBlock::GetSignature()
	{
		return Vector<Signature>{
			{ "Name", DatumTypes::STRING, 1, offsetof(ActionBlock, _name) },
			{ "Actions", DatumTypes::TABLE, 0, 0 }
		};
	}
}

