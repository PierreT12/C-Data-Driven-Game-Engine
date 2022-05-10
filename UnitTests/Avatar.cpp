#include "pch.h"
#include "Avatar.h"


namespace FooSupport
{
	RTTI_DEFINITIONS(Avatar)

	Avatar::Avatar() :
		GameObject(Avatar::TypeIdClass()) {}


	Avatar::Avatar(IdType typeID) :
		GameObject(typeID) {}



	std::string Avatar::ToString() const
	{
		return std::string("Avatar!! :D");
	}

	bool Avatar::Equals(const RTTI* rhs) const
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

		auto* avatar = rhs->As<Avatar>();

		if (avatar == nullptr)
		{
			return equals;
		}

		if (_health == avatar->_health && GameObject::Equals(avatar))
		{
			equals = true;
		}

		return equals;
	}


	Avatar* Avatar::Clone() const
	{
		return new Avatar(*this);
	}
	const Vector<Signature> Avatar::GetSignature()
    {
		return Vector<Signature>{
			{ "Name", DatumTypes::STRING, 1, offsetof(Avatar, _name) },
			{ "Position", DatumTypes::VEC4, 1, offsetof(Avatar, _transform._position) },
			{ "Rotation", DatumTypes::VEC4, 1, offsetof(Avatar, _transform._rotation) },
			{ "Scale", DatumTypes::VEC4, 1, offsetof(Avatar, _transform._scale) },
			{ "Tag", DatumTypes::STRING, 1, offsetof(Avatar, _tag) },
			{ "Health", DatumTypes::INT, 1, offsetof(Avatar, _health) },
			{ "Children", DatumTypes::TABLE, 0, 0 }
		};
    }

	void Avatar::Update(const GameState& gamestate)
	{
		_health += 100;
		GameObject::Update(gamestate);

	}

	int32_t Avatar::GetHealth()
	{
		return _health;
	}

}
