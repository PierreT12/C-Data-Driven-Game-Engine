#include "pch.h"
#include "Foo.h"


namespace FooSupport
{
	RTTI_DEFINITIONS(Foo)

	Foo::Foo(int32_t data) :
		mData(new int(data)){}


	Foo::Foo(const Foo& other) :
		mData(new int32_t(*other.mData)){}

	Foo& Foo::operator=(const Foo& other)
	{
		if (this != &other)
		{
			*mData = *other.mData;
		}

		return *this;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	int32_t& Foo::Data()
	{
		return *mData;
	}

	int& Foo::Data() const
	{
		return *mData;
	}

	std::string Foo::ToString() const
	{
		return std::to_string(*mData);
	}

	bool Foo::Equals(const RTTI* rhs) const
	{
		const Foo* f = rhs->As<const Foo>();

		return operator==(*f);
	}


	bool Foo::operator==(const Foo& rhs) const
	{
		if (mData == rhs.mData)
		{
			return true;
		}

		return (*mData == *rhs.mData);
	}

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}



}