#pragma once
#include "Transform.h"
#include "Action.h"
namespace FieaGameEngine
{
	/// <summary>
	/// A GameObject class, inherits from Attributed
	/// </summary>
	class GameObject : public Attributed 
	{
		RTTI_DECLARATIONS(GameObject, Attributed)

	
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		GameObject();

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		virtual ~GameObject() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The GameObject that will be copied</param>
		GameObject(const GameObject& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The GameObject that will be copied from</param>
		/// <returns> This GameObject, where the data was copied to</returns>
		GameObject& operator=(const GameObject& other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The GameObject that will be moved</param>
		GameObject(GameObject&& other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The GameObject that will be moved</param>
		/// <returns> A refernce the this GameObject, that has had data moved into it</returns>
		GameObject& operator=(GameObject&& other) = default;

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
		virtual bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Virtual Override of Clone
		/// </summary>
		/// <returns>Returns a copy of this GameObject</returns>
		virtual GameObject* Clone() const override;

		/// <summary>
		/// Static Const Get Signatures
		/// </summary>
		/// <returns>Returns a Vector of all prescribed Attributes</returns>
		static const Vector<Signature> GetSignature();

		/// <summary>
		/// Virtual Update Method, updates all children as well
		/// </summary>
		/// <param name="gameTime"> The new gametime signaling that the game is moving the the next frame</param>
		virtual void Update(const GameState& gamestate);

		/// <summary>
		/// Get the Object Name
		/// </summary>
		/// <returns> The Object Name as a const string ref</returns>
		const std::string& GetObjectName() const;

		/// <summary>
		/// Get the Object Tag
		/// </summary>
		/// <returns> The Object Tag as a const string ref</returns>
		const std::string& GetObjectTag() const;

		/// <summary>
		/// Get the Object's Position
		/// </summary>
		/// <returns> The Object's Position as a const glm::Vec4 ref</returns>
		const glm::vec4& GetPosition() const;

		/// <summary>
		/// Get the Object's Rotation
		/// </summary>
		/// <returns> The Object's Rotation as a const glm::Vec4 ref</returns>
		const glm::vec4& GetRotation() const;

		/// <summary>
		/// Get the Object's Scale
		/// </summary>
		/// <returns> The Object's Scale as a const glm::Vec4 ref</returns>
		const glm::vec4& GetScale() const;

		/// <summary>
		/// Sets the Object's Name
		/// </summary>
		/// <param name="name"> A const string ref to the name that the object will be set to. This data will be moved, so do not use it after this</param>
		void SetObjectName(const std::string& name);

		/// <summary>
		/// Sets the Object's Tag
		/// </summary>
		/// <param name="tag"> A const string ref to the tag that the object will be set to. This data will be moved, so do not use it after this</param>
		void SetObjectTag(const std::string& tag);

		/// <summary>
		/// Sets the Object's Position
		/// </summary>
		/// <param name="position"> A const glm::vec4 ref that will be the object's new position </param>
		void SetPosition(const glm::vec4& position);

		/// <summary>
		/// Sets the Object's Rotation
		/// </summary>
		/// <param name="roatation"> A const glm::vec4 ref that will be the object's new rotation </param>
		void SetRotation(const glm::vec4& rotation);

		/// <summary>
		/// Sets the Object's Scale
		/// </summary>
		/// <param name="scale"> A const glm::vec4 ref that will be the object's new scale </param>
		void SetScale(const glm::vec4& scale);


		const Datum& GetActions() const;

		void CreateAction(const std::string& className, const std::string& actionName);

		void ClearCreateQueue();
		void ClearDestroyQueue();


	protected:
		std::string _name{"GameObject"};
		Transform _transform;
		std::string _tag{ "null" };
		
		/// <summary>
		/// Game Object Constructor that takes a typeID, Protected so the user cannot directly invoke it
		/// </summary>
		/// <param name="typeID"> A RTTI Type ID</param>
		GameObject(IdType typeID);

	private:
		SList<Action*> _pendingDelete;
		std::string _actions{ "Actions" };
		
	};

	ConcreteFactory(GameObject, Scope)
}


