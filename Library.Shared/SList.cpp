#include "pch.h"
#include "SList.h"
#include <stdexcept>

namespace FieaGameEngine
{


	SList::SList():
	_size(0),
	_front(nullptr),
	_back(nullptr){}

	const int32_t& SList::Front() const
	{
		if (_front == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _front->Data;
	}

	int32_t& SList::Front()
	{

		if (_front == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _front->Data;

		
	}


	const int32_t& SList::Back() const
	{
		if (_back == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _back->Data;
	}

	int32_t& SList::Back()
	{
		if (_back == nullptr)
		{
			throw std::runtime_error("Trying to return a null :{");
		}
		return _back->Data;
	}


	//Works!! Look over again in the morn
	void SList::PushFront(int32_t& data)
	{
		//Heap Allocation
		Node* next = nullptr;

		if (_size == 0)
		{
			_front = new Node();
			_front->Data = data;
			_front->Next = next;
			_back = _front;
		}
		else
		{
		
			//Moves Front to the Second Node, and sets front to new values
			//This is probably a copy, fix this later
			next = new Node();

			next->Data = data;

			//The next of the next node will be what front is right now
			next->Next = _front;


			//the new first node is now next, so basically a swap
			_front = next;
			
		}

		_size++;

	}

	//Works!!
	void SList::PopFront()
	{

		if (DeleteFront() == true)
		{
			return;
		}
		Node* holder = _front;

		_front = _front->Next;

		delete holder;

		_size--;

	}

	//Works in constatnt time!!
	void SList::PushBack(int32_t& data)
	{
		//Heap Allocation
		Node* next = nullptr;

		if (_size == 0)
		{
			_back = new Node();
			_back->Data = data;
			_back->Next = next;
			_front = _back;
		}
		else
		{

			//Moves Front to the Second Node, and sets front to new values
			//This is probably a copy, fix this later
			next = new Node();

			next->Data = data;

			
			next->Next = nullptr;

			_back->Next = next;

			_back = next;
			_back->Next = nullptr;

		}

		_size++;
	}

	//Works!!
	void SList::PopBack()
	{

		if (DeleteFront() == true)
		{
			return;
		}

		Node* current = _front;
		Node* next = _front->Next;

		LoopToRemove(current, next);


		Node* holder = _back;
		_back = current;

		delete holder;
		_back->Next = nullptr;
		_size--;
	}


	const std::size_t& SList::Size() const
	{
		return _size;
	}

	std::size_t& SList::Size()
	{
		return _size;
	}

	const bool SList::IsEmpty() const
	{
		//Checking to see if the list is empty or not
		if (_size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool SList::IsEmpty()
	{
		if (_size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SList::ClearList()
	{
		if (DeleteFront() == true)
		{
			return;
		}


		Node* current = _front;
		Node* next = _front->Next;

		LoopToRemove(current, next);


		DeleteCurrent(current, next);	
		
	}

	SList::SList(const SList& other)
	{
		const SList* otherptr = &other;
		if (this == otherptr)
		{
			throw std::runtime_error("These two lists are the same.");
		}
		if (other.Size() == 0)
		{
			throw std::runtime_error("The list you are trying to copy from has no data. Don't do that");
		}


		_front = new Node();
		_back = new Node();

		//Copying the front and back over
		memcpy(_front, other._front, sizeof(Node*));


		Node* currentNode = new Node();
		Node* currentOurNode = new Node();

		currentNode = other._front->Next;

		_front->Next = new Node();
		currentOurNode = _front->Next;


		//nextNode = other._front->Next->Next;
		while (currentNode != nullptr)
		{
			if (currentNode->Next == nullptr)
			{
				_back = currentOurNode;
				_back->Next = nullptr;
			}
			else
			{
				currentOurNode->Next = new Node();
			}

			memcpy(currentOurNode, currentNode, sizeof(Node*));

			currentNode = currentNode->Next;

			currentOurNode = currentOurNode->Next;
		}
		_size = other._size;


	}

	SList SList::operator=(const SList& other)
	{
		const SList* otherptr = &other;

		if (this == otherptr)
		{
			throw std::runtime_error("These two lists are the same.");
		}
		if (_size != 0)
		{
			ClearList();
		}
		if (other.Size() == 0)
		{
			throw std::runtime_error("The list you are trying to copy from has no data. Don't do that");
		}

		//Need to check to see if the front and back are null
		_front = new Node();
		_back = new Node();

		//Copying the front and back over
		memcpy(_front, other._front, sizeof(Node*));


		Node* currentNode = new Node();
		Node* currentOurNode = new Node();

		currentNode = other._front->Next;

		_front->Next = new Node();
		currentOurNode = _front->Next;
			
		while (currentNode != nullptr)
		{
			if (currentNode->Next == nullptr)
			{
				_back = currentOurNode;
				_back->Next = nullptr;
			}
			else
			{
				currentOurNode->Next = new Node();
			}

			memcpy(currentOurNode, currentNode, sizeof(Node*));

			currentNode = currentNode->Next;
			
			currentOurNode = currentOurNode->Next;




		}


		_size = other._size;



		return *this;
	}


	SList::~SList()
	{
		if (_front == nullptr || _front->Next == nullptr)
		{
			delete _front;
			_size = 0;
			return;
		}
		
		Node* current = _front;
		Node* next = _front->Next;

		LoopToRemove(current, next);


		DeleteCurrent(current, next);


	}



	//Private Methods that just help out

	void SList::LoopToRemove(Node* current, Node* next)
	{

		while (next->Next != nullptr)
		{
			current = next;
			next = next->Next;
			delete current;
			_size--;

		}
	}

	bool SList::DeleteFront()
	{
		if (_back == nullptr || _front == nullptr)
		{
			throw std::runtime_error("This list has no data in it :{");
		}

		if (_front->Next == nullptr)
		{
			delete _front;
			_front = nullptr;
			_back = nullptr;
			_size--;
			return true;
		}

		return false;
	}

	void SList::DeleteCurrent(Node* current, Node* next)
	{

		if (_size > 0)
		{
			delete current;
			_size = 0;
		}

		delete next;
		_front = nullptr;
		_back = nullptr;
	}



}

