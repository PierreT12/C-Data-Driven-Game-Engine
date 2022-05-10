#pragma once
#include "Action.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An Action Block Class, inherits from Action
	/// </summary>
	class ActionBlock : public Action
	{
		RTTI_DECLARATIONS(ActionBlock, Action)

	public:

		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionBlock();

		/// <summary>
		/// Virtual Default Destructor
		/// </summary>
		virtual ~ActionBlock() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The ActionBlock that will be copied</param>
		ActionBlock(const ActionBlock& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The ActionBlock that will be copied from</param>
		/// <returns> This ActionBlock, where the data was copied to</returns>
		ActionBlock& operator=(const ActionBlock& other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The ActionBlock that will be moved</param>
		ActionBlock(ActionBlock&& other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The ActionBlock that will be moved</param>
		/// <returns> A refernce the this ActionBlock, that has had data moved into it</returns>
		ActionBlock& operator=(ActionBlock&& other) = default;

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
		/// Virtual Override of Clone
		/// </summary>
		/// <returns>Returns a copy of this GameObject</returns>
		virtual ActionBlock* Clone() const override;

		/// <summary>
		/// Static Const Get Signatures
		/// </summary>
		/// <returns>Returns a Vector of all prescribed Attributes</returns>
		static const Vector<Signature> GetSignature();

	protected:

		/// <summary>
		/// Protected Constructor
		/// </summary>
		/// <param name="typeID"> Takes in an RTTI Type ID</param>
		ActionBlock(IdType typeID);
	};

	ConcreteFactory(ActionBlock, Scope)
}


