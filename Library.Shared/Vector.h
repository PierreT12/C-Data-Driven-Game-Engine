namespace FieaGameEngine
{
	/// <summary>
	/// A Vector Class
	/// </summary>
	template <typename _Type>
	class Vector final
	{

	public:

		using value_type = _Type;
		using size_type = size_t;
		using reference = _Type;
		using pointer = _Type*;
		using difference_type = std::ptrdiff_t;
		
		
		/// <summary>
		/// Constuctor for Vector
		/// </summary>
		/// <param name="capacity"> Provides a default capacity</param>
		/// THIS IS A QUICK FIX
		explicit Vector( size_t capacity = 10);
		explicit Vector(std::initializer_list<_Type> list, size_t capacity = 3);

		/// <summary>
		/// Default Destructor
		/// </summary>
		~Vector();

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other"> Takes in another Vector of _Type</param>
	    Vector(const Vector& other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The r value data </param>
	    Vector(Vector&& rhs)  noexcept;

		/// <summary>
		/// The Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The Vector that will be copied from</param>
		/// <returns> The copied Vector</returns>
		Vector& operator=(const Vector& other);

		/// <summary>
		/// The Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The Rvalue that will be moved</param>
		/// <returns> The Vector the data was moved into</returns>
		Vector& operator=(Vector&& rhs)  noexcept;

		/// <summary>
		/// The Bracket Operator
		/// </summary>
		/// <param name="index"> The index of the value you want from the Vector</param>
		/// <returns> The value you want if it is within range</returns>
		reference& operator[](size_type index);

		/// <summary>
		/// The Bracket Operator Const Version
		/// </summary>
		/// <param name="index"> The index of the value you want from the Vector</param>
		/// <returns> The value you want if it is within range</returns>
		const reference& operator[](size_type index) const;

		/// <summary>
		/// Gets the data at that index if possible
		/// </summary>
		/// <param name="index"> The index of the value you want from the Vector </param>
		/// <returns> The value you want if it is within range </returns>
		reference& At(size_type index);

		/// <summary>
		/// Gets the data at that index if possible Const Version
		/// </summary>
		/// <param name="index"> The index of the value you want from the Vector </param>
		/// <returns> The value you want if it is within range </returns>
		const reference& At(size_type index) const;

		/// <summary>
		/// Removes the last element from the Vector
		/// </summary>
		void PopBack();

		/// <summary>
		/// Adds a spot behind the last index in the list and increases size
		/// </summary>
		/// <param name="data"> The data that will be added to the list</param>
		void PushBack(const reference& data);

		/// <summary>
		/// Returns true if the Vector is Empty
		/// </summary>
		/// <returns> True/False depending on if the Vector is empty or not</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Returns the value at the front of the Vector
		/// </summary>
		/// <returns> A refernce to the value at the front of the Vector </returns>
		reference& Front();

		/// <summary>
		/// Returns the value at the front of the Vector Const Version
		/// </summary>
		/// <returns> A refernce to the value at the front of the Vector</returns>
		const reference& Front() const;

		/// <summary>
		/// Returns the value at the back of the Vector
		/// </summary>
		/// <returns>A refernce to the value at the back of the Vector </returns>
		reference& Back();

		/// <summary>
		/// Returns the value at the back of the Vector Const Version
		/// </summary>
		/// <returns>A refernce to the value at the back of the Vector </returns>
		const reference& Back() const;

		/// <summary>
		/// Gets the Size of the Vector
		/// </summary>
		/// <returns>Returns the size of the Vector</returns>
		size_type Size() const;

		/// <summary>
		/// Returns the capacity
		/// </summary>
		/// <returns> The capacity as a size_t ref</returns>
		size_type Capacity() const;

		/// <summary>
		/// Reserves more bytes for the Vector to use later on
		/// </summary>
		/// <param name="newCapacity"> The new capacity of the Vector, must be bigger than the current</param>
		void Reserve(size_type newCapacity);


		/// <summary>
		/// Clears the Vector of all objects, keeps the same capacity
		/// </summary>
		void ClearList();


		void Resize( const size_t size);



	private:
		reference* _front;

		size_type _size;
		size_type _capacity;



	public:

		/// <summary>
		/// An Iterator Class for Vector
		/// </summary>
		class Iterator
		{
			friend Vector;
		public:

			using value_type = _Type;
			using size_type = size_t;
			using reference = _Type;
			using pointer = _Type*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;
		
			/// <summary>
			/// Default Constructor
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Default Destructor
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// Default Copy Constructor
			/// </summary>
			/// <param name="other">The other Iterator you want to copy from</param>
			Iterator(const Iterator& other);

			/// <summary>
			/// The Move Constructor
			/// </summary>
			/// <param name="rhs">  The r value data </param>
			Iterator(Iterator&& rhs) = default;

			/// <summary>
			/// The Copy Assignment Operator
			/// </summary>
			/// <param name="other"> The Vector that the data will be copied from </param>
			/// <returns> A reference to the vector that was copied to </returns>
			Iterator& operator=(const Iterator& other);

			/// <summary>
			/// The Move Assignment Operator
			/// </summary>
			/// <param name="other"> The Vector that the data will be moved from </param>
			/// <returns> A reference to the vector that was moved to </returns>
			Iterator& operator=(Iterator&& rhs) = default;

			/// <summary>
			/// Returns the data assoicated with the index that the Iterator is at on the Vector
			/// </summary>
			/// <returns>Data that is assoicated with that index that the Iterator is pointing to</returns>
			reference& operator*() const;

			/// <summary>
			/// Moves to the next value on the Vector, no copy
			/// </summary>
			/// <returns> The Iterator pointing to the next value on the Vector</returns>
			Iterator& operator++();

			/// <summary>
			/// Moves to the next value on the Vector copies the data before increasing
			/// </summary>
			/// <returns> The Iterator pointing to the same spot on the Vector</returns>
			Iterator operator++(int);

			/// <summary>
			/// Operator that compares if two Iterators are equal
			/// </summary>
			/// <param name="other">The other Iterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Operator that compares if two Iterators are not equal
			/// </summary>
			/// <param name="other">The other Iterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator!=(const Iterator& other) const;



		private:

			/// <summary>
			/// Constructor for Iterator
			/// </summary>
			/// <param name="Owner">The Vector Vector that will "own" this Iterator</param>
			/// <param name="Index">The spot in the Vector that the value is at</param>
			Iterator(Vector& Owner, size_type Index = 0);

			Vector* _owner{ nullptr };
			size_type _index{ 0 };
		};

		/// <summary>
		/// An ConstIterator Class for Vector
		/// </summary>
		class ConstIterator
		{
			friend Vector;

		public:

			using value_type = _Type;
			using size_type = size_t;
			using reference = _Type;
			using pointer = _Type*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;


			/// <summary>
			/// Default Constructor
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Default Destructor
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// A ConstIterator Constructor that can use an Iterator to Construct
			/// </summary>
			/// <param name="other">The Iterator that it will use to construct</param>
			ConstIterator(const Iterator& other);


			/// <summary>
			/// Default Copy Constructor
			/// </summary>
			/// <param name="other">The other ConstIterator you want to copy from</param>
			ConstIterator(const ConstIterator & other);

			/// <summary>
			/// The Move Constructor
			/// </summary>
			/// <param name="rhs">  The r value data </param>
			ConstIterator(ConstIterator && rhs) = default;

			/// <summary>
			/// The Copy Assignment Operator
			/// </summary>
			/// <param name="other"> The Vector that the data will be copied from </param>
			/// <returns> A reference to the vector that was copied to </returns>
			ConstIterator& operator=(const ConstIterator & other);

			/// <summary>
			/// The Move Assignment Operator
			/// </summary>
			/// <param name="other"> The Vector that the data will be moved from </param>
			/// <returns> A reference to the vector that was moved to </returns>
			ConstIterator& operator=(ConstIterator&& rhs) = default;

			/// <summary>
			/// Returns the data assoicated with the index that the ConstIterator is at on the Vector
			/// </summary>
			/// <returns>Data that is assoicated with that index that the ConstIterator is pointing to</returns>
			const reference& operator*() const;

			/// <summary>
			/// Moves to the next value on the Vector, no copy
			/// </summary>
			/// <returns> The ConstIterator pointing to the next value on the Vector</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Moves to the next value on the Vector copies the data before increasing
			/// </summary>
			/// <returns> The ConstIterator pointing to the same spot on the Vector</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// Operator that compares if two ConstIterators are equal
			/// </summary>
			/// <param name="other">The other ConstIterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Operator that compares if two ConstIterators are not equal
			/// </summary>
			/// <param name="other">The other ConstIterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator!=(const ConstIterator& other) const;



		private:

			/// <summary>
			/// Constructor for ConstIterator
			/// </summary>
			/// <param name="Owner">The Vector Vector that will "own" this ConstIterator</param>
			/// <param name="Index">The spot in the Vector that the value is at</param>
			ConstIterator(const Vector& Owner, size_type Index = 0);

			//ConstIterator(const Vector& Owner, size_type Index = 0);

			

			const Vector* _owner{ nullptr };
			size_type _index{ 0 };
		};

		/// <summary>
		/// Returns an Iterator of the given data, if it is on the Vector 
		/// </summary>
		/// <param name="data"> The data we're searching for</param>
		/// <param name="equalityFunctior"> A functor if a custom datatype is used</param>
		/// <returns> A Iterator of the data if it could find so, or the end of the Vector</returns>
		Iterator Find(const reference& data, std::function<bool(const reference&, const reference&)> equalityFunctor = std::equal_to<value_type>());
		
		/// <summary>
		/// Returns an Iterator of the given data, if it is on the Vector Const Version
		/// </summary>
		/// <param name="data"> The data we're searching for</param>
		/// <param name="equalityFunctior"> A functor if a custom datatype is used</param>
		/// <returns> A Iterator of the data if it could find so, or the end of the Vector</returns>
		ConstIterator Find(const reference& data, std::function<bool(const reference&, const reference&)> equalityFunctor = std::equal_to<value_type>()) const;


		/// <summary>
		/// Removes the data assoicated with this iterator within the vector, if it is able to find it
		/// </summary>
		/// <param name="it"> An iterator that's data in the vector will be removed</param>
		/// <returns> A bool either True/False depending on if the data was removed or not</returns>
		bool Remove(const Iterator& it);


		/// <summary>
		/// Removes the data assoicated with this iterator within the vector, if it is able to find it
		/// </summary>
		/// <param name="it"> An iterator that's data in the vector will be removed</param>
		/// <returns> A bool either True/False depending on if the data was removed or not</returns>
		bool Remove(const reference& data);

		/// <summary>
		/// Returns an Iterator at the start of the Vector
		/// </summary>
		/// <returns>An Iterator at the start of the Vector</returns>
		Iterator begin();

		/// <summary>
		/// Returns an Iterator past the end of the Vector
		/// </summary>
		/// <returns>Returns an Iterator past the end of the Vector</returns>
		Iterator end();

		/// <summary>
		/// Returns a ConstIterator from a const list that points to the front of said Vector
		/// </summary>
		/// <returns>A ConstIterator to the front of the Vector</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns a ConstIterator from a const Vector that points past the end of said Vector
		/// </summary>
		/// <returns>A ConstIterator that points past the end of the Vector</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns a ConstIterator from a non const Vector that points to the front of said Vector
		/// </summary>
		/// <returns>A ConstIterator to the front of the Vector</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns a ConstIterator from a non const Vector that points past the end of said Vector
		/// </summary>
		/// <returns>A ConstIterator that points past the end of the Vector</returns>
		ConstIterator cend() const;

	};
	
}

#include "Vector.inl"