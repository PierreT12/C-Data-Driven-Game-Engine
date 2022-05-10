#pragma once
#include "Action.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An Action Create Class, inherits from Action
	/// </summary>
	class ActionCreate final : public Action
	{
		RTTI_DECLARATIONS(ActionCreate, Action)

	public:

		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionCreate();

		/// <summary>
		/// Virtual Default Destructor
		/// </summary>
		virtual ~ActionCreate() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The ActionCreate that will be copied</param>
		ActionCreate(const ActionCreate & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The ActionCreate that will be copied from</param>
		/// <returns> This ActionCreate, where the data was copied to</returns>
		ActionCreate& operator=(const ActionCreate & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The ActionCreate that will be moved</param>
		ActionCreate(ActionCreate && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The ActionCreate that will be moved</param>
		/// <returns> A refernce the this ActionCreate, that has had data moved into it</returns>
		ActionCreate& operator=(ActionCreate && other) = default;

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
		/// Gets Actor Class Data Member
		/// </summary>
		/// <returns> A Const String Ref to the Action Class Data Member</returns>
		const std::string& GetActionClass() const;

		/// <summary>
		/// Sets the Action Class Data Member
		/// </summary>
		/// <param name="actionClass"> A string that will be moved into Action Class, this item will be moved after calling this method</param>
		void SetActionClass(const std::string& actionClass);


		/// <summary>
		/// Virtual Override of Clone
		/// </summary>
		/// <returns>Returns a copy of this GameObject</returns>
		virtual ActionCreate* Clone() const override;

		/// <summary>
		/// Static Const Get Signatures
		/// </summary>
		/// <returns>Returns a Vector of all prescribed Attributes</returns>
		static const Vector<Signature> GetSignature();

	private:
		std::string _actionClass;

	};

	ConcreteFactory(ActionCreate, Scope)
}


