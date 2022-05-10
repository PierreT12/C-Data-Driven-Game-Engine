namespace FieaGameEngine
{
	/// <summary>
	/// A Single Linked List
	/// </summary>
	/// <typeparam name="_Type">The type of Single Linked List that this will be</typeparam>
	template <typename _Type>
	class SList final
	{

	private:		
		struct Node final
		{			
			_Type _Data;	
			Node* _Next;

			//Needed otherwise it'll try to find and call a Default constructor that may
			//Not exsist, Not all classes use one
			Node(const _Type& data, Node* next = nullptr);
		};


	public:

		/// <summary>
		/// An Iterator for a Single Linked List
		/// </summary>
		class Iterator final
		{
		public:
			/// <summary>
			/// Makes sure that SList can call the private constructor
			/// </summary>
			friend class SList;

			/// <summary>
			/// Default Constructor
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Default Copy Constructor
			/// </summary>
			/// <param name="other">The other Iterator you want to copy from</param>
			Iterator(const Iterator& other) = default;

			/// <summary>
			/// Default Destructor
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// Operator that compares if two Iterators are not equal
			/// </summary>
			/// <param name="other">The other Iterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Operator that compares if two Iterators are equal
			/// </summary>
			/// <param name="other">The other Iterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Returns the data inside the Node that the Iterator is at on the list
			/// </summary>
			/// <returns>Data that is within the Node the Iterator is pointing to</returns>
			_Type& operator*() const;

			/// <summary>
			/// Moves to the next Node on the List, no copy
			/// </summary>
			/// <returns> The Iterator pointing to the next Node on the list</returns>
			Iterator& operator++();

			/// <summary>
			/// Moves to the next Node on the List copies the data before increasing
			/// </summary>
			/// <returns> The Iterator pointing to the same Node on the list</returns>
			Iterator operator++(int);


			



		private:

			/// <summary>
			/// Constructor for Iterator
			/// </summary>
			/// <param name="Owner">The Single Linked List that will "own" this Iterator</param>
			/// <param name="Node">The Node this Iterator will be pointing to</param>
			Iterator(const SList& Owner, Node* Node = nullptr);


			const SList* _owner{ nullptr };
			Node* _node{ nullptr };

		};



		class ConstIterator final
		{
		public:

			/// <summary>
			/// Makes sure that SList can call the private constructor
			/// </summary>
			friend class SList;

			/// <summary>
			/// Default Constructor
			/// </summary>
			ConstIterator() = default;


			/// <summary>
			/// A ConstIterator Constructor that can use an Iterator to Construct
			/// </summary>
			/// <param name="other">The iterator that it will use to construct</param>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// Default Copy Constructor
			/// </summary>
			/// <param name="other">The other Iterator you want to copy from</param>
			ConstIterator(const ConstIterator& other) = default;

			/// <summary>
			/// Default Destructor
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// Operator that compares if two ConstIterators are not equal
			/// </summary>
			/// <param name="other">The other ConstIterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Operator that compares if two ConstIterators are equal
			/// </summary>
			/// <param name="other">The other ConstIterator that is going to be compared</param>
			/// <returns>A bool depending on if the result is true or false</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Returns the data inside the Node that the ConstIterator is at on the list
			/// </summary>
			/// <returns>Data that is within the Node the ConstIterator is pointing to</returns>
			const _Type& operator*()const;

			/// <summary>
			/// Moves to the next Node on the List, no copy
			/// </summary>
			/// <returns> The ConstIterator pointing to the next Node on the list</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Moves to the next Node on the List copies the data before increasing
			/// </summary>
			/// <returns> The ConstIterator pointing to the same Node on the list</returns>
			ConstIterator operator++(int);

			

		private:
			/// <summary>
			/// Constructor for ConstIterator
			/// </summary>
			/// <param name="Owner">The Single Linked List that will "own" this ConstIterator</param>
			/// <param name="Node">The Node this ConstIterator will be pointing to</param>
			ConstIterator(const SList& Owner, Node* Node = nullptr);

			


			const SList* _owner{ nullptr };
			Node* _node{ nullptr };




		};



	public:
		
		/// <summary>
		/// Default Constructor
		/// </summary>
		SList();

		/// <summary>
		/// Copy Constructor that does a Deep Copy.
		/// </summary>
		/// <param name="other">The source list that will be copied from.</param>
		SList(const SList& other);

		/// <summary>
		/// Copy Operator that makes a deep copy of a list.
		/// </summary>
		/// <param name="other">The sourcelist that it is copying from.</param>
		/// <returns>A Single Linked list that the source data was copied into.</returns>
		SList<_Type> operator=(const SList& other);


		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The r value data </param>
		SList<_Type>(SList&& rhs) noexcept;


		/// <summary>
		/// The Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The Rvalue that will be moved</param>
		/// <returns> The SList the data was moved into</returns>
		SList& operator=(SList&& rhs)  noexcept;


		/// <summary>
		/// Returns the first _Type from the list
		/// </summary>
		/// <returns>The _Type at the front of the list as a reference.</returns>
		_Type& Front();

		/// <summary>
		/// Returns the first _Type from the list. This is a const version.
		/// </summary>
		/// <returns>The _Type at the front of the list as a reference</returns>
		const _Type& Front() const;

		
		/// <summary>
		/// Pushes a _Type given to the front of the list.
		/// </summary>
		/// <param name="data">A _Type that will be put into a Node</param>
		Iterator PushFront(const _Type& data);


		/// <summary>
		/// Removes the first Node from the list
		/// </summary>
		void PopFront();
		
		/// <summary>
		/// Returns the last item from the list as a reference.
		/// </summary>
		/// <returns>The _Type that is at the back of the list as a reference.</returns>
		_Type& Back();

		/// <summary>
		/// Returns the last item from the list as a reference. Const Version
		/// </summary>
		/// <returns>The _Type that is at the back of the list as a reference.</returns>
		const _Type& Back() const;

		/// <summary>
		/// Puts a given _Type data on the back of the list in a Node.
		/// </summary>
		/// <param name="data"> Takes in a reference to the _Type Data that will be added to the back of the list.</param>
		Iterator PushBack(const _Type& data);


		/// <summary>
		/// Puts a given _Type data on the back of the list in a Node. Move Version. The data passed into this can no longer be used since it's moved.
		/// </summary>
		/// <param name="data"> Takes in a reference to the _Type Data that will be added to the back of the list.</param>
		Iterator PushBack(_Type&& data);

		/// <summary>
		/// Removes the last Node from the List
		/// </summary>
		void PopBack();


		/// <summary>
		/// Gets the size of the list. Const Version.
		/// </summary>
		/// <returns>The size of the list as an size_t.</returns>
		const std::size_t& Size() const;


		/// <summary>
		/// Checks to see if the list is empty or not. Const version
		/// </summary>
		/// <returns>A bool, true if it is empty, false if it's not.</returns>
		const bool IsEmpty() const;

		/// <summary>
		/// Clears the list of all Nodes and resets the size.
		/// </summary>
		void ClearList();

	
		/// <summary>
		/// Destrctor that destroys the list
		/// </summary>
		~SList();		
		
	private:
		std::size_t _size;

		Node* _front;

		Node* _back;

		

	public:

		/// <summary>
		/// Returns an Iterator at the start of the Single Linked List
		/// </summary>
		/// <returns>An Iterator at the start of the List</returns>
		Iterator begin();

		/// <summary>
		/// Returns an Iterator past the end of the list.
		/// </summary>
		/// <returns>Returns an Iterator past the end of the list.</returns>
		Iterator end();


		Iterator validEnd();

		/// <summary>
		/// Returns a ConstIterator from a const list that points to the front of said list
		/// </summary>
		/// <returns>A ConstIterator to the front of the list</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns a ConstIterator from a const list that points past the end of said list
		/// </summary>
		/// <returns>A ConstIterator that points past the end of the list</returns>
		ConstIterator end() const;



		ConstIterator validEnd() const;
		
		/// <summary>
		/// Returns a ConstIterator from a non const list that points to the front of said list
		/// </summary>
		/// <returns>A ConstIterator to the front of the list</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns a ConstIterator from a non const list that points past the end of said list
		/// </summary>
		/// <returns>A ConstIterator that points past the end of the list</returns>
		ConstIterator cend() const;


		ConstIterator cvalidEnd() const;


		/// <summary>
		/// Inserts a given data, after a given Iterator
		/// </summary>
		/// <param name="it">An Iterator that points to the node we want to insert after</param>
		/// <param name="data">The data we want to insert</param>
		void InsertAfter(const Iterator& it, const _Type& data );

		/// <summary>
		/// Returns an Iterator of the given data, if it is on the list Non Const Version
		/// </summary>
		/// <param name="data"> The data we're searching for</param>
		/// <param name="equalityFunctior"> A functor if a custom datatype is used</param>
		/// <returns> A Iterator of the data if it could find so, or a null Iterator</returns>
		Iterator Find(const _Type& data, std::function<bool(const _Type&, const _Type&)> equalityFunctior = std::equal_to<_Type>());

		/// <summary>
		/// Returns a ConstIterator of the given data, if it is on the list Const Version
		/// </summary>
		/// <param name="data"> The data we're searching for</param>
		/// <param name="equalityFunctior"> A functor if a custom datatype is used</param>
		/// <returns> A ConstIterator of the data if it could find so, or a null ConstIterator</returns>
		ConstIterator Find(const _Type& data, std::function<bool(const _Type&, const _Type&)> equalityFunctior = std::equal_to<_Type>()) const;

		/// <summary>
		/// Removes the given data from the list without causing a memory leak, if it is found
		/// </summary>
		/// <param name="data">The data you want to remove from the list</param>
		void Remove(const _Type& data);



	};


}
#include "SList.inl"