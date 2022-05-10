#pragma once
#include "RTTI.h"
namespace FieaGameEngine
{
	/// <summary>
	/// Forward Declaration of IEvent
	/// </summary>
	class IEvent;

	/// <summary>
	/// An Event Subscriber class that inherits from RTTI
	/// </summary>
	class EventSubscriber : public RTTI
	{
		RTTI_DECLARATIONS(EventSubscriber, RTTI)

	public: 
		/// <summary>
		/// Default Constructor
		/// </summary>
		EventSubscriber() = default;

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		virtual ~EventSubscriber() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The EventSubscriber that will be copied</param>
		EventSubscriber(const EventSubscriber & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The EventSubscriber that will be copied from</param>
		/// <returns> This EventSubscriber, where the data was copied to</returns>
		EventSubscriber& operator=(const EventSubscriber & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The EventSubscriber that will be moved</param>
		EventSubscriber(EventSubscriber && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The EventSubscriber that will be moved</param>
		/// <returns> A refernce the this EventSubscriber, that has had data moved into it</returns>
		EventSubscriber& operator=(EventSubscriber && other) = default;

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
		/// Notifies the subscriber that an event occured
		/// </summary>
		/// <param name="publisher"> The Event that has triggered as a const ref</param>
		virtual void Notify(const IEvent& publisher) = 0;
	};
}


