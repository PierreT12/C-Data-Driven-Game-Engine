namespace FieaGameEngine
{
	template<typename _Type>
	inline Vector<_Type>::Vector(size_t capacity):
		_front{ nullptr },
		_size{ 0 },
		_capacity{ capacity }

	{
		_front = reinterpret_cast<_Type*>(malloc((_capacity * (sizeof(_Type)))));


	}


	template<typename _Type>
	inline Vector<_Type>::Vector(std::initializer_list<_Type> list, size_t capacity):
		Vector<_Type>(capacity)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			PushBack(*it);
		}

	}

	template<typename _Type>
	inline Vector<_Type>::~Vector()
	{
		if (this != nullptr)
		{
			ClearList();

			free(_front);
		}
	}

	template<typename _Type>
	Vector<_Type>::Vector(const Vector& other):
		_capacity{ other._capacity }
	{
		_front = reinterpret_cast<_Type*>(malloc((_capacity * (sizeof(_Type)))));

		_size = 0;
		while (_size != other._size)
		{
			size_t value = _size;

			PushBack(other.At(value));
		}
	}

	template<typename _Type>
	Vector<_Type>::Vector(Vector&& rhs) noexcept :
		_capacity{ rhs._capacity },
		_size{ rhs._size },
		_front{ rhs._front }
	{
		rhs._front = nullptr;
		rhs._capacity = 0;
		rhs._size = 0;
	}

	template<typename _Type>
	Vector<_Type>& Vector<_Type>::operator=(const Vector& other)
	{
		if (this != &other)
		{
			ClearList();

			Reserve(other._capacity);

			while (_size != other._size)
			{
				size_t value = _size;

				PushBack(other.At(value));
			}
		}
		return *this;
	}

	template<typename _Type>
	Vector<_Type>& Vector<_Type>::operator=(Vector&& rhs)  noexcept
	{
		
		this->~Vector();
		_capacity = rhs._capacity;
		_size = rhs._size;
		_front = rhs._front;

		rhs._front = nullptr;
		rhs._capacity = 0;
		rhs._size = 0;
		
		return *this;
	}


	template <typename _Type>
	void Vector<_Type>::PushBack(const _Type& data)
	{

		if (_size == (_capacity - 1))
		{
			Reserve((_capacity + 3));
		}
		_Type* temp = (_front + _size);

		temp = new (_front + _size) _Type(data);
		
		++_size;
	}

	template<typename _Type>
	inline void Vector<_Type>::PopBack()
	{
		if (_size > 0)
		{
			_Type* temp = _front + (_size - 1);

			temp->~_Type();
			_size--;
		}
		
	}

	template<typename _Type>
	_Type& Vector<_Type>::At(size_type index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("index is larger than list.");
		}

		_Type* temp = (_front + index);

		return *temp;
	}

	template<typename _Type>
	const _Type& Vector<_Type>::At(size_type index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("index is larger than list.");
		}

		_Type* temp = (_front + index);


		return *temp;
	}
	
	template<typename _Type>
	inline _Type& Vector<_Type>::operator[](size_type index)
	{
		return At(index);
	}
	
	template<typename _Type>
	inline const _Type& Vector<_Type>::operator[](size_type index) const
	{
		return At(index);
	}



	template <typename _Type>
	bool Vector<_Type>::IsEmpty() const
	{
		return (_size == 0);
	}


	template <typename _Type>
	size_t Vector<_Type>::Size() const
	{
		return _size;
	}


	template <typename _Type>
	size_t Vector<_Type>::Capacity() const
	{
		return _capacity;
	}

	template<typename _Type>
	inline void Vector<_Type>::Reserve(size_type newCapacity)
	{
		if(newCapacity > _capacity && _capacity != 0)
		{
			_Type* reallocate;
			reallocate = reinterpret_cast<_Type*>(realloc(_front, (newCapacity * (sizeof(_Type)))));
			_front = reallocate;

			_capacity = newCapacity;

		}
	}

	template<typename _Type>
	inline void Vector<_Type>::ClearList()
	{
		while (_size > 0)
		{
			_Type* temp = _front + (_size - 1);

			temp->~_Type();
			_size--;
		}

	}

	template<typename _Type>
	inline void Vector<_Type>::Resize(const size_t size)
	{
		ClearList();
		
		Reserve(size);

		for (size_t i = 0; i < size; ++i)
		{
			_Type* temp = (_front + _size);
			
			temp = new (_front + _size)_Type();
			
			_size++;
		}

		


	}


	template <typename _Type>
	_Type& Vector<_Type>::Front()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Trying to return a null :{");
		}

		return *_front;
	}


	template <typename _Type>
	const _Type& Vector<_Type>::Front() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Trying to return a null :{");
		}

		return *_front;
	}

	template<typename _Type>
	inline _Type& Vector<_Type>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Trying to return a null :{");
		}

		return *(_front + _size - 1);
	}

	template<typename _Type>
	inline const _Type& Vector<_Type>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Trying to return a null :{");
		}

		return *(_front + _size - 1);
	}



	template<typename _Type>
	inline Vector<_Type>::Iterator::Iterator(Vector& Owner, size_type Index) :
		_owner(&Owner),
		_index(Index)
	{}


	template<typename _Type>
	inline Vector<_Type>::Iterator::Iterator(const Iterator& other):
		_owner{other._owner},
		_index{other._index}
	{}
	
	template<typename _Type>
	typename inline Vector<_Type>::Iterator& Vector<_Type>::Iterator::operator=(const Iterator& other)
	{
		_owner = other._owner;
		_index = other._index;

		return *this;
	}

	template<typename _Type>
	typename inline Vector<_Type>::Iterator& Vector<_Type>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		assert((_index < _owner->_size));

		++_index;

		return *this;
	}

	template<typename _Type>
	typename inline Vector<_Type>::Iterator Vector<_Type>::Iterator::operator++(int)
	{
		Vector<_Type>::Iterator copy = *this;
		operator++();
		return copy;
	}

	template<typename _Type>
	inline bool Vector<_Type>::Iterator::operator==(const Iterator& other) const
	{
		return((_owner == other._owner && _index == other._index));
	}

	template<typename _Type>
	inline bool Vector<_Type>::Iterator::operator!=(const Iterator& other) const
	{
		return(!(operator==(other)));
	}

	template<typename _Type>
	inline _Type& Vector<_Type>::Iterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		if (_index >= _owner->_size)
		{
			throw std::out_of_range("Index is not in range.");
		}


		return _owner->At(_index);
	}


	template<typename _Type>
	inline Vector<_Type>::ConstIterator::ConstIterator(const Vector& Owner, size_type Index) :
		_owner(&Owner),
		_index(Index)
	{}


	template<typename _Type>
	inline Vector<_Type>::ConstIterator::ConstIterator(const Iterator& other) :
		_owner(other._owner),
		_index(other._index)
	{}

	template<typename _Type>
	inline Vector<_Type>::ConstIterator::ConstIterator(const ConstIterator& other) :
		_owner{ other._owner },
		_index{ other._index }
	{}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator& Vector<_Type>::ConstIterator::operator=(const ConstIterator& other)
	{
		_owner = other._owner;
		_index = other._index;

		return *this;
	}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator& Vector<_Type >::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		assert((_index < _owner->_size));

		++_index;

		return *this;
	}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator Vector<_Type>::ConstIterator::operator++(int)
	{
		Vector<_Type>::ConstIterator copy = *this;
		operator++();
		return copy;
	}

	template<typename _Type>
	inline bool Vector<_Type>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return((_owner == other._owner && _index == other._index));
	}

	template<typename _Type>
	inline bool Vector<_Type>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return(!(operator==(other)));
	}

	template<typename _Type>
	inline const _Type& Vector<_Type>::ConstIterator::operator*() const
	{
		if (_index >= _owner->_size)
		{
			throw std::out_of_range("Index is not in range.");
		}
	
		return _owner->At(_index);
	}


	template<typename _Type>
	typename inline Vector<_Type>::Iterator Vector<_Type>::Find(const _Type& data, std::function<bool(const _Type&, const _Type&)> equalityFunctor)
	{
		Iterator it;
		for (it = begin(); it != (end()); ++it)
		{
			if (equalityFunctor(*it, data))
			{
				
				break;
			}
		}

		return it;
	}

	template<typename _Type>
	typename inline Vector<_Type >::ConstIterator Vector<_Type>::Find(const _Type& data, std::function<bool(const _Type&, const _Type&)> equalityFunctor) const
	{
		ConstIterator it;

		for (it = begin(); it != (end()); ++it)
		{
			if (equalityFunctor(*it, data))
			{
				
				break;
			}
		}


		return it;
	}

	template<typename _Type>
	bool Vector<_Type>::Remove(const Iterator& it)
	{
		if (this != it._owner)
		{
			throw std::runtime_error("This owning container is not the same.");
		}
	
		_Type* temp = (_front + it._index);

		temp->~_Type();

		--_size;
		

		memmove((_front + it._index), (_front + it._index + 1), (sizeof(_Type) * (_size - it._index) ));
		
		return true;
	}

	template<typename _Type>
	bool Vector<_Type>::Remove(const _Type& value)
	{

		auto it = Find(value);

		if (this != it._owner)
		{
			throw std::runtime_error("This owning container is not the same.");
		}

		if (it == end())
		{
			return false;
		}

		_Type* temp = (_front + it._index);

		temp->~_Type();

		--_size;


		memmove((_front + it._index), (_front + it._index + 1), (sizeof(_Type) * (_size - it._index)));

		return true;
	}

	template<typename _Type>
	typename inline Vector<_Type>::Iterator Vector<_Type>::begin()
	{
		return Iterator{ *this, 0 };
	}

	template<typename _Type>
	typename inline Vector<_Type>::Iterator Vector<_Type>::end()
	{
		return Iterator{ *this, _size };
	}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator Vector<_Type>::begin() const
	{


		return ConstIterator{ *this , 0};
	}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator Vector<_Type>::end() const
	{

		return ConstIterator{ *this, _size };
	}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator Vector<_Type>::cbegin() const
	{

		return ConstIterator{ *this, 0 };
	}

	template<typename _Type>
	typename inline Vector<_Type>::ConstIterator Vector<_Type>::cend() const
	{
		return ConstIterator{  *this, _size };
	}





}