#pragma once
#include "pch.h"
//#include "Foo.h"
#include "ToStringSpecialization.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;


namespace UnitTests
{
	TEST_CLASS(AttributedFooTest)
	{

	public:

		TEST_METHOD_INITIALIZE(TestModuleInitalize)
		{
			TypeRegistry* registry = TypeRegistry::GetInstance();
			registry->AddEntry(std::make_pair<size_t,const Vector<Signature>>(AttributedFoo::TypeIdClass(), AttributedFoo::GetSignature()));
			registry->AddEntry(std::make_pair<size_t,const Vector<Signature>>(DerivedAttributedFoo::TypeIdClass(), DerivedAttributedFoo::GetSignature()));
			
			
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif

		}


		TEST_METHOD_CLEANUP(TestModuleCleanUp)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"There was a Memory Leak!! :{");
			}
#endif
		}


		TEST_METHOD(RTTITest)
		{
			AttributedFoo f;
			f.AppendAuxiliaryAttribute("testAux");

			Attributed* a = f.As<Attributed>();
			Assert::IsTrue(a->Is(AttributedFoo::TypeIdClass()));
			
			Assert::AreEqual(f.ToString(), a->ToString());
			Assert::AreNotEqual(f.ToString(), f.Attributed::ToString());
			
			Assert::IsTrue(f.Equals(a));



			DerivedAttributedFoo d;
			d.AppendAuxiliaryAttribute("testAux");

			Attributed* a2 = d.As<Attributed>();
			Assert::IsTrue(a2->Is(DerivedAttributedFoo::TypeIdClass()));

			Assert::AreEqual(d.ToString(), a2->ToString());
			Assert::AreNotEqual(d.ToString(), d.Attributed::ToString());

			Assert::IsTrue(d.Equals(a2));



		}




		
		TEST_METHOD(Constructor)
		{
			AttributedFoo f;

			auto a = f.Find("ExternalInt");
			auto b = f.Find("ExternalFloat");

			f.AppendAuxiliaryAttribute("testAux");
			Assert::AreEqual(12, a->Get<int32_t>());
			Assert::AreEqual(4.0f, b->Get<float>());
			Assert::IsFalse(f.IsEmpty());
			Assert::AreEqual(size_t(14), f.Size());


			DerivedAttributedFoo d;

			auto c = d.Find("ExternalInt");
			auto d2 = d.Find("ExternalFloat");

			d.AppendAuxiliaryAttribute("testAux");
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d2->Get<float>());
			Assert::IsFalse(d.IsEmpty());
			Assert::AreEqual(size_t(26), d.Size());




		}

		TEST_METHOD(CopyConstructor)
		{
			AttributedFoo f;
			Datum* s = &f.AppendAuxiliaryAttribute("testAux");

			*s = 200;

			Assert::IsFalse(f.IsEmpty());
			Assert::AreEqual(size_t(14), f.Size());

			AttributedFoo f2 = f;

			auto a = f.Find("ExternalInt");
			auto b = f.Find("ExternalFloat");

			auto c = f2.Find("ExternalInt");
			auto d = f2.Find("ExternalFloat");

			Assert::AreEqual(12, a->Get<int32_t>());
			Assert::AreEqual(4.0f, b->Get<float>());
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());
			
			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());

			Assert::AreEqual(s->Type(), f2.Append("testAux").Type());
			Assert::AreEqual(s->Get<int32_t>(), f2.Append("testAux").Get<int32_t>());

			f.ClearList();
			
			Assert::IsTrue(f.IsEmpty());
			Assert::AreEqual(size_t(0), f.Size());
			
			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());
			Assert::AreEqual(int32_t(200), f2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());
			

			
			DerivedAttributedFoo d2;
			Datum* sd2 = &d2.AppendAuxiliaryAttribute("testAux");

			*sd2 = 200;

			Assert::IsFalse(d2.IsEmpty());
			Assert::AreEqual(size_t(26), d2.Size());

			AttributedFoo df2 = d2;

			auto a2 = d2.Find("ExternalInt");
			auto b2 = d2.Find("ExternalFloat");

			auto c2 = df2.Find("ExternalInt");
			auto dd2 = df2.Find("ExternalFloat");

			Assert::AreEqual(12, a2->Get<int32_t>());
			Assert::AreEqual(4.0f, b2->Get<float>());
			Assert::AreEqual(12, c2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());

			Assert::AreEqual(sd2->Type(), df2.Append("testAux").Type());
			Assert::AreEqual(sd2->Get<int32_t>(), df2.Append("testAux").Get<int32_t>());

			d2.ClearList();

			Assert::IsTrue(d2.IsEmpty());
			Assert::AreEqual(size_t(0), d2.Size());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());
			Assert::AreEqual(int32_t(200), df2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, c2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());

		}

		TEST_METHOD(MoveConstructor)
		{
			AttributedFoo f;
			Datum* s = &f.AppendAuxiliaryAttribute("testAux");

			*s = 200;

			Assert::IsFalse(f.IsEmpty());
			Assert::AreEqual(size_t(14), f.Size());

			auto a = f.Find("ExternalInt");
			auto b = f.Find("ExternalFloat");

			Assert::AreEqual(12, a->Get<int32_t>());
			Assert::AreEqual(4.0f, b->Get<float>());

			AttributedFoo f2 = std::move(f);

			Datum* s2 = f2.Find("testAux");

			Assert::AreEqual(s2->Type(), f2.Append("testAux").Type());
			Assert::AreEqual(s2->Get<int32_t>(), f2.Append("testAux").Get<int32_t>());

			Assert::IsTrue(f.IsEmpty());
			Assert::AreEqual(size_t(0), f.Size());

			auto c = f2.Find("ExternalInt");
			auto d = f2.Find("ExternalFloat");

			
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());

			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());

			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());
			Assert::AreEqual(int32_t(200), f2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());





			DerivedAttributedFoo df;
			Datum* sdf = &df.AppendAuxiliaryAttribute("testAux");

			*sdf = 200;

			Assert::IsFalse(df.IsEmpty());
			Assert::AreEqual(size_t(26), df.Size());

			auto ad2 = df.Find("ExternalInt");
			auto bd2 = df.Find("ExternalFloat");

			Assert::AreEqual(12, ad2->Get<int32_t>());
			Assert::AreEqual(4.0f, bd2->Get<float>());

			AttributedFoo df2 = std::move(df);

			Datum* s2df = df2.Find("testAux");

			Assert::AreEqual(s2df->Type(), df2.Append("testAux").Type());
			Assert::AreEqual(s2df->Get<int32_t>(), df2.Append("testAux").Get<int32_t>());

			Assert::IsTrue(df.IsEmpty());
			Assert::AreEqual(size_t(0), df.Size());

			auto cd2 = df2.Find("ExternalInt");
			auto dd2 = df2.Find("ExternalFloat");


			Assert::AreEqual(12, cd2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());
			Assert::AreEqual(int32_t(200), df2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, cd2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());
		}


		TEST_METHOD(CopyAssignment)
		{
			AttributedFoo f;
			Datum* s = &f.AppendAuxiliaryAttribute("testAux");

			*s = 200;

			Assert::IsFalse(f.IsEmpty());
			Assert::AreEqual(size_t(14), f.Size());

			AttributedFoo f2;
			
			f2 = f;

			auto a = f.Find("ExternalInt");
			auto b = f.Find("ExternalFloat");

			auto c = f2.Find("ExternalInt");
			auto d = f2.Find("ExternalFloat");

			Assert::AreEqual(12, a->Get<int32_t>());
			Assert::AreEqual(4.0f, b->Get<float>());
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());

			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());

			Assert::AreEqual(s->Type(), f2.Append("testAux").Type());
			Assert::AreEqual(s->Get<int32_t>(), f2.Append("testAux").Get<int32_t>());

			f.ClearList();

			Assert::IsTrue(f.IsEmpty());
			Assert::AreEqual(size_t(0), f.Size());

			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());
			Assert::AreEqual(int32_t(200), f2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());



			DerivedAttributedFoo d2;
			Datum* sd2 = &d2.AppendAuxiliaryAttribute("testAux");

			*sd2 = 200;

			Assert::IsFalse(d2.IsEmpty());
			Assert::AreEqual(size_t(26), d2.Size());

			AttributedFoo df2;
			
			df2 = d2;

			auto a2 = d2.Find("ExternalInt");
			auto b2 = d2.Find("ExternalFloat");

			auto c2 = df2.Find("ExternalInt");
			auto dd2 = df2.Find("ExternalFloat");

			Assert::AreEqual(12, a2->Get<int32_t>());
			Assert::AreEqual(4.0f, b2->Get<float>());
			Assert::AreEqual(12, c2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());

			Assert::AreEqual(sd2->Type(), df2.Append("testAux").Type());
			Assert::AreEqual(sd2->Get<int32_t>(), df2.Append("testAux").Get<int32_t>());

			d2.ClearList();

			Assert::IsTrue(d2.IsEmpty());
			Assert::AreEqual(size_t(0), d2.Size());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());
			Assert::AreEqual(int32_t(200), df2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, c2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());
		}

		TEST_METHOD(MoveAssignment)
		{
			AttributedFoo f;
			Datum* s = &f.AppendAuxiliaryAttribute("testAux");

			*s = 200;

			Assert::IsFalse(f.IsEmpty());
			Assert::AreEqual(size_t(14), f.Size());

			auto a = f.Find("ExternalInt");
			auto b = f.Find("ExternalFloat");

			Assert::AreEqual(12, a->Get<int32_t>());
			Assert::AreEqual(4.0f, b->Get<float>());

			AttributedFoo f2;
			
			f2 = std::move(f);

			Datum* s2 = f2.Find("testAux");

			Assert::AreEqual(s2->Type(), f2.Append("testAux").Type());
			Assert::AreEqual(s2->Get<int32_t>(), f2.Append("testAux").Get<int32_t>());

			Assert::IsTrue(f.IsEmpty());
			Assert::AreEqual(size_t(0), f.Size());

			auto c = f2.Find("ExternalInt");
			auto d = f2.Find("ExternalFloat");


			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());

			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());

			Assert::IsFalse(f2.IsEmpty());
			Assert::AreEqual(size_t(14), f2.Size());
			Assert::AreEqual(int32_t(200), f2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, c->Get<int32_t>());
			Assert::AreEqual(4.0f, d->Get<float>());


			DerivedAttributedFoo df;
			Datum* sdf = &df.AppendAuxiliaryAttribute("testAux");

			*sdf = 200;

			Assert::IsFalse(df.IsEmpty());
			Assert::AreEqual(size_t(26), df.Size());

			auto ad2 = df.Find("ExternalInt");
			auto bd2 = df.Find("ExternalFloat");

			Assert::AreEqual(12, ad2->Get<int32_t>());
			Assert::AreEqual(4.0f, bd2->Get<float>());

			DerivedAttributedFoo df2;
			
			df2 = std::move(df);

			Datum* s2df = df2.Find("testAux");

			Assert::AreEqual(s2df->Type(), df2.Append("testAux").Type());
			Assert::AreEqual(s2df->Get<int32_t>(), df2.Append("testAux").Get<int32_t>());

			Assert::IsTrue(df.IsEmpty());
			Assert::AreEqual(size_t(0), df.Size());

			auto cd2 = df2.Find("ExternalInt");
			auto dd2 = df2.Find("ExternalFloat");


			Assert::AreEqual(12, cd2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());

			Assert::IsFalse(df2.IsEmpty());
			Assert::AreEqual(size_t(26), df2.Size());
			Assert::AreEqual(int32_t(200), df2.Append("testAux").Get<int32_t>());
			Assert::AreEqual(12, cd2->Get<int32_t>());
			Assert::AreEqual(4.0f, dd2->Get<float>());



		}


		TEST_METHOD(IsAttribute)
		{
			AttributedFoo f;
			f.AppendAuxiliaryAttribute("testAux");

			Assert::IsTrue(f.IsAttribute("this"));
			Assert::IsTrue(f.IsAttribute("ExternalInt"));
			Assert::IsTrue(f.IsAttribute("ExternalFloat"));
			Assert::IsTrue(f.IsAttribute("ExternalVec4"));
			Assert::IsTrue(f.IsAttribute("ExternalMat4"));
			Assert::IsTrue(f.IsAttribute("ExternalString"));
			Assert::IsTrue(f.IsAttribute("ExternalIntArray"));
			Assert::IsTrue(f.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(f.IsAttribute("ExternalVec4Array"));
			Assert::IsTrue(f.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(f.IsAttribute("NestedScope"));
			Assert::IsTrue(f.IsAttribute("NestedScopeArray"));
			Assert::IsTrue(f.IsAttribute("testAux"));




			DerivedAttributedFoo d;
			d.AppendAuxiliaryAttribute("testAux");

			Assert::IsTrue(d.IsAttribute("this"));
			Assert::IsTrue(d.IsAttribute("ExternalInt"));
			Assert::IsTrue(d.IsAttribute("ExternalFloat"));
			Assert::IsTrue(d.IsAttribute("ExternalVec4"));
			Assert::IsTrue(d.IsAttribute("ExternalMat4"));
			Assert::IsTrue(d.IsAttribute("ExternalString"));
			Assert::IsTrue(d.IsAttribute("ExternalIntArray"));
			Assert::IsTrue(d.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(d.IsAttribute("ExternalVec4Array"));
			Assert::IsTrue(d.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(d.IsAttribute("NestedScope"));
			Assert::IsTrue(d.IsAttribute("NestedScopeArray"));
			Assert::IsTrue(d.IsAttribute("testAux"));

			Assert::IsTrue(d.IsAttribute("ExternalIntD"));
			Assert::IsTrue(d.IsAttribute("ExternalFloatD"));
			Assert::IsTrue(d.IsAttribute("ExternalVec4D"));
			Assert::IsTrue(d.IsAttribute("ExternalMat4D"));
			Assert::IsTrue(d.IsAttribute("ExternalStringD"));
			Assert::IsTrue(d.IsAttribute("ExternalIntArrayD"));
			Assert::IsTrue(d.IsAttribute("ExternalFloatArrayD"));
			Assert::IsTrue(d.IsAttribute("ExternalVec4ArrayD"));
			Assert::IsTrue(d.IsAttribute("ExternalStringArrayD"));
			Assert::IsTrue(d.IsAttribute("NestedScopeD"));
			Assert::IsTrue(d.IsAttribute("NestedScopeArrayD"));
			Assert::IsTrue(d.IsAttribute("testAux"));
					
					
		}				
					

		TEST_METHOD(IsPrescribedAttribute)
		{
			AttributedFoo f;
			f.AppendAuxiliaryAttribute("testAux");
			Assert::IsTrue(f.IsPrescribedAttribute("this"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInt"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalVec4"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalMat4"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalIntArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalVec4Array"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(f.IsPrescribedAttribute("NestedScopeArray"));
			Assert::IsFalse(f.IsPrescribedAttribute("testAux"));



			DerivedAttributedFoo d;
			d.AppendAuxiliaryAttribute("testAux");

			Assert::IsTrue(d.IsPrescribedAttribute("this"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalInt"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalVec4"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalMat4"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalIntArray"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalVec4Array"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(d.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(d.IsPrescribedAttribute("NestedScopeArray"));
			Assert::IsFalse(d.IsPrescribedAttribute("testAux"));


			Assert::IsTrue(d.IsPrescribedAttribute("ExternalIntD"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalFloatD"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalVec4D"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalMat4D"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalStringD"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalIntArrayD"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalFloatArrayD"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalVec4ArrayD"));
			Assert::IsTrue(d.IsPrescribedAttribute("ExternalStringArrayD"));
			Assert::IsTrue(d.IsPrescribedAttribute("NestedScopeD"));
			Assert::IsTrue(d.IsPrescribedAttribute("NestedScopeArrayD"));

		}


		TEST_METHOD(IsAuxiliaryAttribute)
		{
			AttributedFoo f;
			f.AppendAuxiliaryAttribute("testAux");
			Assert::IsFalse(f.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInt"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalVec4"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalMat4"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalIntArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalVec4Array"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("NestedScopeArray"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("testAux"));



			DerivedAttributedFoo d;
			d.AppendAuxiliaryAttribute("testAux");
			Assert::IsFalse(d.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalInt"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalVec4"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalMat4"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalIntArray"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalVec4Array"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("NestedScopeArray"));
			Assert::IsTrue(d.IsAuxiliaryAttribute("testAux"));


			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalIntD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalFloatD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalVec4D"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalMat4D"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalStringD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalIntArrayD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalFloatArrayD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalVec4ArrayD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("ExternalStringArrayD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("NestedScopeD"));
			Assert::IsFalse(d.IsAuxiliaryAttribute("NestedScopeArrayD"));

		}

		TEST_METHOD(AppendAuxiliaryAttribute)
		{
			AttributedFoo f;
			Assert::AreEqual(size_t(13), f.Size());
			Datum* datum = &f.AppendAuxiliaryAttribute("testAux");
			Assert::IsTrue(&f["testAux"] == datum);

			auto BadAppend = [&f] {f.AppendAuxiliaryAttribute("ExternalInt"); };
			Assert::ExpectException<std::runtime_error>(BadAppend);

			Assert::AreEqual(size_t(14), f.Size());


			DerivedAttributedFoo d;
			Assert::AreEqual(size_t(25), d.Size());
			Datum* datum2 = &d.AppendAuxiliaryAttribute("testAux");
			Assert::IsTrue(&d["testAux"] == datum2);

			auto BadAppend2 = [&d] {d.AppendAuxiliaryAttribute("ExternalInt"); };
			Assert::ExpectException<std::runtime_error>(BadAppend2);

			Assert::AreEqual(size_t(26), d.Size());

		}




	private:
		static _CrtMemState _startMemState;


	};

	_CrtMemState AttributedFooTest::_startMemState;
}