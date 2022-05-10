#include "TypeRegistry.h"
namespace FieaGameEngine
{
	/// <summary>
	/// An Abstract Attributed Class
	/// </summary>
	class Attributed : public Scope
	{
		/// <summary>
		/// RTTI Declarations
		/// </summary>
		RTTI_DECLARATIONS(Attributed, Scope)

	public:

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="typeID">The TypeID of the C++ Class that will have Attributes created for it</param>
		Attributed(IdType typeID);

		/// <summary>
		/// Default Desturctor
		/// </summary>
		virtual ~Attributed() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The Attribute that will be copied</param>
		Attributed(const Attributed& other);

		/// <summary>
		/// Default Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The other Attribute that will be copied</param>
		/// <returns> A ref to the new copied attribute</returns>
		Attributed& operator=(const Attributed& other);

		/// <summary>
		/// Default Move Constructor
		/// </summary>
		/// <param name="other"> The Attribute that will be moved</param>
		Attributed(Attributed&& other) noexcept;

		/// <summary>
		/// Default Move Assignment Operator
		/// </summary>
		/// <param name="other"> The other Attribute that will be moved</param>
		/// <returns> A ref to the new moved Attribute</returns>
		Attributed& operator=(Attributed&& other) noexcept;

		/// <summary>
		/// To String Override 
		/// </summary>
		/// <returns> A string representing a Attributed</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// A Pure Virtual Clone
		/// </summary>
		/// <returns> An Attributed Pointer</returns>
		virtual Attributed* Clone() const override = 0;

		/// <summary>
		/// Popuates and Creates the Prescribed Attributes
		/// </summary>
		/// <param name="typeID"> The type of Attributed that will be populated</param>
		void Populate(IdType typeID);

		/// <summary>
		/// Is Key/Value Pair Attribute
		/// </summary>
		/// <param name="key"> The key of the key value pair that will be checked</param>
		/// <returns> A true/false depending of if the pair is an Attribute or not</returns>
		bool IsAttribute(const std::string& key) const;
		
		/// <summary>
		/// Is Key/Value Pair Prescribe Attribute
		/// </summary>
		/// <param name="key"> The key of the key value pair that will be checked</param>
		/// <returns> A true/false depending of if the pair is a Prescribe Attribute or not</returns>
		bool IsPrescribedAttribute(const std::string& key) const;


		/// <summary>
		/// Is Key/Value Pair Auxiliary Attribute
		/// </summary>
		/// <param name="key"> The key of the key value pair that will be checked</param>
		/// <returns> A true/false depending of if the pair is an Auxiliary Attribute or not</returns>
		bool IsAuxiliaryAttribute(const std::string& key) const;
		
		/// <summary>
		/// Appending Auxiliary Attribute
		/// </summary>
		/// <param name="key"> The key of the Auxiliary Attribute that will try to be Appeneded</param>
		/// <returns> A Datum ref to eithe the Appened Auxiliary Attribute or a Datum ref to an Attribute that already is there</returns>
		Datum& AppendAuxiliaryAttribute(const std::string& key);

		
	private:
		/// <summary>
		/// Reassigns the pointers on a copied or moved Attribute
		/// </summary>
		/// <param name="typeInstance"> The Type Class Instance that needs its Prescribed Attribute pointers reassigned</param>
		void ReasignPointers(size_t typeInstance);


		size_t _prescribedSize{ 0 };

	};

}

