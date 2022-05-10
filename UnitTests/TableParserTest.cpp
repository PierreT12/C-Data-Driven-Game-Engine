#include "pch.h"
#include "Foo.h"
#include "JsonTableParseHelper.h"
#include "JsonParseHelperInt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(TableParserTest)
	{
	public:

		ScopeFactory s;
		GameObjectFactory gf;

		TEST_METHOD_INITIALIZE(Initalize)
		{
			TypeRegistry* registry = TypeRegistry::GetInstance();
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

		TEST_METHOD(ObjectParsing)
		{
			std::string input = R"({"Health": {"type": "integer", "value": 100}})";


			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);

			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.Parse(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			Assert::IsNotNull(dataWrapper._currentContext);

			std::string health = "Health";

			Assert::IsNotNull(dataWrapper._currentContext->Find(health));

			Assert::IsTrue(dataWrapper._currentContext->Find(health)->Size() > 0);
			Assert::AreEqual(int32_t(100), dataWrapper._currentContext->Find(health)->Back<int32_t>());



		}

		TEST_METHOD(ObjectArrayParsing)
		{
			std::string input = R"({"Health":{"type":"integer","value":[100,200,300,400,500,600]}})";


			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.Parse(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			std::string health = "Health";

			Assert::AreEqual(int32_t(100), dataWrapper._currentContext->Find(health)->Get<int32_t>(0));
			Assert::AreEqual(int32_t(200), dataWrapper._currentContext->Find(health)->Get<int32_t>(1));
			Assert::AreEqual(int32_t(300), dataWrapper._currentContext->Find(health)->Get<int32_t>(2));
			Assert::AreEqual(int32_t(400), dataWrapper._currentContext->Find(health)->Get<int32_t>(3));
			Assert::AreEqual(int32_t(500), dataWrapper._currentContext->Find(health)->Get<int32_t>(4));
			Assert::AreEqual(int32_t(600), dataWrapper._currentContext->Find(health)->Get<int32_t>(5));

		}


		TEST_METHOD(NestedObjectParsing)
		{
			std::string input = R"({
									 "Player": {
										 "type": "table",
										"class" : "Scope",
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

			Assert::AreEqual(int32_t(100), dataWrapper._currentContext->Find(player)[0][0].Find(health)->Back<int32_t>());
			Assert::AreEqual(12.5f, dataWrapper._currentContext->Find(player)[0][0].Find(dps)->Back<float>());

		}


		TEST_METHOD(NestedArrayObjectParsing)
		{
			std::string input = R"({
								       "Player": {
								           "type": "table",
								           "value": {
								               "Health": {
								                   "type": "integer",
								                   "value": 100
								               },
								               "DPS": {
								                   "type": "float",
								                   "value": 12.5
								               },
								               "Abilities CoolDown": {
								                   "type": "table",
								                   "value": [
								                       {
								                           "Jump": {
								                               "type": "integer",
								                               "value": 2
								                           }
								                       },
								                       {
								                           "Kick": {
								                               "type": "integer",
								                               "value": 4
								                           }
								                       },
								                       {
								                           "Punch": {
								                               "type": "integer",
								                               "value": 5
								                           }
								                       },
								                       {
								                           "Fly": {
								                               "type": "integer",
								                               "value": 10
								                           }
								                       }
								                   ]
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
			std::string abcd = "Abilities CoolDown";
			std::string jump = "Jump";
			std::string kick = "Kick";
			std::string punch = "Punch";
			std::string fly = "Fly";

			Assert::AreEqual(int32_t(100), dataWrapper._currentContext->Find(player)[0][0].Find(health)->Back<int32_t>());
			Assert::AreEqual(12.5f, dataWrapper._currentContext->Find(player)[0][0].Find(dps)->Back<float>());
			Assert::AreEqual(int32_t(2), dataWrapper._currentContext->Find(player)[0][0].Find(abcd)[0][0].Find(jump)->Back<int32_t>());
			Assert::AreEqual(int32_t(4), dataWrapper._currentContext->Find(player)[0][0].Find(abcd)[0][0].Find(kick)->Back<int32_t>());
			Assert::AreEqual(int32_t(5), dataWrapper._currentContext->Find(player)[0][0].Find(abcd)[0][0].Find(punch)->Back<int32_t>());
			Assert::AreEqual(int32_t(10), dataWrapper._currentContext->Find(player)[0][0].Find(abcd)[0][0].Find(fly)->Back<int32_t>());

		}

		TEST_METHOD(CreateHandlerAndWrapper)
		{
			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			JsonParseMaster* pm2 = parseMaster.Clone();

			Assert::IsNotNull(pm2->GetDataWrapper());

			delete pm2;
		}

		TEST_METHOD(Equals)
		{
			std::string input = R"(
									{
									  "Health":
									  {
									    "type": "integer",
									    "value": 100
									  }
									}
								)";


			JsonTableParseHelper tableHelper;
			JsonTableParseHelper tableHelper2;
			JsonTableParseHelper::DataWrapper dataWrapper;
			JsonTableParseHelper::DataWrapper dataWrapper2;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);



			Assert::IsTrue(dataWrapper.Equals(&dataWrapper));
			Assert::IsTrue(tableHelper.Equals(&tableHelper));

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.Parse(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			Assert::IsFalse(dataWrapper.Equals(&dataWrapper2));
			Assert::IsFalse(tableHelper.Equals(&tableHelper2));

		}

		TEST_METHOD(ToString)
		{

			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			std::string dataWrapperStr = "JsonTableParseHelper's DataWrapper!! :D";
			std::string helperStr = "JsonTableParseHelper!! :D";


			Assert::AreEqual(dataWrapper.ToString(), dataWrapperStr);
			Assert::AreEqual(tableHelper.ToString(), helperStr);


		}

		TEST_METHOD(StartEndHandler)
		{
			std::string input = R"(
									{
									  "Health":
									  {
									    "type": "integer",
									    "value": 100
									  }
									}
								)";


			std::string emptyInput = "";

			std::string brokenInput = R"(
									{
									  "Health":
									  {
									    "type": "bool",
									    "value": 100
									  }
									}
								)";

			JsonTableParseHelper tableHelper;
			JsonParseHelperInt intHelper;
			JsonParseHelperInt::DataWrapper dataWrapper;
			JsonTableParseHelper::DataWrapper dataWrapper2;

			
			JsonParseMaster parseMaster(dataWrapper);
			


			Assert::IsFalse(tableHelper.StartHandler(dataWrapper, input, input));
			Assert::IsFalse(tableHelper.StartHandler(dataWrapper2, emptyInput, input));

			auto FailedEnd = [&tableHelper, &dataWrapper, &input] {tableHelper.EndHandler(dataWrapper, input, false); };
			Assert::ExpectException<std::runtime_error>(FailedEnd);

			JsonParseMaster parseMaster2(dataWrapper2);
			parseMaster2.AddHelper(tableHelper);

			auto FailedParse = [&parseMaster2, &brokenInput] {parseMaster2.Parse(brokenInput); };
			Assert::ExpectException<std::runtime_error>(FailedParse);



		}


	private:
		static _CrtMemState _startMemState;



	};

	_CrtMemState TableParserTest::_startMemState;

}
