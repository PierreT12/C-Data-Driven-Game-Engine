#pragma once
#include "Action.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An Action Destory Class, inherits from Action
	/// </summary>
	class ActionDestroy final : public Action
	{
		RTTI_DECLARATIONS(ActionDestroy, Action)

	public:

		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionDestroy();

		/// <summary>
		/// Virtual Default Destructor
		/// </summary>
		virtual ~ActionDestroy() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The ActionDestroy that will be copied</param>
		ActionDestroy(const ActionDestroy & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The ActionDestroy that will be copied from</param>
		/// <returns> This ActionDestroy, where the data was copied to</returns>
		ActionDestroy& operator=(const ActionDestroy & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The ActionDestroy that will be moved</param>
		ActionDestroy(ActionDestroy && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The ActionDestroy that will be moved</param>
		/// <returns> A refernce the this ActionDestroy, that has had data moved into it</returns>
		ActionDestroy& operator=(ActionDestroy && other) = default;

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
		void Update(const GameState& gamestate) override;

		/// <summary>
		/// Gets the Action To Destroy Member Variable
		/// </summary>
		/// <returns> A const ref to the Action to Destory Member Variable</returns>
		const std::string GetActionToDestroy() const;

		/// <summary>
		/// Sets the Action To Destroy Member Variable
		/// </summary>
		/// <param name="actionName">A const ref string that will be moved into the Destory Member Variable</param>
		void SetActionToDestroy(const std::string& actionName);


		/// <summary>
		/// Virtual Override of Clone
		/// </summary>
		/// <returns>Returns a copy of this GameObject</returns>
		virtual ActionDestroy* Clone() const override;

		/// <summary>
		/// Static Const Get Signatures
		/// </summary>
		/// <returns>Returns a Vector of all prescribed Attributes</returns>
		static const Vector<Signature> GetSignature();

	private:
		std::string _actionToDelete;

	};

	ConcreteFactory(ActionDestroy, Scope)
}


