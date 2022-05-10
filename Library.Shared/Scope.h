#include "Datum.h"
#include "HashMap.h"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// A Scope Class that inherits from RTTI
	/// </summary>
	class Scope : public RTTI
	{
		
		/// <summary>
		/// RTTI Declarations
		/// </summary>
		RTTI_DECLARATIONS(Scope, RTTI)


	public:
		using HashMapType = HashMap<std::string, Datum>::PairType*;
		

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="parent"> Takes in another Scope that will be it's parent, defaulted to nullptr</param>
		/// <param name="capacity"> The Capacity of the Vector that will keep track of the order</param>
		Scope(Scope* parent = nullptr, size_t capacity = 3);

		/// <summary>
		/// Default Destructor, is virtual since inheritance occured
		/// </summary>
		virtual ~Scope();

		/// <summary>
		/// Default Copy Constructor
		/// </summary>
		/// <param name="other"> The Scope that will be copied from</param>
		Scope(const Scope& other);

		/// <summary>
		/// Default Move Constructor
		/// </summary>
		/// <param name="rhs"> The Scope that will be moved from</param>
		Scope(Scope&& rhs);

		/// <summary>
		/// Default Copy Assingment
		/// </summary>
		/// <param name="other"> The Scope that will be copied from</param>
		/// <returns> Returns the copied Scope </returns>
		Scope& operator=(const Scope& other);

		/// <summary>
		/// Default Move Assignment
		/// </summary>
		/// <param name="rhs"> The Scope that will be moved from </param>
		/// <returns> The Scope that the data was moved to </returns>
		Scope& operator=(Scope&& rhs);

		/// <summary>
		/// Equals Override for Scopes
		/// </summary>
		/// <param name="rhs"> A RTTI Pointer that will be passed in. The signature must be the same since this is an override</param>
		/// <returns> A bool if the two values are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;
		

		virtual std::string ToString() const override;


		/// <summary>
		/// Finds a Datum within the Scope
		/// </summary>
		/// <param name="key"> The key value that is assoicated with a Datum</param>
		/// <returns> A datum pointer that points to the correct datum, or a nullptr if none is found</returns>
		Datum* Find(const std::string& key);


	protected:
		/// <summary>
		/// Finds a Datum within the Scope
		/// </summary>
		/// <param name="key"> The key value that is assoicated with a Datum</param>
		/// <returns> A datum pointer that points to the correct datum, or a nullptr if none is found</returns>
		std::pair<Datum*, size_t> FindIndex(const std::string& key);

	public:
		/// <summary>
		/// Finds a Datum within the Scope Const Version
		/// </summary>
		/// <param name="key"> The key value that is assoicated with a Datum</param>
		/// <returns> A const datum pointer that points to the correct datum, or a nullptr if none is found</returns>
		const Datum* Find(const std::string& key) const;

		/// <summary>
		/// Seaches for a Datum within a Scope and its Ancestors
		/// </summary>
		/// <param name="str"> The key assoicated with the Datum that is being searched for</param>
		/// <returns> A Datum pointer that points to the found Datum or nullptr if it is not</returns>
		Datum* Search(const std::string& str);

		/// <summary>
		/// Seaches for a Datum within a Scope and its Ancestors Const Version
		/// </summary>
		/// <param name="str"> The key assoicated with the Datum that is being searched for</param>
		/// <returns> A Datum pointer that points to the found Datum or nullptr if it is not</returns>
		const Datum* Search(const std::string& str) const;
		
		/// <summary>
		/// Seaches for a Datum within a Scope and its Ancestors Scope Specific
		/// </summary>
		/// <param name="str"> The key assoicated with the Datum that is being searched for</param>
		/// <param name="scopeFound"> This is also an output param of the Scope that the Datum was found in</param>
		/// <returns> A Datum pointer that points to the found Datum or nullptr if it is not</returns>
		Datum* Search(const std::string& str, Scope*& scopeFound);

		/// <summary>
		/// Seaches for a Datum within a Scope and its Ancestors Scope Specific Const Version
		/// </summary>
		/// <param name="str"> The key assoicated with the Datum that is being searched for</param>
		/// <param name="scopeFound"> This is also an output param of the Scope that the Datum was found in</param>
		/// <returns> A Datum pointer that points to the found Datum or nullptr if it is not</returns>
		const Datum* Search(const std::string& str,  Scope* const & scopeFound) const;
		
		/// <summary>
		/// Appends a new Datum to this Scope
		/// </summary>
		/// <param name="key">The key value that will be assoicated with the Datum that will store whatever type of valid Datum</param>
		/// <returns> The Datum assoicated with the passed in key</returns>
		Datum& Append(const std::string& key);

		/// <summary>
		/// Appends a New nested Scope to the calling Scope
		/// </summary>
		/// <param name="key">The key value that will be assoicated with the Datum that will store this new Scope</param>
		/// <returns> A reference to the new Scope</returns>
		Scope& AppendScope(const std::string& key);
		
		/// <summary>
		/// Adopting a Scope and making it a nested Scope of the Calling Scope
		/// </summary>
		/// <param name="key"> The key value that will be assoicated with the Datum that will store this Scope</param>
		/// <param name="child"> The Scope that will be adopted</param>
		void Adopt(const std::string& key, Scope& child);
		
		/// <summary>
		/// Gets the parent of this Scope
		/// </summary>
		/// <returns> A Scope pointer to the parent of this Scope</returns>
		Scope* GetParent() const;
	
		/// <summary>
		///  Operator[] Key Version (Wrapper for Append)
		/// </summary>
		/// <param name="key"> They key assoicated with a Datum</param>
		/// <returns>A Datum reference associated with said Key</returns>
		Datum& operator[](const std::string& key);
		
		/// <summary>
		/// Operator[] Index Version
		/// </summary>
		/// <param name="index"> The index of the Order Vector that will be accessed</param>
		/// <returns> A Datum reference associated with said Index</returns>
		Datum& operator[](size_t index) const;
		
		/// <summary>
		/// Equal Operator
		/// </summary>
		/// <param name="other"> The other Scope that you will be Comparing</param>
		/// <returns> True/False depending of if they were not equal or equal</returns>
		bool operator==(const Scope& other) const;
		
		/// <summary>
		/// Not Equal Operator
		/// </summary>
		/// <param name="other"> The other Scope that you will be Comparing</param>
		/// <returns> True/False depending of if they were not equal or equal</returns>
		bool operator!=(const Scope& other) const;

		/// <summary>
		/// Returns Bool if the Scope is empty or not
		/// </summary>
		/// <returns> True/False Depending on if the Scope has any data inside of it</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Returns the size of the Scope
		/// </summary>
		/// <returns> A size_t of how many pairs are in the Scope </returns>
		size_t Size() const;

		/// <summary>
		/// Returns bool depending on if the scope calling this is an ancestor of the given scope
		/// </summary>
		/// <param name="scope"> The scope that is seeing if the calling Scope is an ancestor or not</param>
		/// <returns> True/False depending of if the statment is true or not</returns>
		bool IsAncestorOf(const Scope& scope) const;

		/// <summary>
		/// Returns bool depending on if the scope calling this is a Descendant of the given scope
		/// </summary>
		/// <param name="scope"> The scope that is seeing if the calling Scope is an Descendant or not</param>
		/// <returns> True/False depending of if the statment is true or not</returns>
		bool IsDescendantOf(const Scope& scope) const;
		
		/// <summary>
		/// Finding the given Scope within the Scope calling this function 
		/// </summary>
		/// <param name="scope"> The scope that should exsist within the Scope calling this</param>
		/// <returns> A std::pair that has a Datum pointer to the Datum the data is stored in and the index of said data</returns>
		std::pair<Datum*,size_t> FindContainedScope(const Scope& scope);

		/// <summary>
		/// Finding the given Scope within the Scope calling this function Const Version
		/// </summary>
		/// <param name="scope"> The scope that should exsist within the Scope calling this</param>
		/// <returns> A const std::pair that has a Datum pointer to the Datum the data is stored in and the index of said data</returns>
		const std::pair<Datum*,size_t> FindContainedScope(const Scope& scope) const;
		
		/// <summary>
		/// Clears the Scope
		/// </summary>
		void ClearList();
		
		/// <summary>
		/// Orphans the passed in Scope, child must be a Descendant of the Scope calling this method
		/// </summary>
		/// <param name="child"> The child that will be orphaned </param>
		void Orphan(Scope& child);

		/// <summary>
		/// Clones the Scope
		/// </summary>
		/// <returns> A cloned Scope</returns>
		virtual Scope* Clone() const;

		
	protected:
		Scope* _parent{ nullptr };
		HashMap<std::string, Datum> _pairs;
		Vector<HashMapType> _orderInterted;

	};

	ConcreteFactory(Scope, Scope)
}

