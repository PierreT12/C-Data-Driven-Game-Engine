#include "pch.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventSubscriber)


	std::string EventSubscriber::ToString() const
	{
		return std::string("EventSubscriber!! :D");
	}
	bool EventSubscriber::Equals(const RTTI* rhs) const
	{
		bool equals = false;

		if (rhs == nullptr)
		{
			return equals;
		}


		if (this == rhs)
		{
			equals = true;
		}

		auto* object = rhs->As<EventSubscriber>();

		if (object == nullptr)
		{
			return equals;
		}

		equals = true;

		return equals;
	}
}