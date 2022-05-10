#include "pch.h"
#include "GameState.h"
namespace FieaGameEngine
{
	Vector<Action*>& GameState::GetCreateQueue()
	{
		return _createQueue;
	}
	Vector<Action*>& GameState::GetDestroyQueue()
	{
		return _deleteQueue;
	}
	Vector<std::tuple<std::shared_ptr<IEvent>, bool>>& GameState::GetEventEditQueue()
	{
		return _eventeditQueue;
	}
	GameTime& GameState::GetGameTime()
	{
		return _time;
	}
}