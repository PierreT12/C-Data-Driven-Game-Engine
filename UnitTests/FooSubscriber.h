#pragma once
#include "Event.h"
#include "EventQueue.h"
#include "Foo.h"
using namespace FieaGameEngine;


namespace FooSupport
{
	struct FooSubscriber final : public EventSubscriber
	{
	public:
		void Notify(const IEvent& publisher) override;
		int32_t _eventCall{ 0 };
	};


	struct FooEnqueueSubscriber final : public EventSubscriber
	{
	public:
		void Notify(const IEvent& publisher) override;
		int32_t _eventCall{ 0 };
	};


	struct FooDequeueSubscriber final : public EventSubscriber
	{
	public:
		FooDequeueSubscriber(std::shared_ptr<Event<Foo>>  deletePtr);
		void Notify(const IEvent& publisher) override;
		int32_t _eventCall{ 0 };
		std::shared_ptr<Event<Foo>>  _deletePtr;
	};

}

