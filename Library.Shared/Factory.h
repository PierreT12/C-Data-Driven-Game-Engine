#pragma once
#include "HashMap.h"
namespace FieaGameEngine
{
	template <typename _Type>
	
	/// <summary>
	/// Template Factory Class
	/// </summary>
	class Factory
	{
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		Factory() = default;

		/// <summary>
		/// Virtual Defualt Destructor
		/// </summary>
		virtual ~Factory() = default;

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The Factory that will be copied</param>
		Factory(const Factory& other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The Factory that will be moved</param>
		Factory(Factory&& rhs) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The Factory that will be copied from</param>
		/// <returns> This Factory, where the data was copied to</returns>
		Factory& operator=(const Factory& other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The Factory that will be moved</param>
		/// <returns> A refernce the this factory, that has had data moved into it</returns>
		Factory& operator=(Factory&& rhs) = default;

		/// <summary>
		/// Finds a given Factory in the main, static Factory
		/// </summary>
		/// <param name="key"> The key of the factory that is being serached for</param>
		/// <returns> A const pointer to the const Factory that was found</returns>
		static const Factory<_Type>* const Find(const std::string& key);

		/// <summary>
		/// Adds a Factory to the List of Factories
		/// </summary>
		/// <param name="factory"> A ref to the Factory that will be added</param>
		/// <returns> True/False, depending on if this factory was added or not</returns>
		static bool AddFactory(Factory<_Type>& factory);

		/// <summary>
		/// Removes a Factory to the List of Factories
		/// </summary>
		/// <param name="factory"> A ref to the Factory that will be removed</param>
		/// <returns> True/False, depending on if this factory was removed or not</returns>
		static bool RemoveFactory(Factory<_Type>& factory);

		/// <summary>
		/// Clears the List of Factories
		/// </summary>
		static void ClearList();

		/// <summary>
		/// Creates an object based on the class name given
		/// </summary>
		/// <param name="className"> A string of the Object type that will be created</param>
		/// <returns> A pointer to the new object that was created</returns>
		static _Type* Create(const std::string& className);



		/// <summary>
		/// Size, Static
		/// </summary>
		/// <returns> The Amount of Factories in the Static HashMap</returns>
		static size_t Size();

		/// <summary>
		/// IsEmpty, Static
		/// </summary>
		/// <returns> True/False, if the Factory HashMap is Empty or not</returns>
		static bool IsEmpty();

	private:
		static HashMap<const std::string, const Factory<_Type>* const> _hashMap;

		/// <summary>
		/// Private Virtual Create Method
		/// </summary>
		/// <returns> A pointer to the new object created</returns>
		virtual _Type* Create() const = 0;

		/// <summary>
		/// Returns this Factory's assoicated Class Name
		/// </summary>
		/// <returns> A string of this Factory's Class Name</returns>
		virtual const std::string& ClassName() const = 0 ;
	};



}
#include "Factory.inl"

/// <summary>
/// Macro to Create Concrete Factories
/// </summary>
#define ConcreteFactory(Type, AbstractType)\
class Type ## Factory : public Factory<AbstractType>\
{\
public:\
	Type ## Factory():\
		_className(#Type)\
	{\
		AddFactory(*this);\
	}\
\
	~Type ## Factory()\
	{\
		RemoveFactory(*this);\
	}\
	const std::string& ClassName() const override\
	{\
		return _className;\
	}\
\
	Type* Create() const override\
	{\
		return new Type();\
	}\
private:\
	std::string _className;\
};\
