#include "pch.h"
#include "FooSubscriber.h"
#include "JsonTableParseHelper.h"
#include "JsonParseHelperInt.h"
#include "Avatar.h"
#include "ActionBlockSwitch.h"
#include "ActionCreate.h"
#include "ActionDestroy.h"
#include "ActionIncrement.h"
#include "EventQueue.h"
#include "Event.h"
#include "ToStringSpecialization.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(EventTest)
	{
	public:

		GameState g;
		

		TEST_METHOD_INITIALIZE(Initalize)
		{
		

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{

			Event<Foo>::UnsubscribeAll();
			GameState::GetEventEditQueue().ClearList();

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
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);

			auto temp = std::make_shared<Event<Foo>>(foo);
			FooSubscriber sub;

			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			queue.Enqueue(temp, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));
			
			Assert::AreEqual(size_t(1), queue.Size());
			
			Event<Foo>::Subscribe(&sub);
			
			Assert::AreEqual(size_t(1), Event<Foo>::Size());

			foo.UnsubscribeAll();


		}

		TEST_METHOD(EnDeQueue)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;
			FooSubscriber sub2;
			std::shared_ptr temp = std::make_shared<Event<Foo>>(foo);

			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());

			queue.Enqueue(temp, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));

			queue.Enqueue(temp, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));

			Assert::AreEqual(size_t(1), queue.Size());

			queue.Dequeue(temp);

			Assert::AreEqual(size_t(0), queue.Size());
		}



		TEST_METHOD(SubUnSub)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;
			FooSubscriber sub2;
			
			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			queue.Enqueue(std::make_shared<IEvent>(foo), GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));
			
			Assert::AreEqual(size_t(1), queue.Size());
			
			Event<Foo>::Subscribe(&sub);
			
			Assert::AreEqual(size_t(1), Event<Foo>::Size());
			
			Event<Foo>::Subscribe(&sub);
			
			Assert::AreEqual(size_t(1), Event<Foo>::Size());
			
			Event<Foo>::Unsubscribe(&sub);
			
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			Event<Foo>::Subscribe(&sub);
			Event<Foo>::Subscribe(&sub2);
			
			Assert::AreEqual(size_t(2), Event<Foo>::Size());
			
			Event<Foo>::Subscribe(nullptr);
			
			Assert::AreEqual(size_t(2), Event<Foo>::Size());
			
			Event<Foo>::UnsubscribeAll();
			
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
		}

		TEST_METHOD(Deliver)
		{
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;
			FooSubscriber sub2;
			
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			Event<Foo>::Subscribe(&sub);
			Event<Foo>::Subscribe(&sub2);
			
			Assert::AreEqual(size_t(2), Event<Foo>::Size());
			
			Assert::AreEqual(int32_t(0), sub._eventCall);
			Assert::AreEqual(int32_t(0), sub2._eventCall);
			
			foo.Deliver();
			
			Assert::AreEqual(int32_t(1), sub._eventCall);
			Assert::AreEqual(int32_t(1), sub2._eventCall);


			foo.UnsubscribeAll();
		}

		TEST_METHOD(Send)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;
			FooSubscriber sub2;
			
			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			queue.Enqueue(std::make_shared<IEvent>(foo), GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));
			Event<Foo>::Subscribe(&sub);
			Event<Foo>::Subscribe(&sub2);
			
			Assert::AreEqual(size_t(2), Event<Foo>::Size());

			Assert::AreEqual(int32_t(0), sub._eventCall);
			Assert::AreEqual(int32_t(0), sub2._eventCall);
			
			queue.Send(std::make_shared<Event<Foo>>(foo));
			
			Assert::AreEqual(int32_t(1), sub._eventCall);
			Assert::AreEqual(int32_t(1), sub2._eventCall);

			foo.UnsubscribeAll();
		}

		TEST_METHOD(ClearQueue)
		{
			EventQueue queue;
			EventQueue queue2;
			Foo f;
			Event<Foo>foo(f);
			Event<Foo>foo2(f);
			Event<Foo>foo3(f);


			FooSubscriber sub;
			FooSubscriber sub2;
			
			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			queue.Enqueue(std::make_shared<IEvent>(foo), GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));

			Assert::AreEqual(size_t(1), queue.Size());

			queue.Enqueue(std::make_shared<IEvent>(foo2), GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(500));

			Assert::AreEqual(size_t(2), queue.Size());


			queue.Enqueue(std::make_shared<IEvent>(foo3), GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(1000));

			Assert::AreEqual(size_t(3), queue.Size());

			queue.Clear(g);

			Assert::AreEqual(size_t(0), queue.Size());


			queue2.Enqueue(std::make_shared<IEvent>(foo), GameState::GetGameTime().CurrentTime());
			queue2.Clear(g);
			Assert::AreEqual(size_t(0), queue2.Size());

		}

		TEST_METHOD(Notify)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;
			FooEnqueueSubscriber eSub;
			auto sharedptr = std::make_shared<Event<Foo>>(foo);

			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());

			queue.Enqueue(sharedptr, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));

			Assert::AreEqual(size_t(1), queue.Size());

			Assert::AreEqual(size_t(1), queue.Size());

			Event<Foo>::Subscribe(&sub);

			Assert::AreEqual(size_t(1), Event<Foo>::Size());

			Event<Foo>::Subscribe(&eSub);

			Assert::AreEqual(size_t(2), Event<Foo>::Size());

			sub.Notify(foo);
			eSub.Notify(foo);

			Assert::AreEqual(int32_t(1), sub._eventCall);
			Assert::AreEqual(int32_t(1), eSub._eventCall);

			Assert::AreEqual(size_t(1), queue.Size());

			queue.EditQueue();

			Event<Foo>::Unsubscribe(&eSub);
			Assert::AreEqual(size_t(2), queue.Size());
		}

		TEST_METHOD(Equals)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;

			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());

			queue.Enqueue(std::make_shared<IEvent>(foo), GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));

			Event<Foo> foo2 = foo;

			Assert::IsTrue(foo.Equals(&foo));
			Assert::IsTrue(foo.Equals(&foo2));


			Event<Foo>* foo3 = nullptr;

			Assert::IsFalse(foo.Equals(foo3));


			FooSubscriber sub2 = sub;

			Assert::IsTrue(sub.Equals(&sub));
			Assert::IsTrue(sub.Equals(&sub2));

			FooSubscriber* sub3 = nullptr;

			Assert::IsFalse(sub.Equals(sub3));

			Assert::IsFalse(foo2.Equals(&sub2));
			Assert::IsFalse(sub2.Equals(&foo2));

			Assert::IsFalse(foo2.IEvent::Equals(&sub2));
			Assert::IsFalse(foo2.IEvent::Equals(foo3));


		}

		TEST_METHOD(ToString)
		{
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;


			Assert::AreEqual("0", f.ToString().c_str());
			Assert::AreEqual("Templated Event!! :D", foo.ToString().c_str());
			Assert::AreEqual("EventSubscriber!! :D", sub.ToString().c_str());
			Assert::AreEqual("IEvent!! :D", foo.IEvent::ToString().c_str());
		}

		TEST_METHOD(Update)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			FooSubscriber sub;
			FooEnqueueSubscriber eSub;
			auto sharedptr = std::make_shared<Event<Foo>>(foo);
			
			FooDequeueSubscriber dSub(sharedptr);
			auto currentTime = GameState::GetGameTime().CurrentTime() + std::chrono::milliseconds(100);
			
			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			
			queue.Enqueue(sharedptr, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));
			
			Assert::AreEqual(size_t(1), queue.Size());
			
			Event<Foo>::Subscribe(&sub);
			
			Assert::AreEqual(size_t(1), Event<Foo>::Size());
			
			Event<Foo>::Subscribe(&eSub);
			
			Assert::AreEqual(size_t(2), Event<Foo>::Size());


			Assert::AreEqual(int32_t(0), sub._eventCall);
			queue.Update(g);
			Assert::AreEqual(int32_t(0), sub._eventCall);

			g.GetGameTime().SetCurrentTime(currentTime);
			queue.Update(g);
			Assert::AreEqual(int32_t(1), eSub._eventCall);
			Assert::AreEqual(size_t(2), GameState::GetEventEditQueue().Size());
			Event<Foo>::Unsubscribe(&eSub);

			queue.Update(g);
			queue.Enqueue(sharedptr, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));
			Assert::AreEqual(size_t(2), queue.Size());
			Assert::AreEqual(size_t(1), GameState::GetEventEditQueue().Size());
			
			
			
			Event<Foo>::Subscribe(&dSub);
			Assert::AreEqual(size_t(2), Event<Foo>::Size());
			
			queue.Update(g);
			Event<Foo>::Unsubscribe(&dSub);
			queue.Update(g);
			
			Assert::AreEqual(size_t(1), queue.Size());
			Assert::AreEqual(size_t(0), GameState::GetEventEditQueue().Size());
			
		}


		TEST_METHOD(GettersSetters)
		{
			EventQueue queue;
			Foo f;
			Event<Foo>foo(f);
			Event<Foo>foo2(std::move(f));
			foo2;
			FooSubscriber sub;
			FooEnqueueSubscriber eSub;
			auto sharedptr = std::make_shared<Event<Foo>>(foo);

			Assert::AreEqual(size_t(0), queue.Size());
			Assert::AreEqual(size_t(0), Event<Foo>::Size());
			auto time = GameState::GetGameTime().CurrentTime() + std::chrono::milliseconds(100);
			Assert::IsTrue(queue.IsEmpty());
			queue.Enqueue(sharedptr, GameState::GetGameTime().CurrentTime());
			Assert::IsFalse(queue.IsEmpty());
			Assert::IsTrue(std::chrono::milliseconds(0) == queue.Delay(sharedptr));

			queue.SetTime(sharedptr, GameState::GetGameTime().CurrentTime(), std::chrono::milliseconds(100));

			Assert::IsTrue(time == queue.TimeExpired(sharedptr));



			
		}

		TEST_METHOD(RTTITest)
		{
			Foo f;
			Event<Foo> object1(f);
			FooSubscriber sub;

			RTTI* r1 = &object1;

			Assert::IsTrue(r1->Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(r1->Is(IEvent::TypeIdClass()));
			Assert::IsTrue(r1->Is(r1->TypeIdInstance()));
			Assert::IsFalse(r1->Is(EventSubscriber::TypeIdClass()));


			RTTI* r2 = &sub;

			Assert::IsTrue(r2->Is(EventSubscriber::TypeIdClass()));
			Assert::IsTrue(r2->Is(r2->TypeIdInstance()));
			Assert::IsFalse(r2->Is(IEvent::TypeIdClass()));


			EventSubscriber* a1 = r1->As<EventSubscriber>();
			Assert::IsNull(a1);

			Event<Foo>* object2 = r1->As<Event<Foo>>();
			Assert::IsNotNull(object2);

		}


	private:
		static _CrtMemState _startMemState;



	};

	_CrtMemState EventTest::_startMemState;

}
