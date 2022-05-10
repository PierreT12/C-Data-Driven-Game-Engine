#pragma once
#include "GameObject.h"


using namespace FieaGameEngine;


namespace FooSupport
{
	class Avatar final : public GameObject
	{
		RTTI_DECLARATIONS(Avatar, GameObject)


	public:
		Avatar();
		Avatar(IdType typeID);
		virtual ~Avatar() = default;
		Avatar(const Avatar& other) = default;
		Avatar& operator=(const Avatar& other) = default;
		Avatar(Avatar&& other) = default;
		Avatar& operator=(Avatar&& other) = default;


		virtual std::string ToString() const override;
		virtual bool Equals(const RTTI* rhs) const override;
		virtual Avatar* Clone() const override;

		static const Vector<Signature> GetSignature();


		void Update(const GameState& gamestate) override;


		int32_t GetHealth();


	private:
		int32_t _health;

	};


	ConcreteFactory(Avatar, Scope)
}


