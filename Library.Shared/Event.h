#pragma once
#include "IEvent.h"
namespace FieaGameEngine
{
	/// <summary>
	/// Templated Event Class
	/// </summary>
	template <typename _Type>
	class Event : public IEvent
	{

		RTTI_DECLARATIONS(Event, IEvent)
		
	public:
		
		/// <summary>
		/// LValue Constructor
		/// </summary>
		/// <param name="typeEvent"> The type of event this will be</param>
		/// <param name="delay"> How long the Event experation will be delayed</param>
		Event(_Type& typeEvent, const std::chrono::milliseconds& delay = std::chrono::milliseconds::zero());


		/// <summary>
		/// RValue Constructor
		/// </summary>
		/// <param name="typeEvent"> The type of event this will be</param>
		/// <param name="delay"> How long the Event experation will be delayed</param>
		Event(_Type&& typeEvent, const std::chrono::milliseconds& delay = std::chrono::milliseconds::zero());

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		virtual ~Event() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The Event that will be copied</param>
		Event(const Event & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The Event that will be copied from</param>
		/// <returns> This Event, where the data was copied to</returns>
		Event& operator=(const Event & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The Event that will be moved</param>
		Event(Event && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The Event that will be moved</param>
		/// <returns> A refernce the this Event, that has had data moved into it</returns>
		Event& operator=(Event && other) = default;

		/// <summary>
		/// Virtual Override of To String
		/// </summary>
		/// <returns>Returns a String that represents this class</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Virtual Equal Override
		/// </summary>
		/// <param name="rhs"> An pointer to an RTTI or RTTI inherited object</param>
		/// <returns> True/False, depending on if this and the passed in pointer are equal</returns>
		virtual bool Equals(const RTTI * rhs) const override;

		/// <summary>
		/// Subscribes to an Event. NOTE: Do not do this in the middle of an Update, Event _Type doesn't handle this, and behavior is unknown
		/// </summary>
		/// <param name="sub"> The subscriber pointer that will subscribe to this event</param>
		static inline void Subscribe(EventSubscriber* sub);

		/// <summary>
		///  Unsubscribes to an Event. NOTE: Do not do this in the middle of an Update, Event _Type doesn't handle this, and behavior is unknown
		/// </summary>
		/// <param name="sub">The subscriber pointer that will unsubscribe to this event </param>
		static inline void Unsubscribe(EventSubscriber* sub);

		/// <summary>
		/// Unsubscribes all the Subscribers from this list. NOTE: Do not do this in the middle of an Update, Event _Type doesn't handle this, and behavior is unknown
		/// </summary>
		static inline void UnsubscribeAll();

		/// <summary>
		/// Gets the message assoicated with this Event
		/// </summary>
		/// <returns> A refernce to this message</returns>
		const _Type& Message() const;

		/// <summary>
		/// Returns the Size of the Static Subscriber List
		/// </summary>
		/// <returns> The size of the subscriber list </returns>
		static inline size_t Size();


	private:

		_Type& _message;

		static inline Vector<EventSubscriber*> _subscribers;
	};

	

}
#include "Event.inl"

