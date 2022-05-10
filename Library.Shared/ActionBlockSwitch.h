#pragma once
#include "ActionBlock.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An ActionBlockSwitch Class, inherits from ActionBlock
	/// </summary>
	class ActionBlockSwitch : public ActionBlock
	{
			RTTI_DECLARATIONS(ActionBlockSwitch, ActionBlock)

		public:
			/// <summary>
			/// Default Constructor
			/// </summary>
			ActionBlockSwitch();

			/// <summary>
			/// Virtual Default Destructor
			/// </summary>
			virtual ~ActionBlockSwitch() = default;

			/// <summary>
			/// Default Copy Constructor
			/// </summary>
			/// <param name="other"> The ActionBlockSwitch that will be copied</param>
			ActionBlockSwitch(const ActionBlockSwitch & other) = default;

			/// <summary>
			/// Copy Assignment Operator
			/// </summary>
			/// <param name="other"> The ActionBlockSwitch that will be copied from</param>
			/// <returns> This ActionBlockSwitch, where the data was copied to</returns>
			ActionBlockSwitch& operator=(const ActionBlockSwitch & other) = default;

			/// <summary>
			/// Move Constructor
			/// </summary>
			/// <param name="rhs"> The ActionBlockSwitch that will be moved</param>
			ActionBlockSwitch(ActionBlockSwitch && other) = default;

			/// <summary>
			/// Move Assignment Operator
			/// </summary>
			/// <param name="rhs"> The ActionBlockSwitch that will be moved</param>
			/// <returns> A refernce the this ActionBlockSwitch, that has had data moved into it</returns>
			ActionBlockSwitch& operator=(ActionBlockSwitch && other) = default;

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
			virtual ActionBlockSwitch* Clone() const override;

			/// <summary>
			/// Gets Switch Case's Data Member
			/// </summary>
			/// <returns> A Const string ref that is the Switch Case Value</returns>
			const std::string& GetSwitchValue() const;


			/// <summary>
			/// Sets the Switch Case Data Member
			/// </summary>
			/// <param name="string"> A const string ref that will be moved into the Switch Case Data Member, do not use the moved variable after this</param>
			void SetSwitchValue(const std::string& string);


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
			ActionBlockSwitch(IdType typeID);

		private:
			std::string _value;

	};

		ConcreteFactory(ActionBlockSwitch, Scope)
}


