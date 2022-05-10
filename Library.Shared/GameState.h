#pragma once
#include "GameClock.h"
#include "GameTime.h"
#include "IEvent.h"
#include <memory>
namespace FieaGameEngine
{
	/// <summary>
	/// Forward Declaration of Action
	/// </summary>
	class Action;

	/// <summary>
	/// A GameState Class
	/// </summary>
	class GameState final 
	{
		
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		GameState() = default;

		/// <summary>
		/// Default Destructor
		/// </summary>
		~GameState() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The GameState that will be copied</param>
		GameState(const GameState& other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The GameState that will be moved</param>
		GameState(GameState&& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The GameState that will be copied from</param>
		/// <returns> This GameState, where the data was copied to</returns>
		GameState& operator=(const GameState& other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The GameState that will be moved</param>
		/// <returns> A refernce the this GameState, that has had data moved into it</returns>
		GameState& operator=(GameState&& other) = default;

		/// <summary>
		/// Static Get Create Queue
		/// </summary>
		/// <returns> A ref to the Create Queue Vector</returns>
		static Vector<Action*>& GetCreateQueue();

		/// <summary>
		/// Static Get Destroy Queue
		/// </summary>
		/// <returns> A ref to the Destroy Queue Vector</returns>
		static Vector<Action*>& GetDestroyQueue();



		static Vector<std::tuple<std::shared_ptr<IEvent>, bool>>& GetEventEditQueue();

		/// <summary>
		/// Static Get GameTime
		/// </summary>
		/// <returns> A ref to the GameTime</returns>
		static GameTime& GetGameTime();




	private:
		static inline Vector<Action*> _createQueue;
		static inline Vector<Action*> _deleteQueue;
		
		static inline Vector<std::tuple<std::shared_ptr<IEvent>, bool>> _eventeditQueue;

		static inline GameTime _time;

		

	};
}


