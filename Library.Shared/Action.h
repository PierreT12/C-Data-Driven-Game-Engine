#pragma once
#include "GameState.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An Action Class, inherits from Attributed
	/// </summary>
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		Action();

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		virtual ~Action() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The Action that will be copied</param>
		Action(const Action & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The Action that will be copied from</param>
		/// <returns> This Action, where the data was copied to</returns>
		Action& operator=(const Action & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The Action that will be moved</param>
		Action(Action && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The Action that will be moved</param>
		/// <returns> A refernce the this Action, that has had data moved into it</returns>
		Action& operator=(Action && other) = default;

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
		/// Virtual Update Method, updates all children as well
		/// </summary>
		/// <param name="gameTime"> The new gametime signaling that the game is moving the the next frame</param>
		virtual void Update(const GameState& gamestate) = 0;


		/// <summary>
		/// Get the Object Name
		/// </summary>
		/// <returns> The Object Name as a const string ref</returns>
		const std::string& GetObjectName() const;


		/// <summary>
		/// Sets the Object's Name
		/// </summary>
		/// <param name="name"> A const string ref to the name that the object will be set to. This data will be moved, so do not use it after this</param>
		void SetObjectName(const std::string& name);


	protected:
		std::string _name{"Default Action Name"};

		/// <summary>
		/// Protected Constructor
		/// </summary>
		/// <param name="typeID"> Takes in an RTTI Type ID</param>
		Action(IdType typeID);
		
	};
}


