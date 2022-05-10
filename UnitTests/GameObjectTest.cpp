#include "pch.h"
#include "Foo.h"
#include "JsonTableParseHelper.h"
#include "JsonParseHelperInt.h"
#include "Avatar.h"
#include "ToStringSpecialization.h"

#include "ActionIncrement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(GameObjectTest)
	{
	public:
		ActionIncrementFactory aif;
	

		TEST_METHOD_INITIALIZE(Initalize)
		{
			TypeRegistry* registry = TypeRegistry::GetInstance();
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(GameObject::TypeIdClass(), GameObject::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(Avatar::TypeIdClass(), Avatar::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(ActionIncrement::TypeIdClass(), ActionIncrement::GetSignature()));


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

		TEST_METHOD(Construtor)
		{
			GameObject object1;

			Assert::AreEqual("GameObject", object1.GetObjectName().c_str());
			Assert::AreEqual(glm::vec4(0.0), object1.GetPosition());
			Assert::AreEqual(glm::vec4(0.0), object1.GetRotation());
			Assert::AreEqual(glm::vec4(0.0), object1.GetScale());
			Assert::IsNull(object1.GetParent());



			Avatar avatar1;

			Assert::AreEqual("GameObject", avatar1.GetObjectName().c_str());
			Assert::AreEqual(glm::vec4(0.0), avatar1.GetPosition());
			Assert::AreEqual(glm::vec4(0.0), avatar1.GetRotation());
			Assert::AreEqual(glm::vec4(0.0), avatar1.GetScale());
			Assert::IsNull(avatar1.GetParent());
			Assert::AreEqual(int32_t(0), avatar1.GetHealth());
			
		}

		TEST_METHOD(Parse)
		{

			AvatarFactory af;
			ScopeFactory s;
			GameObjectFactory gf;

			std::string input = R"(GameObjectTest2.json)";

			
			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.ParseFromFile(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());


			Assert::AreEqual(size_t(9), dataWrapper._currentContext->Size());
			Assert::IsNotNull(dataWrapper._currentContext->Find("Name"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Position"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Rotation"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Scale"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Tag"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Children"));
			Assert::AreEqual("Root Game Object", dataWrapper._currentContext->Find("Name")->Back<std::string>().c_str());
			Assert::AreEqual(glm::vec4(1), dataWrapper._currentContext->Find("Position")->Back<glm::vec4>());
			Assert::AreEqual(glm::vec4(1), dataWrapper._currentContext->Find("Rotation")->Back<glm::vec4>());
			Assert::AreEqual(glm::vec4(1), dataWrapper._currentContext->Find("Scale")->Back<glm::vec4>());
			Assert::AreEqual("root", dataWrapper._currentContext->Find("Tag")->Back<std::string>().c_str());
			
			
			Assert::IsNotNull(dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 1"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2"));
			
			Assert::AreEqual("GameObject Child One", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 1")->Back<Scope>().Find("Name")->Back<std::string>().c_str());
			Assert::AreEqual("child", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 1")->Back<Scope>().Find("Tag")->Back<std::string>().c_str());
			
			
			Assert::AreEqual("Avatar Child One", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2")->Back<Scope>().Find("Name")->Back<std::string>().c_str());
			Assert::AreEqual("child", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2")->Back<Scope>().Find("Tag")->Back<std::string>().c_str());

		}



		TEST_METHOD(Clone)
		{
			GameObject object1;

			GameObject* object2 = object1.Clone();

			Assert::IsNotNull(object2);
			Assert::AreEqual("GameObject", object2->GetObjectName().c_str());
			Assert::AreEqual(glm::vec4(0.0), object2->GetPosition());
			Assert::AreEqual(glm::vec4(0.0), object2->GetRotation());
			Assert::AreEqual(glm::vec4(0.0), object2->GetScale());
			Assert::IsNull(object2->GetParent());

			delete object2;

			Avatar avatar1;
			
			Avatar* avatar2 = avatar1.Clone();
			
			Assert::IsNotNull(avatar2);
			Assert::AreEqual("GameObject", avatar2->GetObjectName().c_str());
			Assert::AreEqual(glm::vec4(0.0), avatar2->GetPosition());
			Assert::AreEqual(glm::vec4(0.0), avatar2->GetRotation());
			Assert::AreEqual(glm::vec4(0.0), avatar2->GetScale());
			Assert::IsNull(avatar2->GetParent());
			Assert::AreEqual(int32_t(0), avatar2->GetHealth());
			delete avatar2;


		}

		TEST_METHOD(Equals)
		{
			GameObject object1;

			GameObject* object2 = object1.Clone();

			Assert::IsTrue(object1.Equals(&object1));
			Assert::IsTrue(object1.Equals(object2));

			delete object2;

			GameObject* object3 = nullptr;

			Assert::IsFalse(object1.Equals(object3));

			Avatar avatar1;

			Avatar* avatar2 = avatar1.Clone();

			Assert::IsTrue(avatar1.Equals(&avatar1));
			Assert::IsTrue(avatar1.Equals(avatar2));
			delete avatar2;

			Avatar* avatar3 = nullptr;

			Assert::IsFalse(avatar1.Equals(avatar3));

			Assert::IsFalse(object1.Equals(&avatar1));
		}

		TEST_METHOD(ToString)
		{
			GameObject object1;
			Avatar avatar1;

			std::string gOString = "GameObject!! :D";
			std::string AvString = "Avatar!! :D";

			Assert::AreEqual(object1.ToString(), gOString);
			Assert::AreEqual(avatar1.ToString(), AvString);
		}

		TEST_METHOD(Update)
		{

			AvatarFactory af;
			ScopeFactory s;
			GameObjectFactory gf;


			std::string input = R"(GameObjectTest2.json)";


			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.ParseFromFile(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			Assert::AreEqual(int32_t(0), dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2")->Back<Scope>().Find("Health")->Back<int32_t>());

			GameState gTime;
			dataWrapper._currentContext->As<GameObject>()->Update(gTime);


			Assert::AreEqual(int32_t(100), dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2")->Back<Scope>().Find("Health")->Back<int32_t>());
		}


		TEST_METHOD(GettersSetters)
		{
			GameObject object1;

			Assert::AreEqual(glm::vec4(0.0), object1.GetPosition());
			Assert::AreEqual(glm::vec4(0.0), object1.GetRotation());
			Assert::AreEqual(glm::vec4(0.0), object1.GetScale());
			Assert::AreEqual("null", object1.GetObjectTag().c_str());
			Assert::AreEqual("GameObject", object1.GetObjectName().c_str());


			object1.SetObjectName("Cooler GameObject");
			object1.SetObjectTag("Cool");
			object1.SetPosition(glm::vec4(1.0));
			object1.SetRotation(glm::vec4(1.0));
			object1.SetScale(glm::vec4(1.0));

			Assert::AreEqual(glm::vec4(1.0), object1.GetPosition());
			Assert::AreEqual(glm::vec4(1.0), object1.GetRotation());
			Assert::AreEqual(glm::vec4(1.0), object1.GetScale());
			Assert::AreEqual("Cool", object1.GetObjectTag().c_str());
			Assert::AreEqual("Cooler GameObject", object1.GetObjectName().c_str());
		}

		TEST_METHOD(RTTITest)
		{
			GameObject object1;

			RTTI* r1 = &object1;

			Assert::IsTrue(r1->Is(GameObject::TypeIdClass()));
			Assert::IsTrue(r1->Is(r1->TypeIdInstance()));
			Assert::IsFalse(r1->Is(Avatar::TypeIdClass()));

			Avatar* a1 = r1->As<Avatar>();
			Assert::IsNull(a1);

			GameObject* object2 = r1->As<GameObject>();
			Assert::IsNotNull(object2);


		}


	private:
		static _CrtMemState _startMemState;



	};

	_CrtMemState GameObjectTest::_startMemState;

}
