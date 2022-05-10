namespace FieaGameEngine
{



	template <typename _TypeKey, typename _TypeData>
	HashMap<_TypeKey, _TypeData>::HashMap(size_t buckets, std::function<size_t(const _TypeKey&)> hashFunctor, std::function<size_t(const _TypeKey&, const _TypeKey&)> equalityFunctor):
		_bucket{buckets},
		_hashFunctor{ hashFunctor },
		_size{ 0 },
		_equalityFunctor{ equalityFunctor }
	{
		if (buckets < 2)
		{
			throw std::runtime_error("Bucket size is too small, it must be greater than 2 :{");
		}

		_bucket.Resize(buckets);

		_emptyBucket = buckets;
	}



	template<typename _TypeKey, typename _TypeData>
	inline size_t HashMap<_TypeKey, _TypeData>::Mod(const size_t hash) const
	{
		return hash % _bucket.Size();
	}


	template<typename _TypeKey, typename _TypeData>
	inline size_t HashMap<_TypeKey, _TypeData>::HashMod(const _TypeKey& key) const
	{
		return Mod(_hashFunctor(key));
	}

	template<typename _TypeKey, typename _TypeData>
	inline HashMap<_TypeKey, _TypeData>::HashMap(const HashMap& other):
		_bucket{other._bucket},
		_emptyBucket{ other._emptyBucket },
		_size{ other._size },
		_hashFunctor{ other._hashFunctor },
		_equalityFunctor{other._equalityFunctor }	{}



	template<typename _TypeKey, typename _TypeData>
	inline HashMap<_TypeKey, _TypeData>::HashMap(HashMap&& rhs) noexcept:
		_emptyBucket{ rhs._emptyBucket},
		_size{ rhs._size}
	{
		_bucket = std::move(rhs._bucket);

		rhs._emptyBucket = 0;
		rhs._size = 0;

	}

	template<typename _TypeKey, typename _TypeData>
	inline HashMap<_TypeKey, _TypeData>& HashMap<_TypeKey, _TypeData>::operator=(HashMap&& rhs) noexcept
	{
		_bucket = std::move(rhs._bucket);
		_emptyBucket = rhs._emptyBucket;
		_size = rhs._size;

		rhs._emptyBucket = 0;
		rhs._size = 0;

		return *this;
	}

	template<typename _TypeKey, typename _TypeData>
	inline float HashMap<_TypeKey, _TypeData>::GetLoadFactor() const
	{
		return _size / static_cast<float>(_bucket.Size());
	}

	template<typename _TypeKey, typename _TypeData>
	inline size_t HashMap<_TypeKey, _TypeData>::GetEmptyBuckets() const
	{
		return _emptyBucket;
	}

	template<typename _TypeKey, typename _TypeData>
	inline size_t HashMap<_TypeKey, _TypeData>::GetBuckets() const
	{
		return _bucket.Size();
	}

	template <typename _TypeKey, typename _TypeData>
	size_t HashMap<_TypeKey, _TypeData>::Size() const
	{
		return _size;
	}

	template<typename _TypeKey, typename _TypeData>
	inline _TypeData& HashMap<_TypeKey, _TypeData>::At(const _TypeKey& key)
	{
		if (_bucket.Size() == 0)
		{
			throw std::runtime_error("This list is empty :{");
		}

		auto [it, found, index] = Find(key);

		if (!found)
		{
			throw std::runtime_error("Unable to return value :{");
		}

		return (*it).second;
	}

	template<typename _TypeKey, typename _TypeData>
	inline const _TypeData& HashMap<_TypeKey, _TypeData>::At(const _TypeKey& key) const
	{

		if (_bucket.Size() == 0)
		{
			throw std::runtime_error("This list is empty :{");
		}

		auto [it, found, index] = Find(key);

		if (!found)
		{
			throw std::runtime_error("Unable to return value :{");
		}

		return (*it).second;
	}

	template<typename _TypeKey, typename _TypeData>
	inline _TypeData HashMap<_TypeKey, _TypeData>::operator[](const _TypeKey& key)
	{

		auto temp = Insert({ key,  _TypeData() });

		return (temp.first)->second;

	}

	template<typename _TypeKey, typename _TypeData>
	inline bool HashMap<_TypeKey, _TypeData>::IsEmpty() const
	{
		return (_size == 0);
	}

	template<typename _TypeKey, typename _TypeData>
	inline std::pair<typename HashMap<_TypeKey, _TypeData>::Iterator, bool> HashMap<_TypeKey, _TypeData>::ContainsKey(const _TypeKey& key)
	{
		auto [it, found, index] = Find(key);

		return {it, found};
	}

	template<typename _TypeKey, typename _TypeData>
	inline std::pair<typename HashMap<_TypeKey, _TypeData>::ConstIterator, bool> HashMap<_TypeKey, _TypeData>::ContainsKey(const _TypeKey& key) const
	{
		auto [it, found, index] = Find(key);

		return { it, found };
	}

	template<typename _TypeKey, typename _TypeData>
	inline std::pair<typename HashMap<_TypeKey, _TypeData>::Iterator, bool> HashMap<_TypeKey, _TypeData>::Insert(const PairType& pair)
	{
		auto [it, found, index] = Find(pair.first);

		if (found)
		{
			return { it, found };
		}

		
		_bucket[index].PushBack(std::move(pair));

		_emptyBucket -= 1;

		++_size;

		return { { *this, index, _bucket[index].begin() }, found };
	}


	//Fix this in a second
	template<typename _TypeKey, typename _TypeData>
	inline std::pair<typename HashMap<_TypeKey, _TypeData>::Iterator, bool> HashMap<_TypeKey, _TypeData>::Insert(PairType&& pair)
	{
		auto [it, found, index] = Find(pair.first);

		if (found)
		{
			return { it, found };
		}


		_bucket[index].PushBack(pair);

		_emptyBucket -= 1;

		++_size;

		return { { *this, index, _bucket[index].validEnd() }, found };
	}


	template<typename _TypeKey, typename _TypeData>
	inline void HashMap<_TypeKey, _TypeData>::ClearList()
	{
		_emptyBucket = _bucket.Size();

		for (auto& chain : _bucket)
		{
			chain.ClearList();
		}
		_size = 0;
	}

	template<typename _TypeKey, typename _TypeData>
	inline HashMap<_TypeKey, _TypeData>& HashMap<_TypeKey, _TypeData>::Resize(const size_t newSize)
	{
		HashMap<_TypeKey, _TypeData> temp(newSize, _hashFunctor, _equalityFunctor);
		
		for (auto& value : *this)
		{
			temp.Insert(value);
		}

		*this = std::move(temp);

		return *this;
	}

	template<typename _TypeKey, typename _TypeData>
	inline HashMap<_TypeKey, _TypeData>& HashMap<_TypeKey, _TypeData>::Rehash(std::function<size_t(const _TypeKey&)> hashFunctor)
	{
		HashMap<_TypeKey, _TypeData> temp(_bucket.Size(), hashFunctor, _equalityFunctor);

		for (auto& value : *this)
		{
			temp.Insert(value);
		}

		*this = std::move(temp);

		return *this;
	}


	template <typename _TypeKey, typename _TypeData>
	HashMap<_TypeKey, _TypeData>::Iterator::Iterator(HashMap& Owner, const size_t& BucketIndex, typename SList<std::pair<const  _TypeKey, _TypeData>>::Iterator iterator):
		_owner{ &Owner },
		_bucketIndex{ BucketIndex },
		_chainIterator{ iterator }{}


	template <typename _TypeKey, typename _TypeData>
	HashMap<_TypeKey, _TypeData>::Iterator::Iterator(const Iterator& other) :
		_owner{ other._owner },
		_bucketIndex{ other._bucketIndex },
		_chainIterator{ other._chainIterator }{}


	template <typename _TypeKey, typename _TypeData>
	HashMap<_TypeKey, _TypeData>::ConstIterator::ConstIterator(const HashMap& Owner, const size_t& BucketIndex, typename SList<std::pair<const _TypeKey, _TypeData>>::ConstIterator iterator) :
		_owner{ &Owner },
		_bucketIndex{ BucketIndex },
		_chainIterator{ iterator }{}


	template <typename _TypeKey, typename _TypeData>
	HashMap<_TypeKey, _TypeData>::ConstIterator::ConstIterator(const Iterator& other) :
		_owner{ other._owner },
		_bucketIndex{ other._bucketIndex },
		_chainIterator{ other._chainIterator }{}

	template <typename _TypeKey, typename _TypeData>
	HashMap<_TypeKey, _TypeData>::ConstIterator::ConstIterator(const ConstIterator& other):
		_owner{ other._owner },
		_bucketIndex{ other._bucketIndex },
		_chainIterator{ other._chainIterator }{}


	


	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::Iterator HashMap<_TypeKey, _TypeData>::Iterator::operator=(const Iterator& other)
	{
		_owner = other._owner;
		_bucketIndex = other._bucketIndex;
		_chainIterator = other._chainIterator;

		return *this;
	}


	template <typename _TypeKey, typename _TypeData>
	std::pair<const _TypeKey, _TypeData>& HashMap<_TypeKey, _TypeData>::Iterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		if (_bucketIndex > _owner->_bucket.Size() || _chainIterator == _owner->_bucket[_bucketIndex].end())
		{
			throw std::runtime_error("Trying to dereference null :{");
		}

		return *_chainIterator;
	}

	template<typename _TypeKey, typename _TypeData>
	inline std::pair<const _TypeKey, _TypeData>* HashMap<_TypeKey, _TypeData>::Iterator::operator->() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		if (_bucketIndex > _owner->_bucket.Size() || _chainIterator == _owner->_bucket[_bucketIndex].end())
		{
			throw std::runtime_error("Trying to dereference null :{");
		}

		return &(*_chainIterator);
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::Iterator& HashMap<_TypeKey, _TypeData>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}
			++_chainIterator;
			while (_chainIterator == _owner->_bucket[_bucketIndex].end())
			{
				++_bucketIndex;
				if (_bucketIndex >= _owner->_bucket.Size())
				{
					_chainIterator = _owner->_bucket[_bucketIndex - 1].end();
					break;
				}

				_chainIterator = _owner->_bucket[_bucketIndex].begin();
			}


		return *this;
	}


	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::Iterator HashMap<_TypeKey, _TypeData>::Iterator::operator++(int)
	{
		Iterator copy = *this;
		operator++();
		return copy;
	}

	template <typename _TypeKey, typename _TypeData>
	bool HashMap<_TypeKey, _TypeData>::Iterator::operator!=(const Iterator& other) const
	{
		return(_owner != other._owner || _bucketIndex != other._bucketIndex || _chainIterator != other._chainIterator);
	}


	template <typename _TypeKey, typename _TypeData>
	bool HashMap<_TypeKey, _TypeData>::Iterator::operator==(const Iterator& other) const
	{
		return(!(operator!=(other)));
	}




	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator HashMap<_TypeKey, _TypeData>::ConstIterator::operator=(const ConstIterator& other)
	{
		_owner = other._owner;
		_bucketIndex = other._bucketIndex;
		_chainIterator = other._chainIterator;

		return *this;
	}


	template <typename _TypeKey, typename _TypeData>
	inline const std::pair<const _TypeKey, _TypeData>& HashMap<_TypeKey, _TypeData>::ConstIterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		
		if (_bucketIndex > _owner->_bucket.Size() || _chainIterator == _owner->_bucket[_bucketIndex].end())
		{
			throw std::runtime_error("Trying to dereference null :{");
		}

		return *_chainIterator;
	}

	template<typename _TypeKey, typename _TypeData>
	inline const std::pair<const _TypeKey, _TypeData>* HashMap<_TypeKey, _TypeData>::ConstIterator::operator->() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		if (_bucketIndex > _owner->_bucket.Size() || _chainIterator == _owner->_bucket[_bucketIndex].end())
		{
			throw std::runtime_error("Trying to dereference null :{");
		}

		return &(*_chainIterator);
	}


	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator& HashMap<_TypeKey, _TypeData>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}
		++_chainIterator;
		while (_chainIterator == _owner->_bucket[_bucketIndex].end())
		{
			++_bucketIndex;
			if (_bucketIndex >= _owner->_bucket.Size())
			{
				_chainIterator = _owner->_bucket[_bucketIndex - 1].end();
				break;
			}

			_chainIterator = _owner->_bucket[_bucketIndex].begin();
		}

		return *this;
	}


	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator HashMap<_TypeKey, _TypeData>::ConstIterator::operator++(int)
	{
		ConstIterator copy = *this;
		operator++();
		return copy;
	}

	template <typename _TypeKey, typename _TypeData>
	bool HashMap<_TypeKey, _TypeData>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return(_owner != other._owner || _bucketIndex != other._bucketIndex || _chainIterator != other._chainIterator);
	}


	template <typename _TypeKey, typename _TypeData>
	bool HashMap<_TypeKey, _TypeData>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return(!(operator!=(other)));
	}


	template<typename _TypeKey, typename _TypeData>
	 inline std::tuple< typename HashMap<_TypeKey, _TypeData>::Iterator, bool, size_t>  HashMap<_TypeKey, _TypeData>::Find(const _TypeKey& key)
	{
		bool found = false;


		size_t index = HashMod(key);

		auto sListIterator = _bucket[index].begin();

		for (; sListIterator != _bucket[index].end(); ++sListIterator)
		{

			if (_equalityFunctor(key, (*sListIterator).first))
			{
				found = true;
				break;
			}
		}
		
		
		return { Iterator{*this, index, sListIterator}, found, index };
	}

	 template<typename _TypeKey, typename _TypeData>
	 inline std::tuple<typename HashMap<_TypeKey, _TypeData>::ConstIterator, bool, size_t> HashMap<_TypeKey, _TypeData>::Find(const _TypeKey& key) const
	 {
		 bool found = false;

		 size_t index = HashMod(key);

		 auto sListIterator = _bucket[index].begin();

		 for (; sListIterator != _bucket[index].end(); ++sListIterator)
		 {

			 if (_equalityFunctor(key, (*sListIterator).first))
			 {
				 found = true;
				 break;
			 }
		 }

		 return { ConstIterator{*this, index, sListIterator}, found, index };
	 }


	template<typename _TypeKey, typename _TypeData>
	inline bool HashMap<_TypeKey, _TypeData>::Remove(const _TypeKey& key)
	{
		bool removed = false;

		auto [it, found, index] = Find(key);

		if (found)
		{
			_bucket[index].Remove(*it);

			removed = true;

			--_size;
		}

		return removed;
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::Iterator HashMap<_TypeKey, _TypeData>::begin()
	{
		std::pair<size_t, typename SList<PairType>::Iterator> temp = FindFirstValue();

		return Iterator{ *this, temp.first, temp.second };
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::Iterator HashMap<_TypeKey, _TypeData>::end()
	{
		return Iterator{ *this, _bucket.Size() , _bucket[_bucket.Size() - 1].end() };
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator HashMap<_TypeKey, _TypeData>::begin() const
	{
		std::pair<size_t, typename SList<PairType>::ConstIterator> temp = FindFirstValue();

		return ConstIterator{ *this, temp.first, temp.second };
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator HashMap<_TypeKey, _TypeData>::end() const
	{
		return ConstIterator{ *this, _bucket.Size() , _bucket[_bucket.Size() - 1].end() };
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator HashMap<_TypeKey, _TypeData>::cbegin()
	{
		std::pair<size_t, typename SList<PairType>::ConstIterator> temp = FindFirstValue();

		return ConstIterator{ *this, temp.first, temp.second };
	}

	template <typename _TypeKey, typename _TypeData>
	typename inline HashMap<_TypeKey, _TypeData>::ConstIterator HashMap<_TypeKey, _TypeData>::cend()
	{
		return ConstIterator{ *this, _bucket.Size() , _bucket[_bucket.Size() - 1].end() };
	}


	template<typename _TypeKey, typename _TypeData>
	inline std::pair<size_t, typename SList<std::pair<const _TypeKey, _TypeData>>::Iterator> HashMap<_TypeKey, _TypeData>::FindFirstValue()
	{
		std::pair<size_t, typename SList<PairType>::Iterator> first = { _bucket.Size() , _bucket[_bucket.Size() - 1].end() };
		for (size_t i = 0; i < _bucket.Size(); ++i)
		{
			if (_bucket[i].Size() > 0)
			{
				auto it = _bucket[i].begin();
				first = { i, it };
				break;
			}
		}
		return first;
	}

	template<typename _TypeKey, typename _TypeData>
	inline std::pair<size_t, typename SList<std::pair<const _TypeKey, _TypeData>>::ConstIterator> HashMap<_TypeKey, _TypeData>::FindFirstValue() const
	{
		std::pair<size_t, typename SList<PairType>::ConstIterator> first = { _bucket.Size() , _bucket[_bucket.Size() - 1].cend() };
		for (size_t i = 0; i < _bucket.Size(); ++i)
		{
			if (_bucket[i].Size() > 0)
			{
				auto it = _bucket[i].cbegin();
				first = { i, it };
				break;
			}
		}

		return first;
	}

}

