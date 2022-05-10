#pragma once
#include "AttributedFoo.h"
#include "Signature.h"

using namespace FieaGameEngine;

namespace FooSupport
{
	class DerivedAttributedFoo final : public AttributedFoo
	{
		RTTI_DECLARATIONS(DerivedAttributedFoo, AttributedFoo)

	public:

		DerivedAttributedFoo();
		virtual ~DerivedAttributedFoo() = default;
		DerivedAttributedFoo(const DerivedAttributedFoo& other) = default;
		DerivedAttributedFoo& operator=(const DerivedAttributedFoo& other) = default;
		DerivedAttributedFoo(DerivedAttributedFoo&& other) = default;
		DerivedAttributedFoo& operator=(DerivedAttributedFoo&& other) = default;

		virtual std::string ToString() const override;
		//virtual bool Equals(const RTTI* rhs) const override;
		virtual DerivedAttributedFoo* Clone() const override;

		static const Vector<Signature> GetSignature();




		static const int32_t arraySize = 5;

		int32_t ExternalIntD = 12;
		float ExternalFloatD = 4.0f;
		glm::vec4 ExternalVec4D;
		glm::mat4 ExternalMat4D;
		std::string ExternalStringD;

		int32_t ExternalIntArrayD[arraySize];
		float ExternalFloatArrayD[arraySize];
		glm::vec4 ExternalVec4ArrayD[arraySize];
		glm::mat4 ExternalMat4ArrayD[arraySize];
		std::string ExternalStringArrayD[arraySize];




	};
}
