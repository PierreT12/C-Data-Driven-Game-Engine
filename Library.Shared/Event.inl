#include "Event.h"
namespace FieaGameEngine
{
	template<typename _Type>
	RTTI_DEFINITIONS(Event<_Type>)

	template<typename _Type>
	Event<_Type>::Event(_Type& typeEvent, const std::chrono::milliseconds& delay ):
		IEvent{_subscribers, delay},
		_message{typeEvent} {}

	template<typename _Type>
	inline Event<_Type>::Event(_Type&& typeEvent, const std::chrono::milliseconds& delay):
		IEvent{ _subscribers, delay },
		_message{typeEvent}{}

	template<typename _Type>
	inline std::string Event<_Type>::ToString() const
	{
		return std::string("Templated Event!! :D");
	}

	template<typename _Type>
	inline bool Event<_Type>::Equals(const RTTI* rhs) const
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

		auto* object = rhs->As<Event<_Type>>();

		if (object == nullptr)
		{
			return equals;
		}

		if (_message == object->_message
			&& IEvent::Equals(object))
		{

			equals = true;
		}

		return equals;
	}

	template<typename _Type>
	inline void Event<_Type>::Subscribe(EventSubscriber* sub)
	{
		if (sub != nullptr)
		{
			if (_subscribers.Find(sub) == _subscribers.end())
			{
				_subscribers.PushBack(sub);
			}
		}
	}

	template<typename _Type>
	inline void Event<_Type>::Unsubscribe(EventSubscriber* sub)
	{
		if (sub != nullptr)
		{
			_subscribers.Remove(sub);	
		}

	}

	template<typename _Type>
	inline void Event<_Type>::UnsubscribeAll()
	{
		_subscribers.ClearList();

	}

	template<typename _Type>
	inline const _Type& Event<_Type>::Message() const
	{
		return _message;
	}


	template<typename _Type>
	inline size_t Event<_Type>::Size()
	{
		return _subscribers.Size();
	}
	
}