#include "pch.h"
#include "EventQueue.h"
namespace FieaGameEngine
{
	void EventQueue::Enqueue(std::shared_ptr<IEvent> publisher, const std::chrono::high_resolution_clock::time_point& currentTime, const std::chrono::milliseconds& delayTime)
	{
		if (_queue.Find(publisher) == _queue.end())
		{
			IEvent* pub = publisher.get();

			pub->_delay = delayTime;
			pub->_expireTime = currentTime + delayTime;
			_queue.PushBack(publisher);
		}
	}

	void EventQueue::Dequeue(std::shared_ptr<IEvent> publisher)
	{
		_queue.Remove(publisher);
	}

	void EventQueue::Send(const std::shared_ptr<IEvent>& publisher)
	{
		publisher->Deliver();
	}

	void EventQueue::Update(const GameState& gameState)
	{
		EditQueue();

		for (auto& events : _queue)
		{
			bool expired = events->IsExpired(gameState.GetGameTime().CurrentTime());
			if (expired)
			{
				Send(events);
				GameState::GetEventEditQueue().PushBack(std::tuple<std::shared_ptr<IEvent>, bool>(events, !expired));
			}
		}

	}

	void EventQueue::Clear(const GameState& gameState)
	{
		for (auto& publisher : _queue)
		{
			if (publisher->IsExpired(gameState.GetGameTime().CurrentTime()))
			{
				Send(publisher);
			}
		}

		_queue.ClearList();
	}

	size_t EventQueue::Size() const
	{
		return _queue.Size();
	}

	bool EventQueue::IsEmpty() const
	{
		return _queue.IsEmpty();
	}

	void EventQueue::SetTime(const std::shared_ptr<IEvent>& publisher, const std::chrono::high_resolution_clock::time_point& currentTime, const std::chrono::milliseconds& delayTime)
	{
		IEvent* pub = publisher.get();

		pub->_expireTime = (currentTime + delayTime);
		pub->_delay = delayTime;
	}

	const std::chrono::high_resolution_clock::time_point& EventQueue::TimeExpired(const std::shared_ptr<IEvent>& publisher) const
	{
		return publisher.get()->_expireTime;
	}

	const std::chrono::milliseconds& EventQueue::Delay(const std::shared_ptr<IEvent>& publisher) const
	{
		return publisher.get()->_delay;
	}

	void EventQueue::EditQueue()
	{
		auto& editQueue = GameState::GetEventEditQueue();
		for (auto& eve : editQueue)
		{
			auto [shared, create] = eve;

			if (create)
			{
				Enqueue(shared, GameState::GetGameTime().CurrentTime(), shared.get()->_delay);
			}
			else
			{
				Dequeue(shared);
			}
		}

		editQueue.ClearList();
	}


}


