#pragma once
#include "pch.h"
#include "Foo.h"
#include <string>
#include "ToStringSpecialization.h"
#include"DefaultHashFoo.inl"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;


namespace UnitTests
{
	TEST_CLASS(DefaultHashTest)
	{

	public:
		TEST_METHOD_INITIALIZE(Initalize)
		{
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



		TEST_METHOD(DefaultHashint)
		{
			DefaultHash<size_t> hash;
			size_t a = 10;
			size_t b = 75;
			size_t c(a);


			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));
		}

		TEST_METHOD(DefaultHashfloat)
		{
			DefaultHash<float> hash;
			float a = 1.0f;
			float b = 75.5f;
			float c(a);


			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));
		}

		TEST_METHOD(DefaultHashdouble)
		{
			DefaultHash<double> hash;
			double a = 10.25;
			double b = 75.45;
			double c(a);


			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));
		}

		TEST_METHOD(DefaultHashstring)
		{
			DefaultHash<std::string> hash;
			std::string a = "Hello";
			std::string b = "GoodBye";
			std::string c(a);


			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));

			DefaultHash<const std::string> hashconst;
			const std::string ac = "Hello";
			const std::string bc = "GoodBye";
			const std::string cc(ac);


			Assert::AreEqual(hashconst(ac), hashconst(ac));
			Assert::AreEqual(hashconst(ac), hashconst(cc));
			Assert::AreNotEqual(hashconst(ac), hashconst(bc));
			Assert::AreNotEqual(hashconst(bc), hashconst(cc));

		}

		TEST_METHOD(DefaultHashwstring)
		{
			DefaultHash<std::wstring> hash;
			std::wstring a = L"Hello";
			std::wstring b = L"GoodBye";
			std::wstring c(a);


			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));


			DefaultHash<const std::wstring> hashconst;
			const std::wstring ac = L"Hello";
			const std::wstring bc = L"GoodBye";
			const std::wstring cc(ac);


			Assert::AreEqual(hashconst(a), hashconst(a));
			Assert::AreEqual(hashconst(a), hashconst(c));
			Assert::AreNotEqual(hashconst(a), hashconst(b));
			Assert::AreNotEqual(hashconst(b), hashconst(c));
		}

		TEST_METHOD(DefaultHashcharPtr)
		{
			DefaultHash<char*> hash;
			char* a = "Hello";
			char* b = "GoodBye";
			char* c(a);


			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));

			DefaultHash<const char*> hashconst;
			const char* ac = "Hello";
			const char* bc = "GoodBye";
			const char* cc(ac);


			Assert::AreEqual(hashconst(ac), hashconst(ac));
			Assert::AreEqual(hashconst(ac), hashconst(cc));
			Assert::AreNotEqual(hashconst(ac), hashconst(bc));
			Assert::AreNotEqual(hashconst(bc), hashconst(cc));
		}

		TEST_METHOD(DefaultHashFoo)
		{
			DefaultHash<Foo> hash;
		
			Foo a{ 10 };
			Foo b{ 75 };
			Foo c(a);
		
		
			Assert::AreEqual(hash(a), hash(a));
			Assert::AreEqual(hash(a), hash(c));
			Assert::AreNotEqual(hash(a), hash(b));
			Assert::AreNotEqual(hash(b), hash(c));

			DefaultHash<const Foo> hashconst;

			const Foo ac{ 10 };
			const Foo bc{ 75 };
			const Foo cc(ac);


			Assert::AreEqual(hashconst(ac), hashconst(ac));
			Assert::AreEqual(hashconst(ac), hashconst(cc));
			Assert::AreNotEqual(hashconst(ac), hashconst(bc));
			Assert::AreNotEqual(hashconst(bc), hashconst(cc));
		}


	




		private:
			static _CrtMemState _startMemState;


	};

	_CrtMemState DefaultHashTest::_startMemState;
}