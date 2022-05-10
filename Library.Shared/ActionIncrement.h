#pragma once
#include "Action.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An ActionIncrement Class, Inhreits from Action
	/// </summary>
	class ActionIncrement : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action)

	public:

		/// <summary>
		/// Default Constructor
		/// </summary>
		ActionIncrement();

		/// <summary>
		/// Virtual Default Destructor
		/// </summary>
		virtual ~ActionIncrement() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The ActionIncrement that will be copied</param>
		ActionIncrement(const ActionIncrement & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The ActionIncrement that will be copied from</param>
		/// <returns> This ActionIncrement, where the data was copied to</returns>
		ActionIncrement& operator=(const ActionIncrement & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The ActionIncrement that will be moved</param>
		ActionIncrement(ActionIncrement && other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The ActionIncrement that will be moved</param>
		/// <returns> A refernce the this ActionIncrement, that has had data moved into it</returns>
		ActionIncrement& operator=(ActionIncrement && other) = default;

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
		/// Sets the Target Data Member
		/// </summary>
		/// <param name="target"> A const string ref that is moved into the Target Data Member, Do not use after moved</param>
		void SetTarget(const std::string& target);

		/// <summary>
		/// Sets the Step Data Member
		/// </summary>
		/// <param name="step"> A Float that will be the new step</param>
		void SetStep(float step);

		/// <summary>
		/// Returns the Target Data Member
		/// </summary>
		/// <returns> Returns a const String Ref to the Target Data Member</returns>
		const std::string& GetTarget() const;

		/// <summary>
		/// Gets the Step Data Member
		/// </summary>
		/// <returns> Returns a Float that is a copy of the Step Data Member</returns>
		float GetStep() const;

		/// <summary>
		/// Virtual Override of Clone
		/// </summary>
		/// <returns>Returns a copy of this GameObject</returns>
		virtual ActionIncrement* Clone() const override;

		/// <summary>
		/// Static Const Get Signatures
		/// </summary>
		/// <returns>Returns a Vector of all prescribed Attributes</returns>
		static const Vector<Signature> GetSignature();

	private:
		/// <summary>
		/// Protected Constructor
		/// </summary>
		/// <param name="typeID"> Takes in an RTTI Type ID</param>
		ActionIncrement(IdType typeID);
		std::string _target{ "null" };
		float _step{ 0.0f };
		bool _changedName{ true };
		Datum* _targetDatum{ nullptr };

	};

	ConcreteFactory(ActionIncrement, Scope)
}


