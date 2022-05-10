#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(FooTest)
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

		TEST_METHOD(Constructor)
		{
			Foo f{ 10 };
			const Foo g{ 20 };

			Assert::AreEqual(10, f.Data());
			Assert::AreEqual(20, g.Data());
		}

		TEST_METHOD(CopyConstructor)
		{
			Foo f{ 10 };


			Foo g(f);

			Assert::AreEqual(f.Data(), g.Data());
		}


		TEST_METHOD(CopyOperator)
		{
			Foo f{ 10 };

			Foo g{ 0 };

			Assert::AreNotEqual(f.Data(), g.Data());

			g = f;

			Assert::AreEqual(f.Data(), g.Data());

		}


		TEST_METHOD(Data)
		{
			Foo f{ 10 };
			

			Assert::AreEqual(10, f.Data());
			
		}

		TEST_METHOD(DataConst)
		{
			const Foo g{ 20 };

			Assert::AreEqual(20, g.Data());
		}


		TEST_METHOD(EqualOperator)
		{
			Foo f{ 10 };
			Foo g{ 20 };

			Assert::IsFalse(f == g);

			Foo k{ 10 };

			Assert::IsTrue(f == k);
			Assert::IsTrue(f == f);
		}

		TEST_METHOD(NotEqualOperator)
		{
			Foo f{ 10 };
			Foo g{ 20 };

			Assert::IsTrue(f != g);

			Foo k{ 10 };

			Assert::IsFalse(f != k);
		}

	


	private:
		//Static is not const, Static is persistent and only created once and before any of the methods run
		static _CrtMemState _startMemState;



	};

	_CrtMemState FooTest::_startMemState;

}
