#include "pch.h"
#include "FooSubscriber.h"

namespace FooSupport
{
	void FooSubscriber::Notify(const IEvent& publisher)
	{
		const auto* eFoo = publisher.As<Event<Foo>>();

		if (eFoo != nullptr)
		{
			++_eventCall;
		}
	}

	void FooEnqueueSubscriber::Notify(const IEvent& publisher)
	{
		const auto* eFoo = publisher.As<Event<Foo>>();

		if (eFoo != nullptr)
		{
			const Foo& temp = eFoo->Message();
			Event<const Foo>foo(temp);

			const auto sharedEvent = std::make_shared<Event<const Foo>>(foo);
			GameState::GetEventEditQueue().PushBack(std::make_tuple<std::shared_ptr<IEvent>, bool>(sharedEvent, true));
			++_eventCall;
		}
		

	}

	FooDequeueSubscriber::FooDequeueSubscriber(std::shared_ptr<Event<Foo>> deletePtr):
		_deletePtr{deletePtr}
	{}

	void FooDequeueSubscriber::Notify(const IEvent& publisher)
	{
		const auto* eFoo = publisher.As<Event<Foo>>();
		if (eFoo != nullptr)
		{
			GameState::GetEventEditQueue().PushBack(std::make_tuple<std::shared_ptr<IEvent>, bool>(_deletePtr, false));
			++_eventCall;
		}

	}

}

