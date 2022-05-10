#include "pch.h"
#include "DerivedAttributedFoo.h"


namespace FooSupport
{
	RTTI_DEFINITIONS(DerivedAttributedFoo)

		DerivedAttributedFoo::DerivedAttributedFoo() :
		AttributedFoo(DerivedAttributedFoo::TypeIdClass()) {}



	std::string DerivedAttributedFoo::ToString() const
	{
		return std::string("DerivedAttributedFoo :D");
	}

	DerivedAttributedFoo* DerivedAttributedFoo::Clone() const
	{
		return new DerivedAttributedFoo(*this);
	}

	const Vector<Signature> DerivedAttributedFoo::GetSignature()
	{
		return Vector<Signature>
		{
			{ "ExternalInt", DatumTypes::INT, 1, offsetof(AttributedFoo, ExternalInt)},
			{ "ExternalFloat", DatumTypes::FLOAT, 1, offsetof(AttributedFoo, ExternalFloat) },
			{ "ExternalVec4", DatumTypes::VEC4, 1, offsetof(AttributedFoo, ExternalVec4) },
			{ "ExternalMat4", DatumTypes::MAT4, 1, offsetof(AttributedFoo, ExternalMat4) },
			{ "ExternalString", DatumTypes::STRING, 1, offsetof(AttributedFoo, ExternalString) },
			{ "ExternalIntArray", DatumTypes::INT, arraySize, offsetof(AttributedFoo, ExternalIntArray) },
			{ "ExternalFloatArray", DatumTypes::FLOAT, arraySize, offsetof(AttributedFoo, ExternalFloatArray) },
			{ "ExternalVec4Array", DatumTypes::VEC4, arraySize, offsetof(AttributedFoo, ExternalVec4Array) },
			{ "ExternalMat4Array", DatumTypes::MAT4, arraySize, offsetof(AttributedFoo, ExternalMat4Array) },
			{ "ExternalStringArray", DatumTypes::STRING, arraySize, offsetof(AttributedFoo, ExternalStringArray) },
			{ "NestedScope", DatumTypes::TABLE, 1, 0 },
			{ "NestedScopeArray", DatumTypes::TABLE, arraySize, 0 }, 


			{ "ExternalIntD", DatumTypes::INT, 1, offsetof(AttributedFoo, ExternalInt)},
			{ "ExternalFloatD", DatumTypes::FLOAT, 1, offsetof(AttributedFoo, ExternalFloat) },
			{ "ExternalVec4D", DatumTypes::VEC4, 1, offsetof(AttributedFoo, ExternalVec4) },
			{ "ExternalMat4D", DatumTypes::MAT4, 1, offsetof(AttributedFoo, ExternalMat4) },
			{ "ExternalStringD", DatumTypes::STRING, 1, offsetof(AttributedFoo, ExternalString) },
			{ "ExternalIntArrayD", DatumTypes::INT, arraySize, offsetof(AttributedFoo, ExternalIntArray) },
			{ "ExternalFloatArrayD", DatumTypes::FLOAT, arraySize, offsetof(AttributedFoo, ExternalFloatArray) },
			{ "ExternalVec4ArrayD", DatumTypes::VEC4, arraySize, offsetof(AttributedFoo, ExternalVec4Array) },
			{ "ExternalMat4ArrayD", DatumTypes::MAT4, arraySize, offsetof(AttributedFoo, ExternalMat4Array) },
			{ "ExternalStringArrayD", DatumTypes::STRING, arraySize, offsetof(AttributedFoo, ExternalStringArray) },
			{ "NestedScopeD", DatumTypes::TABLE, 1, 0 },
			{ "NestedScopeArrayD", DatumTypes::TABLE, arraySize, 0 }
		};
	}

}