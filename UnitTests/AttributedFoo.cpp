#include "pch.h"
#include "AttributedFoo.h"


namespace FooSupport
{
	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo():
		Attributed(AttributedFoo::TypeIdClass()){}



	AttributedFoo::AttributedFoo(IdType typeID):
		Attributed{typeID}{}

	std::string AttributedFoo::ToString() const
	{
		return std::string("AttributedFoo :D");
	}

	AttributedFoo* AttributedFoo::Clone() const
	{
		return new AttributedFoo(*this);
	}

	const Vector<Signature> AttributedFoo::GetSignature()
	{
		return Vector<Signature>
		{
			{ "ExternalInt", DatumTypes::INT, 1, offsetof(AttributedFoo, ExternalInt)},
			{ "ExternalFloat", DatumTypes::FLOAT, 1, offsetof(AttributedFoo, ExternalFloat)},
			{ "ExternalVec4", DatumTypes::VEC4, 1, offsetof(AttributedFoo, ExternalVec4)},
			{ "ExternalMat4", DatumTypes::MAT4, 1, offsetof(AttributedFoo, ExternalMat4)},
			{ "ExternalString", DatumTypes::STRING, 1, offsetof(AttributedFoo, ExternalString)},
			{ "ExternalIntArray", DatumTypes::INT, arraySize, offsetof(AttributedFoo, ExternalIntArray)},
			{ "ExternalFloatArray", DatumTypes::FLOAT, arraySize, offsetof(AttributedFoo, ExternalFloatArray)},
			{ "ExternalVec4Array", DatumTypes::VEC4, arraySize, offsetof(AttributedFoo, ExternalVec4Array)},
			{ "ExternalMat4Array", DatumTypes::MAT4, arraySize, offsetof(AttributedFoo, ExternalMat4Array)},
			{ "ExternalStringArray", DatumTypes::STRING, arraySize, offsetof(AttributedFoo, ExternalStringArray)},
			{ "NestedScope", DatumTypes::TABLE, 1, 0},
			{ "NestedScopeArray", DatumTypes::TABLE, arraySize, 0}
		};
	}

}