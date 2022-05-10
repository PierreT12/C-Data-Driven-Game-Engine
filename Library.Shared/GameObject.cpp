#include "pch.h"
#include "GameObject.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject)


	GameObject::GameObject():
		Attributed(GameObject::TypeIdClass()) {}

	GameObject::GameObject(IdType typeID):
		Attributed(typeID){}

	std::string GameObject::ToString() const
	{
		return std::string("GameObject!! :D");
	}
	bool GameObject::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<GameObject>();

		if (object == nullptr)
		{
			return equals;
		}

		

		if (_transform._position == object->_transform._position
			&& _transform._rotation == object->_transform._rotation
			&& _transform._scale == object->_transform._scale
			&& _tag == object->_tag 
			&& Scope::Equals(object))
		{

			equals = true;
		}

		return equals;

	}
	GameObject* GameObject::Clone() const
	{
		return new GameObject(*this);
	}

	void GameObject::Update(const GameState& gamestate)
	{
		ClearDestroyQueue();
		ClearCreateQueue();
	
		Datum* actionListDatum = Search("Actions");
		if (actionListDatum != nullptr && actionListDatum->Size() > 0)
		{
			Scope* actionListScope = &actionListDatum->Get<Scope>();

			for (size_t index = 0; index < actionListScope->Size(); ++index)
			{
				Scope* actionScope = &actionListScope->operator[](index).Get<Scope>();

				if (actionScope->GetParent() == actionListScope)
				{
					assert(actionScope->Is(Action::TypeIdClass()));
					Action* child = static_cast<Action*>(actionScope);
					if (child != nullptr)
					{
						child->Update(gamestate);
					}
				}
				

			}
		}

		Datum* children = Find("Children");
		if (children != nullptr && children->Size() > 0)
		{
			for (size_t index = 0; index < children[0].operator[](0).Size(); ++index)
			{
				Scope* scope = &children->operator[](0).operator[](index).Get<Scope>();
				assert(scope->Is(GameObject::TypeIdInstance()));
				GameObject* child = static_cast<GameObject*>(scope);
				if (child != nullptr)
				{
					child->Update(gamestate);
				}
			}
		}
	}

	const std::string& GameObject::GetObjectName() const
	{
		return _name;
	}

	const std::string& GameObject::GetObjectTag() const
	{
		return _tag;
	}

	const glm::vec4& GameObject::GetPosition() const
	{
		return _transform._position;
	}

	const glm::vec4& GameObject::GetRotation() const
	{
		return _transform._rotation;
	}

	const glm::vec4& GameObject::GetScale() const
	{
		return _transform._scale;
	}

	void GameObject::SetObjectName(const std::string& name)
	{
		_name = std::move(name);
	}

	void GameObject::SetObjectTag(const std::string& tag)
	{
		_tag = std::move(tag);
	}

	void GameObject::SetPosition(const glm::vec4& position)
	{
		_transform._position = position;
	}

	void GameObject::SetRotation(const glm::vec4& rotation)
	{
		_transform._rotation = rotation;
	}

	void GameObject::SetScale(const glm::vec4& scale)
	{
		_transform._scale = scale;
	}

	const Datum& GameObject::GetActions() const
	{
		return *Find(_actions);
	}

	void GameObject::CreateAction(const std::string& className, const std::string& actionName)
	{
		Scope* createdAction = Factory<Scope>::Create(className);
		assert(createdAction->Is(Action::TypeIdClass()));

		Action* action = static_cast<Action*>(createdAction);
		action->SetObjectName(actionName);

		Scope* actionList = &GetActions().Get<Scope>();
		assert(actionList->Is(Action::TypeIdClass()));

		actionList->Adopt(actionName, *action);
	}

	void GameObject::ClearCreateQueue()
	{
		Vector<Action*>& createAction = GameState::GetCreateQueue();

		for (auto& actions : createAction)
		{
				Datum* classNameDatum = actions->Find("Class Name");
				Datum* nameDatum = actions->Find("Name");

				if (classNameDatum != nullptr && nameDatum != nullptr)
				{
					std::string& classNameStr = classNameDatum->Get<std::string>();
					std::string& nameStr = nameDatum->Get<std::string>();
					CreateAction(classNameStr, nameStr);
					createAction.Remove(actions);
				}
		}

	}

	void GameObject::ClearDestroyQueue()
	{
		Vector<Action*>& destroyAction = GameState::GetDestroyQueue();
		Datum* actionParent = Search("Actions");
		if (actionParent != nullptr && actionParent->Size() > 0)
		{
			for (size_t index = 0; index < destroyAction.Size(); ++index)
			{
				Action* actions = destroyAction[index];

				Datum* stringDatum = actions->Find("Action To Destory"); 

				assert(stringDatum != nullptr);

				std::string str = stringDatum->Get<std::string>();

				Datum* foundAction = actionParent->Get<Scope>().Find(str.c_str()); 
				
				if (foundAction != nullptr)
				{
					Scope* foundActionScope = &foundAction->Get<Scope>();

					assert(foundActionScope->Is(Action::TypeIdClass()));

					Action* action = static_cast<Action*>(foundActionScope);

					actionParent->Get<Scope>().Orphan(*action);

					destroyAction.Remove(actions);

					delete action;
				}

			}
		}
	}

	const Vector<Signature> GameObject::GetSignature()
	{
		return Vector<Signature>{
			{ "Name", DatumTypes::STRING, 1, offsetof(GameObject, _name) },
			{ "Position", DatumTypes::VEC4, 1, offsetof(GameObject, _transform._position) },
			{ "Rotation", DatumTypes::VEC4, 1, offsetof(GameObject, _transform._rotation) },
			{ "Scale", DatumTypes::VEC4, 1, offsetof(GameObject, _transform._scale) },
			{ "Tag", DatumTypes::STRING, 1, offsetof(GameObject, _tag) },
			{ "Children", DatumTypes::TABLE, 0, 0 },
			{ "Actions", DatumTypes::TABLE, 0, 0 }
		};
	}
}

