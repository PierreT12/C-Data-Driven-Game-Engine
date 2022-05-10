#pragma once
#include "EventSubscriber.h"
#include "Attributed.h"
#include <chrono>
namespace FieaGameEngine
{
	/// <summary>
	/// A IEvent Class that inherits from RTTI
	/// </summary>
	class IEvent : public RTTI
	{
		RTTI_DECLARATIONS(IEvent, RTTI)

	public:
		
		/// <summary>
		/// Friend class EventQueue
		/// </summary>
		friend class EventQueue;

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		virtual ~IEvent() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The IEvent that will be copied</param>
		IEvent(const IEvent & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The IEvent that will be copied from</param>
		/// <returns> This IEvent, where the data was copied to</returns>
		IEvent& operator=(const IEvent & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The IEvent that will be moved</param>
		IEvent(IEvent && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The IEvent that will be moved</param>
		/// <returns> A refernce the this IEvent, that has had data moved into it</returns>
		IEvent& operator=(IEvent && other) = default;

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
		/// Returns a bool if this event is expired or not from the time it was Enqueued
		/// </summary>
		/// <param name="currentTime"> The Current GameTime </param>
		/// <returns> True/False depeneding if the event is expired</returns>
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const;

		/// <summary>
		/// Delivers Notifies to Each of the subscribers
		/// </summary>
		void Deliver();

	protected:

		/// <summary>
		/// Protected Constructor for IEvent
		/// </summary>
		/// <param name="subscribers"> A non const ref to the subscribers list</param>
		/// <param name="delay"> How long the event will be delayed from expiring from the time it was enqueued</param>
		IEvent(Vector<EventSubscriber*>& subscribers, const std::chrono::milliseconds& delay = std::chrono::milliseconds::zero());

	private:
		std::chrono::high_resolution_clock::time_point _expireTime;

		std::chrono::milliseconds _delay;

		Vector<EventSubscriber*>* _eventSubs{ nullptr };
	};
}


