#pragma once
//#include "Attributed.h"
#include "JsonTableParseHelper.h"
#include "Signature.h"

using namespace FieaGameEngine;

namespace FooSupport
{
	class AttributedFoo : public Attributed 
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)

	public:

		AttributedFoo();
		AttributedFoo(IdType typeID);
		virtual ~AttributedFoo() = default;
		AttributedFoo(const AttributedFoo& other) = default;
		AttributedFoo& operator=(const AttributedFoo& other) = default;
		AttributedFoo(AttributedFoo&& other) = default;
		AttributedFoo& operator=(AttributedFoo&& other) = default;

		virtual std::string ToString() const override;
		//virtual bool Equals(const RTTI* rhs) const override;
		virtual AttributedFoo* Clone() const override;

		static const Vector<Signature> GetSignature();




		static const int32_t arraySize = 5;

		int32_t ExternalInt = 12;
		float ExternalFloat = 4.0f;
		glm::vec4 ExternalVec4;
		glm::mat4 ExternalMat4;
		std::string ExternalString;

		int32_t ExternalIntArray[arraySize];
		float ExternalFloatArray[arraySize];
		glm::vec4 ExternalVec4Array[arraySize];
		glm::mat4 ExternalMat4Array[arraySize];
		std::string ExternalStringArray[arraySize];
		


		//const Vector<Signature> _signatures;

	};

	ConcreteFactory(AttributedFoo, Scope)
}
