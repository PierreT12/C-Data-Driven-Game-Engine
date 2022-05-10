#pragma once
//#include "JsonTableParseHelper.h"
#include "pch.h"
#include "Foo.h"
#include "AttributedFoo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(FactoryTest)
	{
	public:
		const std::string f = "Foo";
		const std::string s = "Scope";



		TEST_METHOD_INITIALIZE(Initalize)
		{
			TypeRegistry* registry = TypeRegistry::GetInstance();
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(AttributedFoo::TypeIdClass(), AttributedFoo::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(GameObject::TypeIdClass(), GameObject::GetSignature()));


#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(CleanUp)
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

		TEST_METHOD(Constructor)
		{
			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());
		}

		TEST_METHOD(GetClassName)
		{
			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			Assert::AreEqual(size_t(0), Factory<Scope>::Size());
			Assert::IsTrue(Factory<Scope>::IsEmpty());

			FooFactory foo;
			ScopeFactory sf;

			Assert::AreEqual(size_t(1), Factory<RTTI>::Size());
			Assert::IsFalse(Factory<RTTI>::IsEmpty());

			Assert::AreEqual(size_t(1), Factory<Scope>::Size());
			Assert::IsFalse(Factory<Scope>::IsEmpty());

			const std::string& fooName = foo.ClassName();

			Assert::AreEqual(f, fooName);

			const std::string& scopeName = sf.ClassName();

			Assert::AreEqual(s, scopeName);


		}


		TEST_METHOD(AddRemove)
		{
			const Factory<RTTI>* nullfound = Factory<RTTI>::Find(f);

			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			Assert::IsNull(nullfound);

			FooFactory foo;
			
			Assert::AreEqual(size_t(1), Factory<RTTI>::Size());
			Assert::IsFalse(Factory<RTTI>::IsEmpty());

			const Factory<RTTI>* found = Factory<RTTI>::Find(f);

			Assert::IsNotNull(found);


			foo.~FooFactory();

			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());
		}


		TEST_METHOD(CreateFactory)
		{
			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			FooFactory foo;

			Assert::AreEqual(size_t(1), Factory<RTTI>::Size());
			Assert::IsFalse(Factory<RTTI>::IsEmpty());

			const Factory<RTTI>* found = Factory<RTTI>::Find(f);

			Assert::IsNotNull(found);

			RTTI* foundFoo = Factory<RTTI>::Create("Foo")->As<Foo>();

			Assert::IsNotNull(foundFoo);

			Assert::IsTrue(foundFoo->Is(Foo::TypeIdClass()));

			Assert::AreEqual(int32_t(0), foundFoo->As<Foo>()->Data());
			
			delete foundFoo;


			auto CreateFail = [] {Factory<RTTI>::Create("RandomFailString"); };
			Assert::ExpectException<std::runtime_error>(CreateFail);


			foo.~FooFactory();

			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

		}

		TEST_METHOD(Find)
		{
			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			const Factory<RTTI>* nullfound = Factory<RTTI>::Find(f);

			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			Assert::IsNull(nullfound);

			FooFactory foo;

			Assert::AreEqual(size_t(1), Factory<RTTI>::Size());
			Assert::IsFalse(Factory<RTTI>::IsEmpty());

			const Factory<RTTI>* found = Factory<RTTI>::Find(f);

			Assert::IsNotNull(found);

			foo.~FooFactory();


			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

		}

		TEST_METHOD(Clear)
		{
			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			FooFactory foo;

			Assert::AreEqual(size_t(1), Factory<RTTI>::Size());
			Assert::IsFalse(Factory<RTTI>::IsEmpty());


			Factory<RTTI>::ClearList();


			Assert::AreEqual(size_t(0), Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

		}

		TEST_METHOD(Parsing)
		{
			Assert::AreEqual(size_t(0), Factory<Scope>::Size());
			Assert::IsTrue(Factory<Scope>::IsEmpty());


			ScopeFactory sf;
			GameObjectFactory gf;


			Assert::AreEqual(size_t(2), Factory<Scope>::Size());
			Assert::IsFalse(Factory<Scope>::IsEmpty());

			AttributedFooFactory af;

			Assert::AreEqual(size_t(3), Factory<Scope>::Size());
			Assert::IsFalse(Factory<Scope>::IsEmpty());


			std::string input = R"({
									 "Player": {
										 "type": "table",
										"class" : "AttributedFoo",
										 "value": {
										     "Health": {
										         "type": "integer",
										         "value": 100
										     },
										     "DPS": {
										         "type": "float",
										         "value": 12.5
												}
											 }
										}
									})";


			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.Parse(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			std::string player = "Player";
			std::string health = "Health";
			std::string dps = "DPS";

			Assert::AreEqual(size_t(15), dataWrapper._currentContext->Find(player)[0][0].Size());
			Assert::AreEqual(int32_t(100), dataWrapper._currentContext->Find(player)[0][0].Find(health)->Back<int32_t>());
			Assert::AreEqual(12.5f, dataWrapper._currentContext->Find(player)[0][0].Find(dps)->Back<float>());


			sf.~ScopeFactory();

			Assert::AreEqual(size_t(2), Factory<Scope>::Size());
			Assert::IsFalse(Factory<Scope>::IsEmpty());
			

			af.~AttributedFooFactory();

			Assert::AreEqual(size_t(1), Factory<Scope>::Size());
			Assert::IsFalse(Factory<Scope>::IsEmpty());

		}


	private:
		static _CrtMemState _startMemState;



	};

	_CrtMemState FactoryTest::_startMemState;

}