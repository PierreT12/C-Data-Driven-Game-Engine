namespace FieaGameEngine
{

	template <typename _Type>
	SList<_Type>::SList() :
		_size(0),
		_front(nullptr),
		_back(nullptr) {}


	template <typename _Type>
	SList<_Type>::SList(const SList& other)
	{
		Node* currentNode = other._front;

		_size = 0;

		while (currentNode != nullptr)
		{
			PushBack(currentNode->_Data);
			currentNode = currentNode->_Next;
		}

	}


	template<typename _Type>
	inline SList<_Type>::SList(SList&& rhs) noexcept:
		_size(rhs._size),
		_front(rhs._front),
		_back(rhs._back)
	{
		rhs._size = 0;
		rhs._front = nullptr;
		rhs._back = nullptr;

	}


	template<typename _Type>
	inline SList<_Type>& SList<_Type>::operator=(SList&& rhs) noexcept
	{
		_size = rhs._size;
		_front = rhs._front;
		_back = rhs._back;

		rhs._size = 0;
		rhs._front = nullptr;
		rhs._back = nullptr;

		return *this;
	}

	template <typename _Type>
	SList<_Type>::Node::Node(const _Type& _Data, Node* _Next) :
		_Data(_Data),
		_Next(_Next) {}


	template <typename _Type>
	SList<_Type> SList<_Type>::operator=(const SList& other)
	{
		if (this != &other)
		{
			ClearList();
			Node* currentNode = other._front;

			while (currentNode != nullptr)
			{
				PushBack(currentNode->_Data);
				currentNode = currentNode->_Next;
			}


		}

		return *this;
	}


	template<typename _Type>
	inline SList<_Type>::Iterator::Iterator(const SList& Owner, Node* Node) :
		_owner(&Owner),
		_node(Node)
	{}


	template<typename _Type>
	typename inline SList<_Type>::Iterator& SList<_Type>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		assert(_node);
		_node = _node->_Next;
		return *this;
	}

	template<typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::Iterator::operator++(int)
	{
		SList<_Type>::Iterator copy = *this;
		operator++();
		return copy;
	}

	
	template<typename _Type>
	inline bool SList<_Type>::Iterator::operator!=(const Iterator& other) const
	{
		if (this->_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		else if (&(this->_owner) != &(other._owner))
		{
			if (this->_node != other._node)
			{
				return true;
			}
		}
		return false;
	}

	template<typename _Type>
	inline bool SList<_Type>::Iterator::operator==(const Iterator& other) const
	{
		return !(operator!=(other));
	}

	template<typename _Type>
	inline _Type& SList<_Type>::Iterator::operator*() const
	{
		if (_node == nullptr)
		{
			throw std::runtime_error("Trying to dereference null :{");
		}
		return _node->_Data;
	}



	template<typename _Type>
	inline SList<_Type>::ConstIterator::ConstIterator(const SList& Owner, Node* Node) :
		_owner(&Owner),
		_node(Node)
	{}


	template<typename _Type>
	inline SList<_Type>::ConstIterator::ConstIterator(const Iterator& other):
		_owner(other._owner),
		_node(other._node) {}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator& SList<_Type>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}

		assert(_node);

		_node = _node->_Next;

		return *this;
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::ConstIterator::operator++(int)
	{
		SList<_Type>::ConstIterator copy = *this;

		operator++();

		return copy;
	}

	template<typename _Type>
	inline bool SList<_Type>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		if (this->_owner == nullptr)
		{
			throw std::runtime_error("This iterator has no container :{");
		}


		else if (&(this->_owner) != &(other._owner))
		{
			if (this->_node != other._node)
			{
				return true;
			}
		}
		return false;
	}

	template<typename _Type>
	inline bool SList<_Type>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(operator!=(other));
	}

	template<typename _Type>
	inline const _Type& SList<_Type>::ConstIterator::operator*() const
	{
		if (_node == nullptr)
		{
			throw std::runtime_error("Trying to dereference null :{");
		}
		return _node->_Data;
	}


	template <typename _Type>
	inline const _Type& SList<_Type>::Front() const
	{
		if (_front == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _front->_Data;
	}

	template <typename _Type>
	inline _Type& SList<_Type>::Front()
	{

		if (_front == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _front->_Data;


	}

	template <typename _Type>
	inline	const _Type& SList<_Type>::Back() const
	{
		if (_back == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _back->_Data;
	}

	template <typename _Type>
	inline _Type& SList<_Type>::Back()
	{
		if (_back == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _back->_Data;
	}


	template <typename _Type>
	inline typename  SList<_Type>::Iterator SList<_Type>::PushFront(const _Type& _Data)
	{
		_front = new Node(_Data, _front);		
		if (_size == 0)
		{	
			_back = _front;
		}		
		_size++;
		return Iterator{ *this, _front };
	}

	template <typename _Type>
	void SList<_Type>::PopFront()
	{
		if (_size > 0)
		{
			Node* temp = _front;
			_front = _front->_Next;

			delete temp;

			_size--;
		}

		else if (_size == 0)
		{
			_back = _front;
		}
	}

	template <typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::PushBack(const _Type& data)
	{
		Node* temp = new Node(data);
		if (_size == 0)
		{
			_back = temp;
			_front = _back;
		}
		else
		{
			_back->_Next = temp;
			_back = _back->_Next;
		}
		
		_size++;

		return Iterator{ *this, _back};
	}


	template<typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::PushBack(_Type&& data)
	{
		Node* temp = new Node(data);
		if (_size == 0)
		{
			_back = temp;
			_front = _back;
		}
		else
		{
			_back->_Next = temp;
			_back = _back->_Next;
		}

		_size++;

		

		return Iterator{ *this, _back };
	}

	
	template <typename _Type>
	void SList<_Type>::PopBack()
	{
		if (_size > 0)
		{
			Node* currentNode = _front;
			Node* previousNode = _front;

			while (currentNode->_Next != nullptr)
			{
				previousNode = currentNode;
				currentNode = currentNode->_Next;
			}

			Node* temp = _back;
			_back = previousNode;

			delete temp;
			_back->_Next = nullptr;

			_size--;
		}
		if (_size == 0)
		{
			_back = _front = nullptr;
		}
	}


	template<typename _Type>
	inline const std::size_t& SList<_Type>::Size() const
	{
		return _size;
	}


	template <typename _Type>
	inline const bool SList<_Type>::IsEmpty() const
	{
		return (_size == 0);
	}


	template <typename _Type>
	void SList<_Type>::ClearList()
	{
		Node* currentNode = _front;
		
		while (currentNode != nullptr)
		{
			Node* nextNode = currentNode->_Next;
			delete currentNode;
			currentNode = nextNode;
		}

		_size = 0;
		_back = _front = nullptr;
	}


	template <typename _Type>
	SList<_Type>::~SList()
	{
		if (_size > 0)
		{
			ClearList();
		}
		
	}


	


	template<typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::begin()
	{
		return  Iterator{ *this, _front };
	}

	template<typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::end()
	{
		return Iterator{ *this };
	}

	template<typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::validEnd()
	{
		return Iterator{*this, _back};
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::begin() const
	{
		return ConstIterator{ *this, _front };
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::end() const
	{
		return ConstIterator{ *this };
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::validEnd() const
	{
		return ConstIterator{ *this, _back };
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::cbegin() const
	{
		return ConstIterator{ *this, _front };
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::cend() const
	{
		return ConstIterator{ *this };
	}

	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::cvalidEnd() const
	{
		return ConstIterator{ *this, _back };
	}



	template<typename _Type>
	inline void SList<_Type>::InsertAfter(const Iterator& it, const _Type& data)
	{
		if (this != it._owner)
		{
			throw std::runtime_error("These Iterators refer to two different lists :{");
		}

		if (it._node == nullptr)
		{
			this->PushBack(data);
		}
		else
		{
			Node* insert = new Node(data);
			Node* next = it._node->_Next;

			it._node->_Next = insert;
			insert->_Next = next;

			if (next == nullptr)
			{
				_back = insert;
			}


			_size++;
		}
		

	}

	template<typename _Type>
	typename inline SList<_Type>::Iterator SList<_Type>::Find(const _Type& data, std::function<bool(const _Type&, const _Type&)> equalityFunctior)
	{
		Iterator it;
		for (it = this->begin(); it != (this->end()); ++it)
		{
			if (equalityFunctior(*it, data))
			{
				break;
			}
		}
		return it;
	}


	template<typename _Type>
	typename inline SList<_Type>::ConstIterator SList<_Type>::Find(const _Type& data, std::function<bool(const _Type&, const _Type&)> equalityFunctior) const
	{
		ConstIterator it;
		for (it = this->begin(); it != this->end(); ++it)
		{
			if (equalityFunctior(*it, data))
			{
				break;
			}
		}
		return it;
	}

	template<typename _Type>
	inline void SList<_Type>::Remove(const _Type& data)
	{
		if (_front != nullptr)
		{
			Iterator it = this->Find(data);
			Node* previous = _front;
			Node* next = it._node->_Next;

			for (Iterator finder = this->begin(); finder != it; ++finder)
			{
				previous = finder._node;
			}


			delete it._node;

			if (_size == 1)
			{
				_back = _front = nullptr;
			}
			else
			{
				
				previous->_Next = next;
			}

			

			_size--;
		}
		
	}





}