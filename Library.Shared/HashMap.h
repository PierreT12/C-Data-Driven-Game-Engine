#pragma once
#include "DefaultHash.h"
#include <cstdint>
#include "SList.h"
#include "Vector.h"
namespace FieaGameEngine
{
	/// <summary>
	/// A Tempalted HashMap
	/// </summary>
	template <typename _TypeKey, typename _TypeData>
	class HashMap final
	{
		

	public:

		using PairType = std::pair<const _TypeKey, _TypeData>;
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;

		/// <summary>
		/// Construtor for the HashMap
		/// </summary>
		/// <param name="buckets"> The number of buckets that the hashmap will have</param>
		/// <param name="hashFunctor"> The hashing functor that the user can provide</param>
		/// <param name="equailityFunctor"> The equality functor that the user can provide</param>
		HashMap(size_t buckets = 10, std::function<size_t(const _TypeKey&)> hashFunctor = DefaultHash<_TypeKey>(), std::function<size_t(const _TypeKey&, const _TypeKey&)> equailityFunctor = std::equal_to<_TypeKey>());

		/// <summary>
		/// Destructor
		/// </summary>
		~HashMap() = default;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other"> The other HashMap that will be copied from </param>
		HashMap(const HashMap& other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> The R value that will be moved from</param>
		HashMap(HashMap&& rhs) noexcept;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The other HashMap that will be copied from </param>
		/// <returns> This Hashmap with the copied data </returns>
		HashMap<_TypeKey, _TypeData>& operator=(const HashMap& other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"> The R value that will be moved from </param>
		/// <returns> This Hashmap with the moved data </returns>
		HashMap<_TypeKey, _TypeData>& operator=(HashMap&& rhs) noexcept;


		/// <summary>
		/// Calculates the Load Factor
		/// </summary>
		/// <returns> The Load Factor as a float</returns>
		float GetLoadFactor() const;

		/// <summary>
		/// Returns the amount of Empty Buckets
		/// </summary>
		/// <returns> The amount of Empty Buckets</returns>
		size_t GetEmptyBuckets() const;

		/// <summary>
		/// Returns all the Buckets (Empty and Full)
		/// </summary>
		/// <returns>Returns all the Buckets</returns>
		size_t GetBuckets() const;


		/// <summary>
		/// Returns the Size
		/// </summary>
		/// <returns>The Size as a size_t</returns>
		size_t Size() const;

		/// <summary>
		/// Returns the data with an assoicated key
		/// </summary>
		/// <param name="key"> A Key Value</param>
		/// <returns> The Data Associated with that Key as a reference</returns>
		_TypeData& At(const _TypeKey& key);

		/// <summary>
		/// Returns the data with an assoicated key Const Version
		/// </summary>
		/// <param name="key"> A Key Value</param>
		/// <returns> The Data Associated with that Key as a const reference</returns>
		const _TypeData& At(const _TypeKey& key) const;

		/// <summary>
		/// Returns the data with an assoicated key, if non exisits, insert with a default type
		/// </summary>
		/// <param name="key"></param>
		/// <returns> The Data Associated with that Key as a reference </returns>
		_TypeData operator[](const _TypeKey& key);

		/// <summary>
		/// Returns if the HashMap is empty or not
		/// </summary>
		/// <returns> A bool which is true/false depending on if the Hashmap is empty</returns>
		bool IsEmpty() const;
		
	

		/// <summary>
		/// Clears the HashMap
		/// </summary>
		void ClearList();

		/// <summary>
		/// Resizes the HashMap to a given size
		/// </summary>
		/// <param name="newSize"> The new size of the HashMap</param>
		/// <returns> The new, resized HashMap</returns>
		HashMap<_TypeKey, _TypeData>& Resize(const size_t newSize = 12);

		/// <summary>
		/// Rehashs the HashMap with a given Functor
		/// </summary>
		/// <param name="hashFunctor"> The new Functor that will do all the hashing</param>
		/// <returns> The new, rehashed hashmap</returns>
		HashMap<_TypeKey, _TypeData>& Rehash( std::function<size_t(const _TypeKey&)> hashFunctor = DefaultHash<_TypeKey>());


	private:

		BucketType _bucket;

		size_t _emptyBucket;

		size_t _size;

		
		std::function<size_t(const _TypeKey&)> _hashFunctor;

		std::function<bool(const _TypeKey&, const _TypeKey&)>  _equalityFunctor;





		/// <summary>
		/// Mods the Hash Value so it can go into a bucket const version
		/// </summary>
		/// <param name="hash"> The hashed value from a key</param>
		/// <returns> The mod hash value</returns>
		size_t Mod(const size_t hash) const ;



		/// <summary>
		/// Preforms both a Hash and a Mod const Version
		/// </summary>
		/// <param name="key"> The key that will be hashed, then mod</param>
		/// <returns> The mod hash value</returns>
		size_t HashMod(const _TypeKey& key) const;


		/// <summary>
		/// Finds the first vaild value in the HashMap
		/// </summary>
		/// <returns>A std::pair of the first bucket index and a SList Iterator</returns>
		std::pair<size_t, typename SList<PairType>::Iterator> FindFirstValue();

		/// <summary>
		/// Finds the first vaild value in the HashMap Const Version
		/// </summary>
		/// <returns>A std::pair of the first bucket index and a SList Iterator</returns>
		std::pair<size_t, typename SList<PairType>::ConstIterator> FindFirstValue() const;


	public:

		/// <summary>
		/// An Iterator Class for HashMap
		/// </summary>
		class Iterator
		{
			
		public:
			friend class HashMap;

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
			/// The Copy Assignment Operator
			/// </summary>
			/// <param name="other"> The HashMap that the data will be copied from </param>
			/// <returns> A reference to the HashMap that was copied to </returns>
			Iterator operator=(const Iterator& other);

			/// <summary>
			/// Moves to the next value on the HashMap, no copy
			/// </summary>
			/// <returns> The Iterator pointing to the next valid value on the HashMap</returns>
			Iterator& operator++();

			/// <summary>
			/// Moves to the next value on the HashMap copies the data before increasing
			/// </summary>
			/// <returns> The Iterator pointing to the same spot on the HashMap</returns>
			Iterator operator++(int);


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
			/// Returns the data assoicated with the index that the Iterator is at on the HashMap
			/// </summary>
			/// <returns>Data that is assoicated with that index that the Iterator is pointing to</returns>
			PairType& operator*() const;

			/// <summary>
			/// Returns a data pointer assoicated with the index that the Iterator is at on the HashMap
			/// </summary>
			/// <returns>Data Pointer that is assoicated with that index that the Iterator is pointing to</returns>
			PairType* operator->() const;



		private:
			size_t _bucketIndex;
			typename ChainType::Iterator _chainIterator;

			HashMap* _owner;

			/// <summary>
			/// Constructor for Iterator
			/// </summary>
			/// <param name="Owner">HashMap that owns the data that the Iterator is pointing to </param>
			/// <param name="BucketIndex"> The index of the BucketType that points to the bucket</param>
			/// <param name="iterator"> A Chaintype Iterator that points a node on the chain</param>
			Iterator(HashMap& Owner, const size_t& BucketIndex, typename ChainType::Iterator iterator);


		};

		/// <summary>
		/// An ConstIterator Class for HashMap
		/// </summary>
		class ConstIterator
		{
			
		public:
			friend class HashMap;

			/// <summary>
			/// Default Constructor
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// A ConstIterator Constructor that can use an Iterator to Construct
			/// </summary>
			/// <param name="other">The Iterator that it will use to construct</param>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// Default Destructor
			/// </summary>
			~ConstIterator() = default;
			
			/// <summary>
			/// Default Copy Constructor
			/// </summary>
			/// <param name="other">The other ConstIterator you want to copy from</param>
			ConstIterator(const ConstIterator& other);



			/// <summary>
			/// The Copy Assignment Operator
			/// </summary>
			/// <param name="other"> The HashMap that the data will be copied from </param>
			/// <returns> A reference to the HashMap that was copied to </returns>
			ConstIterator operator=(const ConstIterator& other);

			/// <summary>
			/// Moves to the next value on the HashMap, no copy
			/// </summary>
			/// <returns> The ConstIterator pointing to the next valid value on the HashMap</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Moves to the next value on the HashMap copies the data before increasing
			/// </summary>
			/// <returns> The ConstIterator pointing to the same spot on the HashMap</returns>
			ConstIterator operator++(int);


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
			/// Returns the data assoicated with the index that the ConstIterator is at on the HashMap
			/// </summary>
			/// <returns>Data that is assoicated with that index that the ConstIterator is pointing to</returns>
			const PairType& operator*() const;

			/// <summary>
			/// Returns a data pointer assoicated with the index that the ConstIterator is at on the HashMap
			/// </summary>
			/// <returns>Data Pointer that is assoicated with that index that the ConstIterator is pointing to</returns>
			const PairType* operator->() const;



		private:

			/// <summary>
			/// Constructor for ConstIterator
			/// </summary>
			/// <param name="Owner">HashMap that owns the data that the ConstIterator is pointing to </param>
			/// <param name="BucketIndex"> The index of the BucketType that points to the bucket</param>
			/// <param name="iterator"> A Chaintype ConstIterator that points a node on the chain</param>
			ConstIterator(const HashMap& Owner, const size_t& BucketIndex, typename SList<PairType>::ConstIterator iterator);

			size_t _bucketIndex;
			typename ChainType::ConstIterator _chainIterator;

			const HashMap* _owner;

			
		};

	public:

		/// <summary>
		/// Sees if the given key is in the HsahMap and returns an Iterator to it
		/// </summary>
		/// <param name="key"> The key that is being looked for in the HsahMap</param>
		/// <returns> A std::pair that contains an Iterator to the spot of the key, and a bool if that key was found</returns>
		std::pair<Iterator, bool> ContainsKey(const _TypeKey& key);

		/// <summary>
		/// Sees if the given key is in the HsahMap and returns a ConstIterator to it
		/// </summary>
		/// <param name="key"> The key that is being looked for in the HsahMap</param>
		/// <returns> A std::pair that contains an ConstIterator to the spot of the key, and a bool if that key was found</returns>
		std::pair<ConstIterator, bool> ContainsKey(const _TypeKey& key) const;

		/// <summary>
		/// Inserts the given pair into the list, if the key is already in the HashMap, that value is returned
		/// </summary>
		/// <param name="pair"> A key/value pair that will be inserted into the list </param>
		/// <returns> A std::pair that contains an Iterator to the spot of the key, and a bool if that key was inserted</returns>
		std::pair<Iterator, bool> Insert(const PairType& pair);


		/// <summary>
		/// Inserts the given pair into the list, if the key is already in the HashMap, that value is returned, Move Version
		/// </summary>
		/// <param name="pair"> A key/value pair that will be inserted into the list. The pair passed into this can no longer be used since it's moved. </param>
		/// <returns> A std::pair that contains an Iterator to the spot of the key, and a bool if that key was inserted</returns>
		std::pair<Iterator, bool> Insert(PairType&& pair);

		/// <summary>
		/// Finds a key/value pair inside the list 
		/// </summary>
		/// <param name="key"> The key of the key/value pair that will be found</param>
		/// <returns> Returns a std::tuple that has an Iterator pointing to the found pair, and a bool that is true/false depending on if the pair was found, and the hashed key</returns>
		std::tuple<Iterator, bool, size_t> Find(const _TypeKey& key);


		/// <summary>
		/// Finds a key/value pair inside the list const version
		/// </summary>
		/// <param name="key"> The key of the key/value pair that will be found</param>
		/// <returns> Returns a std::tuple that has an ConstIterator pointing to the found pair, and a bool that is true/false depending on if the pair was found, and the hashed key</returns>
		std::tuple<ConstIterator, bool, size_t> Find(const _TypeKey& key) const;

		/// <summary>
		/// Tries to remove a Key/Value Pair from the HashMap
		/// </summary>
		/// <param name="key"> The key assoicated with a Key/Value pair that will be removed</param>
		/// <returns> A bool returning true/false depeding on if the pair was removed or not</returns>
		bool Remove(const _TypeKey& key);

		/// <summary>
		/// Returns an Iterator at the start of the HashMap
		/// </summary>
		/// <returns>An Iterator at the start of the HashMap</returns>
		Iterator begin();

		/// <summary>
		/// Returns an Iterator past the end of the HashMap
		/// </summary>
		/// <returns>Returns an Iterator past the end of the HashMap</returns>
		Iterator end();

		/// <summary>
		/// Returns a ConstIterator from a const HashMap that points to the front of said HashMap
		/// </summary>
		/// <returns>A ConstIterator to the first valid value of the HashMap</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns a ConstIterator from a const HashMap that points past the end of said HashMap
		/// </summary>
		/// <returns>A ConstIterator that points past the end of the HashMap</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns a ConstIterator from a non const HashMap that points to the front of said HashMap
		/// </summary>
		/// <returns>A ConstIterator to the first valid value of the HashMap</returns>
		ConstIterator cbegin();

		/// <summary>
		/// Returns a ConstIterator from a non const HashMap that points past the end of said HashMap
		/// </summary>
		/// <returns>A ConstIterator that points past the end of the HashMap</returns>
		ConstIterator cend();


	};


	


}
#include "HashMap.inl"

