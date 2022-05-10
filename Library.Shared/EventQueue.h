#pragma once
#include "GameState.h"
#include <algorithm>
namespace FieaGameEngine
{
	/// <summary>
	/// An Event Queue Class
	/// </summary>
	class EventQueue final
	{
	public:

		// <summary>
		/// Default Constructor
		/// </summary>
		EventQueue() = default;

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		~EventQueue() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The EventQueue that will be copied</param>
		EventQueue(const EventQueue & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The EventQueue that will be copied from</param>
		/// <returns> This EventQueue, where the data was copied to</returns>
		EventQueue& operator=(const EventQueue & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The EventQueue that will be moved</param>
		EventQueue(EventQueue && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The EventQueue that will be moved</param>
		/// <returns> A refernce the this EventQueue, that has had data moved into it</returns>
		EventQueue& operator=(EventQueue && other) = default;

		/// <summary>
		/// Enqueues an event if it not already on the queue list
		/// </summary>
		/// <param name="publisher"> The Event shared Pointer which is going to be queued </param>
		/// <param name="currentTime"> The time that the object is being enqueued at </param>
		/// <param name="delayTime"> How long before the event expires</param>
		void Enqueue(std::shared_ptr<IEvent> publisher, const std::chrono::high_resolution_clock::time_point& currentTime, const std::chrono::milliseconds& delayTime = std::chrono::milliseconds::zero());

		/// <summary>
		/// Removes the Event from the Queue
		/// </summary>
		/// <param name="publisher"> The Event that will be removed from the queue</param>
		void Dequeue(std::shared_ptr<IEvent> publisher);

		/// <summary>
		/// Starts Sending Deliveries to all Subscribers of this Event
		/// </summary>
		/// <param name="publisher"> The event that will be sending out the deliveries</param>
		void Send(const std::shared_ptr<IEvent>& publisher);

		/// <summary>
		/// Updates to see if any Events have expired
		/// </summary>
		/// <param name="gameState"> A const ref to a GameState, which holds the GameTime</param>
		void Update(const GameState& gameState);

		/// <summary>
		/// Clears the Queue, but Sends on any Events that are expired at the time of the Clear
		/// </summary>
		/// <param name="gameState"> A const ref to a GameState, which holds the GameTime </param>
		void Clear(const GameState& gameState);

		/// <summary>
		/// Returns the Size of the Queue
		/// </summary>
		/// <returns> A size_t of the Size of the Queue</returns>
		size_t Size() const;

		/// <summary>
		/// Returns if the Queue is empty or not
		/// </summary>
		/// <returns>True/False depending on if the queue is empty</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Sets the new Expire Time of an Event
		/// </summary>
		/// <param name="publisher"> The event that will have its expired time changed</param>
		/// <param name="currentTime"> The current GameTime</param>
		/// <param name="delayTime"> The new time the expiring will be delayed by</param>
		void SetTime(const std::shared_ptr<IEvent>& publisher, const std::chrono::high_resolution_clock::time_point& currentTime, const std::chrono::milliseconds& delayTime = std::chrono::milliseconds::zero());

		/// <summary>
		/// Returns when the given event will expire
		/// </summary>
		/// <param name="publisher"> The event that the time expire will be taken from</param>
		/// <returns> A const ref to the expire time</returns>
		const std::chrono::high_resolution_clock::time_point& TimeExpired(const std::shared_ptr<IEvent>& publisher) const;

		/// <summary>
		/// Returns the set dealy for an event
		/// </summary>
		/// <param name="publisher"> The event that the delay will be taken from</param>
		/// <returns>A const ref to the delya time</returns>
		const std::chrono::milliseconds& Delay(const std::shared_ptr<IEvent>& publisher) const;

		/// <summary>
		/// Edits the Queue based on the PendingQueue
		/// </summary>
		void EditQueue();
		
		
	private:
		Vector<std::shared_ptr<IEvent>> _queue;

		

	};
}


