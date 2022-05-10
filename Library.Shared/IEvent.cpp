#include "pch.h"
#include "IEvent.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(IEvent)

	IEvent::IEvent(Vector<EventSubscriber*>& subscribers, const std::chrono::milliseconds& delay) :
		_eventSubs{ &subscribers },
		_delay{ delay }{}

	std::string IEvent::ToString() const
	{
		return std::string("IEvent!! :D");
	}

	bool IEvent::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<IEvent>();

		if (object == nullptr)
		{
			return equals;
		}



		if (_delay == object->_delay
			&& _expireTime == object->_expireTime
			&& _eventSubs == object->_eventSubs)
		{

			equals = true;
		}

		return equals;
	}

	bool IEvent::IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const
	{
		if (currentTime >= _expireTime)
		{
			return true;
		}

		return false;
	}
	void IEvent::Deliver()
	{

		if (_eventSubs != nullptr)
		{
			for (auto& sub : *_eventSubs)
			{
				sub->Notify(*this);
			}
		}
	}
}