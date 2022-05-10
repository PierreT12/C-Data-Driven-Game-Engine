#include "pch.h"
#include "Foo.h"
#include "JsonTableParseHelper.h"
#include "JsonParseHelperInt.h"
#include "Avatar.h"
#include "ActionBlockSwitch.h"
#include "ActionCreate.h"
#include "ActionDestroy.h"
#include "ActionIncrement.h"
#include "ToStringSpecialization.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(ActionTest)
	{
	public:

		ScopeFactory s;
		GameObjectFactory gf;
		AvatarFactory af;
		ActionIncrementFactory aif;
		ActionCreateFactory acf;
		ActionDestroyFactory adf;
		ActionBlockSwitchFactory asf;
		ActionBlockFactory abf;

		TEST_METHOD_INITIALIZE(Initalize)
		{
			TypeRegistry* registry = TypeRegistry::GetInstance();
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(GameObject::TypeIdClass(), GameObject::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(Avatar::TypeIdClass(), Avatar::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(ActionIncrement::TypeIdClass(), ActionIncrement::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(ActionCreate::TypeIdClass(), ActionCreate::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(ActionDestroy::TypeIdClass(), ActionDestroy::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(ActionBlockSwitch::TypeIdClass(), ActionBlockSwitch::GetSignature()));
			registry->AddEntry(std::make_pair<size_t, const Vector<Signature>>(ActionBlock::TypeIdClass(), ActionBlock::GetSignature()));


#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
			GameState::GetCreateQueue().ClearList();
			GameState::GetDestroyQueue().ClearList();

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
			ActionBlock ab;
			ActionBlockSwitch abs;
			ActionCreate ac;
			ActionDestroy ad;
			ActionIncrement ai;

			Assert::AreEqual(size_t(3), ab.Size());
			Assert::AreEqual(size_t(4), abs.Size());
			Assert::AreEqual(size_t(3), ac.Size());
			Assert::AreEqual(size_t(3), ad.Size());
			Assert::AreEqual(size_t(4), ai.Size());

		}

		TEST_METHOD(Parse)
		{
			std::string input = R"(GameObjectTest.json)";


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
			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("A"));
			Assert::AreEqual("Root Game Object", dataWrapper._currentContext->Find("Name")->Back<std::string>().c_str());
			Assert::AreEqual(glm::vec4(1), dataWrapper._currentContext->Find("Position")->Back<glm::vec4>());
			Assert::AreEqual(glm::vec4(1), dataWrapper._currentContext->Find("Rotation")->Back<glm::vec4>());
			Assert::AreEqual(glm::vec4(1), dataWrapper._currentContext->Find("Scale")->Back<glm::vec4>());
			Assert::AreEqual("root", dataWrapper._currentContext->Find("Tag")->Back<std::string>().c_str());
			Assert::AreEqual(10.f, dataWrapper._currentContext->Find("A")->Back<float>());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 1"));
			Assert::IsNotNull(dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2"));

			Assert::AreEqual("GameObject Child One", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 1")->Back<Scope>().Find("Name")->Back<std::string>().c_str());
			Assert::AreEqual("child", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 1")->Back<Scope>().Find("Tag")->Back<std::string>().c_str());

			Assert::AreEqual("GameObject Child Two", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2")->Back<Scope>().Find("Name")->Back<std::string>().c_str());
			Assert::AreEqual("child", dataWrapper._currentContext->Find("Children")->Front<Scope>().Find("Child 2")->Back<Scope>().Find("Tag")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5"));

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5")->Front<Scope>().Find("Name"));
			Assert::AreEqual("Add 1.5", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5")->Front<Scope>().Find("Name")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5")->Front<Scope>().Find("Target"));
			Assert::AreEqual("A", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5")->Front<Scope>().Find("Target")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5")->Front<Scope>().Find("Step"));
			Assert::AreEqual(1.5f, dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Add 1.5")->Front<Scope>().Find("Step")->Back<float>());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Destroy Add 1.5"));

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Destroy Add 1.5")->Front<Scope>().Find("Name"));
			Assert::AreEqual("Destory Add 1.5", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Destroy Add 1.5")->Front<Scope>().Find("Name")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Destroy Add 1.5")->Front<Scope>().Find("Action To Destory"));
			Assert::AreEqual("Add 1.5", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("Destroy Add 1.5")->Front<Scope>().Find("Action To Destory")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase"));

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Name"));
			Assert::AreEqual("Add 2.5", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Name")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Switch"));
			Assert::AreEqual("Case 1", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Switch")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case"));

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 0"));

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 0")->Front<Scope>().Find("Name"));
			Assert::AreEqual("Create Add 1.5", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 0")->Front<Scope>().Find("Name")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 0")->Front<Scope>().Find("Class Name"));
			Assert::AreEqual("ActionIncrement", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 0")->Front<Scope>().Find("Class Name")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1"));
			
			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1")->Front<Scope>().Find("Name"));
			Assert::AreEqual("Default Action Name", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1")->Front<Scope>().Find("Name")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1")->Front<Scope>().Find("Actions")->Get<Scope>().Find("Add 3")->Get<Scope>().Find("Target"));
			Assert::AreEqual("A", dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1")->Front<Scope>().Find("Actions")->Get<Scope>().Find("Add 3")->Get<Scope>().Find("Target")->Back<std::string>().c_str());

			Assert::IsNotNull(dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1")->Front<Scope>().Find("Actions")->Get<Scope>().Find("Add 3")->Get<Scope>().Find("Step"));
			Assert::AreEqual(3.f, dataWrapper._currentContext->Find("Actions")->Front<Scope>().Find("SwitchCase")->Front<Scope>().Find("Case")->Front<Scope>().Find("Case 1")->Front<Scope>().Find("Actions")->Get<Scope>().Find("Add 3")->Get<Scope>().Find("Step")->Back<float>());

		}



		TEST_METHOD(Clone)
		{
			ActionBlock ab;
			ActionBlockSwitch abs;
			ActionCreate ac;
			ActionDestroy ad;
			ActionIncrement ai;


			ActionBlock* ab2 = ab.Clone();
			ActionBlockSwitch* abs2 = abs.Clone();
			ActionCreate* ac2 = ac.Clone();
			ActionDestroy* ad2 = ad.Clone();
			ActionIncrement* ai2 = ai.Clone();

			Assert::IsNotNull(ab2);
			Assert::IsNotNull(abs2);
			Assert::IsNotNull(ac2);
			Assert::IsNotNull(ad2);
			Assert::IsNotNull(ai2);


			Assert::IsNull(ab2->GetParent());
			Assert::IsNull(abs2->GetParent());
			Assert::IsNull(ac2->GetParent());
			Assert::IsNull(ad2->GetParent());
			Assert::IsNull(ai2->GetParent());


			delete ab2;
			delete abs2;
			delete ac2;
			delete ad2;
			delete ai2;

		}

		TEST_METHOD(Equals)
		{
			ActionBlock ab;
			ActionBlockSwitch abs;
			ActionCreate ac;
			ActionDestroy ad;
			ActionIncrement ai;


			ActionBlock* ab2 = ab.Clone();
			ActionBlockSwitch* abs2 = abs.Clone();
			ActionCreate* ac2 = ac.Clone();
			ActionDestroy* ad2 = ad.Clone();
			ActionIncrement* ai2 = ai.Clone();

			Assert::IsTrue(ab.Equals(&ab));
			Assert::IsTrue(abs.Equals(&abs));
			Assert::IsTrue(ac.Equals(&ac));
			Assert::IsTrue(ad.Equals(&ad));
			Assert::IsTrue(ai.Equals(&ai));

			Assert::IsTrue(ab.Equals(ab2));
			Assert::IsTrue(abs.Equals(abs2));
			Assert::IsTrue(ac.Equals(ac2));
			Assert::IsTrue(ad.Equals(ad2));
			Assert::IsTrue(ai.Equals(ai2));

			Assert::IsFalse(ai.Equals(ab2));
			Assert::IsFalse(ad.Equals(abs2));
			Assert::IsFalse(abs.Equals(ac2));
			Assert::IsFalse(ab.Equals(ad2));
			Assert::IsFalse(ac.Equals(ai2));


			delete ab2;
			delete abs2;
			delete ac2;
			delete ad2;
			delete ai2;


			Assert::IsFalse(ab.Equals(nullptr));
			Assert::IsFalse(abs.Equals(nullptr));
			Assert::IsFalse(ac.Equals(nullptr));
			Assert::IsFalse(ad.Equals(nullptr));
			Assert::IsFalse(ai.Equals(nullptr));

		}

		TEST_METHOD(ToString)
		{
			ActionBlock ab;
			ActionBlockSwitch abs;
			ActionCreate ac;
			ActionDestroy ad;
			ActionIncrement ai;

			std::string abString = "ActionBlock!! :D";
			std::string absString = "ActionBlockSwitch!! :D";
			std::string acString = "ActionCreate!! :D";
			std::string adString = "ActionDestroy!! :D";
			std::string aiString = "ActionIncrement!! :D";

			Assert::AreEqual(ab.ToString(), abString);
			Assert::AreEqual(abs.ToString(), absString);
			Assert::AreEqual(ac.ToString(), acString);
			Assert::AreEqual(ad.ToString(), adString);
			Assert::AreEqual(ai.ToString(), aiString);









		}

		TEST_METHOD(Update)
		{
			GameState gTime;
			std::string input = R"(GameObjectTest.json)";


			JsonTableParseHelper tableHelper;
			JsonTableParseHelper::DataWrapper dataWrapper;

			JsonParseMaster parseMaster(dataWrapper);
			Assert::IsFalse(tableHelper.isInitalized);
			parseMaster.AddHelper(tableHelper);
			Assert::IsTrue(tableHelper.isInitalized);

			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());
			parseMaster.ParseFromFile(input);
			Assert::AreEqual(size_t(0), dataWrapper.GetDepth());

			Assert::AreEqual(10.f, dataWrapper._currentContext->Find("A")->Back<float>());

			dataWrapper._currentContext->As<GameObject>()->Update(gTime);

			Assert::AreEqual(17.f, dataWrapper._currentContext->Find("A")->Back<float>());

			dataWrapper._currentContext->As<GameObject>()->Update(gTime);

			Assert::AreEqual(22.5f, dataWrapper._currentContext->Find("A")->Back<float>());

			ActionCreate ac;

			ac.Update(gTime);
		}


		TEST_METHOD(GettersSetters)
		{

			ActionBlock ab;
			ActionBlockSwitch abs;
			ActionCreate ac;
			ActionDestroy ad;
			ActionIncrement ai;

			ab.SetObjectName("ActionBlock");
			abs.SetSwitchValue("Case 1");
			ac.SetActionClass("ActionIncrement");
			ad.SetActionToDestroy("Case 1");
			ai.SetStep(6.5f);
			ai.SetTarget("A");

			Assert::AreEqual("ActionBlock", ab.GetObjectName().c_str());
			Assert::AreEqual("Case 1", abs.GetSwitchValue().c_str());
			Assert::AreEqual("ActionIncrement", ac.GetActionClass().c_str());
			Assert::AreEqual("Case 1", ad.GetActionToDestroy().c_str());
			Assert::AreEqual(6.5f, ai.GetStep());
			Assert::AreEqual("A", ai.GetTarget().c_str());

			
		}

		TEST_METHOD(RTTITest)
		{
			ActionBlock ab;
			ActionBlockSwitch abs;
			ActionCreate ac;
			ActionDestroy ad;
			ActionIncrement ai;

			RTTI* r1 = &ab;
			RTTI* r2 = &abs;
			RTTI* r3 = &ac;
			RTTI* r4 = &ad;
			RTTI* r5 = &ai;

			Assert::IsTrue(r1->Is(Action::TypeIdClass()));
			Assert::IsTrue(r1->Is(r1->TypeIdInstance()));
			Assert::IsFalse(r1->Is(ActionCreate::TypeIdClass()));
			
			Assert::IsTrue(r2->Is(Action::TypeIdClass()));
			Assert::IsTrue(r2->Is(r2->TypeIdInstance()));
			Assert::IsFalse(r2->Is(ActionCreate::TypeIdClass()));
			
			Assert::IsTrue(r3->Is(Action::TypeIdClass()));
			Assert::IsTrue(r3->Is(r3->TypeIdInstance()));
			Assert::IsFalse(r3->Is(ActionDestroy::TypeIdClass()));
			
			Assert::IsTrue(r4->Is(Action::TypeIdClass()));
			Assert::IsTrue(r4->Is(r4->TypeIdInstance()));
			Assert::IsFalse(r4->Is(ActionCreate::TypeIdClass()));
			
			Assert::IsTrue(r5->Is(Action::TypeIdClass()));
			Assert::IsTrue(r5->Is(r5->TypeIdInstance()));
			Assert::IsFalse(r5->Is(ActionCreate::TypeIdClass()));
			
			ActionCreate* a1 = r1->As<ActionCreate>();
			Assert::IsNull(a1);
			
			ActionBlock* rh1 = r1->As<ActionBlock>();
			Assert::IsNotNull(rh1);
			
			
			ActionCreate* a2 = r2->As<ActionCreate>();
			Assert::IsNull(a2);
			
			ActionBlock* rh2 = r2->As<ActionBlockSwitch>();
			Assert::IsNotNull(rh2);
			
			ActionDestroy* a3 = r3->As<ActionDestroy>();
			Assert::IsNull(a3);
			
			ActionCreate* rh3 = r3->As<ActionCreate>();
			Assert::IsNotNull(rh3);
			
			ActionCreate* a4 = r4->As<ActionCreate>();
			Assert::IsNull(a4);
			
			ActionDestroy* rh4 = r4->As<ActionDestroy>();
			Assert::IsNotNull(rh4);
			
			ActionCreate* a5 = r5->As<ActionCreate>();
			Assert::IsNull(a5);
			
			ActionIncrement* rh5 = r5->As<ActionIncrement>();
			Assert::IsNotNull(rh5);


		}


	private:
		static _CrtMemState _startMemState;



	};

	_CrtMemState ActionTest::_startMemState;

}
