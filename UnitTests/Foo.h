#pragma once
#include "pch.h"
#include "RTTI.h"
#include "Factory.h"

using namespace FieaGameEngine;
namespace FooSupport
{
	class Foo : public FieaGameEngine::RTTI
	{

		RTTI_DECLARATIONS(Foo, RTTI)

	public:
		//Foo() = default;
		Foo(std::int32_t data = 0);
		Foo(const Foo& other);
		Foo& operator=(const Foo& other);
		virtual ~Foo();

		int& Data();
		int& Data() const;

		virtual std::string ToString() const override;

		virtual bool Equals(const RTTI* rhs) const  override;

		bool operator==(const Foo& rhs) const;
		
		bool operator!=(const Foo& rhs) const;

	private:
		std::int32_t* mData{ nullptr };

	};

	ConcreteFactory(Foo, RTTI)
}





