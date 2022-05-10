#include "pch.h"
#include "Foo.h"
#include "JsonParseHelperInt.h"
#include "JsonTableParseHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(ParseMasterTest)
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

		TEST_METHOD(IntParsing)
		{
			std::string input = R"( {"integer" : 100 })";


			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);


			parseMaster.Parse(input);
			
			Assert::AreEqual(size_t(1), dataWrapper.Data.Size());
			Assert::AreEqual(100, dataWrapper.Data.Front());

		}

		TEST_METHOD(IntArrayParsing)
		{
			std::string input = R"( {"integer" : [100, 200, 300, 400, 500, 600] })";


			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.Parse(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			Assert::AreEqual(size_t(6), dataWrapper.Data.Size());
			Assert::AreEqual(100, dataWrapper.Data.At(0));
			Assert::AreEqual(200, dataWrapper.Data.At(1));
			Assert::AreEqual(300, dataWrapper.Data.At(2));
			Assert::AreEqual(400, dataWrapper.Data.At(3));
			Assert::AreEqual(500, dataWrapper.Data.At(4));
			Assert::AreEqual(600, dataWrapper.Data.At(5));

		}



		TEST_METHOD(Clone)
		{

			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);

			JsonParseMaster* pm2 = parseMaster.Clone();
			
			Assert::IsFalse(pm2 == &parseMaster);
			Assert::IsTrue(pm2 != &parseMaster);

			delete pm2;

		}

		TEST_METHOD(AddRemoveHelper)
		{
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;
			JsonParseHelperInt intHelper2;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);
			Assert::IsFalse(intHelper2.isInitalized);


			parseMaster.RemoveHelper(intHelper);

			JsonParseMaster* pm2 = parseMaster.Clone();

			Assert::IsFalse(pm2 == &parseMaster);
			Assert::IsTrue(pm2 != &parseMaster);

			

			auto FailedAdd = [&pm2, &intHelper] {pm2->AddHelper(intHelper); };
			Assert::ExpectException<std::runtime_error>(FailedAdd);

			auto FailedRemove = [&pm2, &intHelper] {pm2->RemoveHelper(intHelper); };
			Assert::ExpectException<std::runtime_error>(FailedRemove);


			auto FailedRemove2 = [&parseMaster, &intHelper2] {parseMaster.RemoveHelper(intHelper2); };
			Assert::ExpectException<std::runtime_error>(FailedRemove2);


			delete pm2;
		}

		TEST_METHOD(GetSetDataWrapper)
		{
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt::DataWrapper dataWrapper2;
			JsonParseHelperInt intHelper;

			JsonParseMaster parseMaster(dataWrapper);

			parseMaster.SetDataWrapper(dataWrapper2);
			JsonParseHelperInt::DataWrapper* dataWrapperGet = parseMaster.GetDataWrapper()->As<JsonParseHelperInt::DataWrapper>();

			Assert::IsTrue(dataWrapperGet = &dataWrapper2);

			JsonParseMaster* pm2 = parseMaster.Clone();

			auto FailedSet = [&pm2, &dataWrapper] {pm2->SetDataWrapper(dataWrapper); };
			Assert::ExpectException<std::runtime_error>(FailedSet);


			delete pm2;
		}

		TEST_METHOD(GetParseMaster)
		{
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;

			Assert::IsNull(dataWrapper.GetJsonParseMaster());

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);

			Assert::IsNotNull(dataWrapper.GetJsonParseMaster());

			Assert::IsTrue(&parseMaster == dataWrapper.GetJsonParseMaster());
		}

		TEST_METHOD(Depth)
		{
			std::string input = R"( {"integer" : 100 })";


			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;


			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);


			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.Parse(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			Assert::AreEqual(size_t(1), intHelper.StartHandlerCalls);
			Assert::AreEqual(size_t(1), intHelper.EndHandlerCalls);
			Assert::AreEqual(size_t(1), dataWrapper.DeepestDepth);
		}

		TEST_METHOD(MoveConstructorAssignment)
		{
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt::DataWrapper dataWrapper2;
			JsonParseHelperInt intHelper;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);

			JsonParseMaster parseMaster2 = std::move(parseMaster);

			Assert::IsTrue(&parseMaster != &parseMaster2);
			Assert::IsNull(parseMaster.GetDataWrapper());
			Assert::IsNotNull(parseMaster2.GetDataWrapper());


			JsonParseMaster parseMaster3(dataWrapper2);

			parseMaster3 = std::move(parseMaster2);

			Assert::IsTrue(&parseMaster2 != &parseMaster3);
			Assert::IsNull(parseMaster2.GetDataWrapper());
			Assert::IsNotNull(parseMaster3.GetDataWrapper());

		}

		TEST_METHOD(Equals)
		{
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt::DataWrapper dataWrapper2;
			JsonParseHelperInt intHelper;
			JsonParseHelperInt intHelper2;


			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);

			Assert::IsTrue(dataWrapper.Equals(&dataWrapper2));
			Assert::IsTrue(dataWrapper.Equals(&dataWrapper));

			Assert::IsTrue(intHelper.Equals(&intHelper2));
			Assert::IsTrue(intHelper.Equals(&intHelper));

		}

		TEST_METHOD(ToString)
		{
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt intHelper;
			
			
			JsonParseMaster parseMaster(dataWrapper);
			
			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);
			
			
			std::string dataWrapperStr = "JsonParseHelperInt's DataWrapper!!! :D";
			std::string helperStr = "JsonParseHelperInt!!! :D";
			
			
			Assert::AreEqual(dataWrapper.ToString(), dataWrapperStr);
			Assert::AreEqual(intHelper.ToString(), helperStr);
		}

		TEST_METHOD(StartEndHandler)
		{
			std::string input = R"( {"integer" : 100 })";

			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonParseHelperInt::DataWrapper dataWrapper2;
			JsonParseHelperInt intHelper;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(intHelper.isInitalized);
			parseMaster.AddHelper(intHelper);
			Assert::IsTrue(intHelper.isInitalized);

			Json::Value value;
			std::string key = "integer";

			Assert::IsFalse(intHelper.StartHandler(dataWrapper2, input, value));
			Assert::IsTrue(intHelper.StartHandler(dataWrapper2, key, value));

			
			auto FailedStart = [&intHelper, &dataWrapper2, &key, &value] {intHelper.StartHandler(dataWrapper2, key, value); };
			Assert::ExpectException<std::runtime_error>(FailedStart);


			auto FailedEnd = [&intHelper, &dataWrapper2, &input] {intHelper.EndHandler(dataWrapper2, input, false); };
			Assert::ExpectException<std::runtime_error>(FailedEnd);


		}


	private:
		static _CrtMemState _startMemState;



	};

	_CrtMemState ParseMasterTest::_startMemState;

}
