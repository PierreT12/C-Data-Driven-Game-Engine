#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Scope)

	Scope::Scope(Scope* parent, size_t capacity):
		_parent{parent},
		_orderInterted{capacity},
		_pairs{10, DefaultHash<std::string>()} {}

	Scope::~Scope()
	{	
		ClearList();
	}

	Scope::Scope(const Scope& other)
	{
		Vector<HashMapType>::ConstIterator otherit = other._orderInterted.begin();

		for (; otherit != other._orderInterted.end(); ++otherit)
		{
			std::string otherStr = (*otherit)->first;
			Datum otherDatum = (*otherit)->second;
			if (otherDatum.Type() == DatumTypes::TABLE)
			{
				for (size_t i = 0; i < otherDatum.Size(); ++i)
				{
					Scope* scopeTemp = otherDatum.Get<Scope>(i).Clone();
					Adopt(otherStr, *scopeTemp);

				}
			}
			else
			{
				auto [it, intsert] = _pairs.Insert(*(*otherit));
				_orderInterted.PushBack(&(*it));
			}
		}
	}

	Scope::Scope(Scope&& rhs):
		_parent{rhs._parent}
	{
		Vector<HashMapType>::Iterator rhsit = rhs._orderInterted.begin();
		for (; rhsit != rhs._orderInterted.end(); ++rhsit)
		{
			std::string otherStr = (*rhsit)->first;
			Datum otherDatum = (*rhsit)->second;

			if (otherDatum.Type() == DatumTypes::TABLE)
			{
				for (size_t i = 0; i < otherDatum.Size(); ++i)
				{
					Adopt(otherStr, otherDatum.Get<Scope>(i));
				}
			}
			else
			{
				auto [it, intsert] = _pairs.Insert(std::move(*(*rhsit)));
				_orderInterted.PushBack(&(*it));
			}
		}
		if (_parent != nullptr)
		{
			Vector<HashMapType>::Iterator parentIt = _parent->_orderInterted.begin();
			for (; parentIt != _parent->_orderInterted.end(); ++parentIt)
			{
				std::string otherStr = (*parentIt)->first;
				Datum otherDatum = (*parentIt)->second;
				if (otherDatum.Type() == DatumTypes::TABLE)
				{
					auto [index, found ] = otherDatum.Find(rhs);
					if (found)
					{
				
						otherDatum.Set(*this, index);
					}
				}
			}
		}

		rhs._parent = nullptr;
		rhs._pairs.ClearList();
		rhs._orderInterted.ClearList();
		rhs.ClearList();
	}

	Scope& Scope::operator=(const Scope& other)
	{
		if (this != &other)
		{
			ClearList();

			Vector<HashMapType>::ConstIterator otherit = other._orderInterted.begin();
			for (; otherit != other._orderInterted.end(); ++otherit)
			{
				std::string otherStr = (*otherit)->first;
				Datum otherDatum = (*otherit)->second;

				if (otherDatum.Type() == DatumTypes::TABLE)
				{
					for (size_t i = 0; i < otherDatum.Size(); ++i)
					{
						Scope* scopeTemp = otherDatum.Get<Scope>(i).Clone();
						Adopt(otherStr, *scopeTemp);
					}
				}
				else
				{
					auto [it, intsert] = _pairs.Insert(*(*otherit));
					_orderInterted.PushBack(&(*it));
				}
			}
		}
		return *this;
	}

	Scope& Scope::operator=(Scope&& rhs)
	{
		if (this != &rhs)
		{
			_parent = rhs._parent;
			Vector<HashMapType>::Iterator rhsit = rhs._orderInterted.begin();
			for (; rhsit != rhs._orderInterted.end(); ++rhsit)
			{
				std::string otherStr = (*rhsit)->first;
				Datum otherDatum = (*rhsit)->second;

				if (otherDatum.Type() == DatumTypes::TABLE)
				{
					for (size_t i = 0; i < otherDatum.Size(); ++i)
					{
						Adopt(otherStr, otherDatum.Get<Scope>(i));
					}
				}
				else
				{
					auto [it, intsert] = _pairs.Insert(std::move(*(*rhsit)));
					_orderInterted.PushBack(&(*it));
				}

			}
			if (_parent != nullptr)
			{
				Vector<HashMapType>::Iterator parentIt = _parent->_orderInterted.begin();
				for (; parentIt != _parent->_orderInterted.end(); ++parentIt)
				{
					std::string otherStr = (*parentIt)->first;
					Datum otherDatum = (*parentIt)->second;
					if (otherDatum.Type() == DatumTypes::TABLE)
					{
						auto [index, found] = otherDatum.Find(rhs);
						if (found)
						{
							otherDatum.Set(*this, index);
						}
					}
				}
			}
			rhs._parent = nullptr;
			rhs._pairs.ClearList();
			rhs._orderInterted.ClearList();
			rhs.ClearList();
		}
		return *this;
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		bool equal = false;

		if (rhs == nullptr)
		{
			return equal;
		}


		auto* s = rhs->As<Scope>();
		if (s == nullptr)
		{
			equal = false;
		}
		else
		{
			equal = (operator==(*s));
		}

		return equal;
	}

	std::string Scope::ToString() const
	{
		return std::string("Scope :D");
	}

	Datum* Scope::Find(const std::string& key)
	{
		if (key.empty())
		{
			return nullptr;
		}

		Datum* temp;
		auto [it, found, index] = _pairs.Find(key);

		if (!found)
		{
			temp = nullptr;
		}
		else
		{
			temp = &(*it).second;
		}

		return temp;
	}

	std::pair<Datum*, size_t> Scope::FindIndex(const std::string& key)
	{
		Datum* temp;
		auto [it, found, index] = _pairs.Find(key);

		if (!found)
		{
			temp = nullptr;
		}
		else
		{
			temp = &(*it).second;
		}

		return { temp, index };
	}

	const Datum* Scope::Find(const std::string& key) const
	{
		const Datum* temp;
		auto [it, found, index] = _pairs.Find(key);

		if (!found)
		{
			temp = nullptr;
		}
		else
		{
			temp = &(*it).second;
		}

		return temp;
	}

	Datum* Scope::Search(const std::string& str)
	{
		Datum* foundDatum = Find(str);

		if (foundDatum == nullptr && _parent != nullptr)
		{
			foundDatum = Search(str, _parent);
		}

		return foundDatum;
	}

	const Datum* Scope::Search(const std::string& str) const
	{
		const Datum* foundDatum = Find(str);

		if (foundDatum == nullptr && _parent != nullptr)
		{
			foundDatum = Search(str, _parent);
		}

		return foundDatum;
	}

	Datum* Scope::Search(const std::string& str, Scope*& scopeFound)
	{
		Datum* foundDatum = scopeFound->Find(str.c_str());

		if (foundDatum == nullptr && scopeFound->_parent != nullptr)
		{
			foundDatum = Search(str, scopeFound->_parent);
		}

		return foundDatum;
	}

	const Datum* Scope::Search(const std::string& str, Scope* const & scopeFound) const
	{
		const Datum* foundDatum = scopeFound->Find(str);

		if (foundDatum == nullptr && scopeFound != nullptr)
		{
			foundDatum = Search(str, scopeFound->_parent);
		}

		return foundDatum;
	}
	
	
	
	Scope* Scope::GetParent() const
	{
		return _parent;
	}

	Datum& Scope::operator[](const std::string& key)
	{

		Datum temp = Append(key);

		return Append(key);
	}

	Datum& Scope::operator[](size_t index) const
	{
		return (*_orderInterted[index]).second;
	}

	//This is slow, fix it
	bool Scope::operator==(const Scope& other) const
	{
		bool equals = true;

		if (this == &other)
		{
			return equals;
		}

		if (_pairs.Size() != other._pairs.Size())
		{
			equals = false;
			return equals;
		}
		else
		{
			HashMap<std::string, Datum>::ConstIterator otherit = other._pairs.begin();
			for (HashMap<std::string, Datum>::ConstIterator it = _pairs.begin(); it != _pairs.end(); ++it, ++otherit)
			{
				
				if ((*otherit).first == "this")
				{
					continue;
				}


				if ((*it) != (*otherit))
				{
					equals = false;
					break;
				}
			}
		}
		return equals;
	}

	bool Scope::operator!=(const Scope& other) const
	{
		return (!operator==(other));
	}

	bool Scope::IsEmpty() const
	{
		return _orderInterted.IsEmpty();
	}

	size_t Scope::Size() const
	{
		return _orderInterted.Size();
	}

	bool Scope::IsAncestorOf(const Scope& scope) const
	{
		bool isAncestor = false;
		Scope* parent = scope._parent;

		while (parent != nullptr)
		{

			if (parent == this)
			{
				isAncestor = true;
				break;
			}

			parent = parent->GetParent();
		}

		return isAncestor;
	}

	bool Scope::IsDescendantOf(const Scope& scope) const
	{
		return scope.IsAncestorOf(*this);
	}

	std::pair<Datum*, size_t> Scope::FindContainedScope(const Scope& scope)
	{
		Datum* temp = nullptr;
		for (Vector<HashMapType> ::Iterator it = _orderInterted.begin(); it != _orderInterted.end(); ++it)
		{
			temp = &(*it)->second;

			if (temp->Type() == DatumTypes::TABLE)
			{
				for (size_t i = 0; i < temp->Size(); ++i)
				{
					if (&scope == &temp->Get<Scope>(i))
					{
						return { temp, i};
					}
				}
			}
			
		}

		return {nullptr, 0 };
	}

	const std::pair<Datum*, size_t> Scope::FindContainedScope(const Scope& scope) const
	{
		Datum* temp = nullptr;
		for (Vector<HashMapType>::ConstIterator it = _orderInterted.cbegin(); it != _orderInterted.cend(); ++it)
		{
			temp = &(*it)->second;

			if (temp->Type() == DatumTypes::TABLE)
			{
				for (size_t i = 0; i < temp->Size(); ++i)
				{
					if (&scope == &temp->Get<Scope>(i))
					{
						return { temp, i };
					}
				}
			}

		}

		return { nullptr, 0 };
	}

	void Scope::ClearList()
	{
		for (Vector<HashMapType>::Iterator it = _orderInterted.begin(); it != _orderInterted.end(); ++it)
		{
			if ((*it)->first != "this")
			{
				Datum temp = (*it)->second;
				if (temp.Type() == DatumTypes::TABLE)
				{
					for (size_t index = 0; index < temp.Size(); ++index)
					{
						if (temp[index].GetParent() == this)
						{
							temp.Get<Scope>(index)._parent = nullptr;
							delete& temp.Get<Scope>(index);
						}
						

					}
				}
				temp.ClearList();
			}
		}
		_pairs.ClearList();
		_orderInterted.ClearList();
	}

	void Scope::Orphan(Scope& child)
	{
		if (&child == this)
		{
			throw std::runtime_error("Cannot Orphan Self :{");
		}
		if (this == child._parent || IsAncestorOf(child))
		{

			for (Vector<HashMapType>::Iterator it = _orderInterted.begin(); it != _orderInterted.end(); ++it)
			{
				Datum temp = (*it)->second;

				if (temp.Type() == DatumTypes::TABLE)
				{
					child._parent = nullptr;
					temp.Remove(child);

					

					break;

				}

				
			}
		}

	}

	Scope* Scope::Clone() const
	{
		return new Scope(*this);
	}


	

	Datum& Scope::Append(const std::string& key)
	{
		if (key.empty())
		{
			throw std::runtime_error("You must have a key value :{");
		}

		auto [it, found, index] = _pairs.Find(key);
		Datum* datum = nullptr;
		if (!found)
		{
			auto [itin, insert] = _pairs.Insert(std::pair(key, Datum()));
			datum = &(*itin).second;

			_orderInterted.PushBack(&(*itin));
		}
		else
		{
			datum = &(*it).second;
		}


		return *datum;
	}

	Scope& Scope::AppendScope(const std::string& key)
	{
		Datum* scopeDatum = &Append(key);

		if (scopeDatum->Type() != DatumTypes::TABLE && scopeDatum->Type() != DatumTypes::UNKNOWN)
		{
			throw std::runtime_error("Non Scope Data Already in this Datum. Please try another key :{");
		}
		
		
		scopeDatum->PushBack(*new Scope(this));

		Scope* temp = &scopeDatum->Back<Scope>();


		return *temp;
	}

	void Scope::Adopt(const std::string& key, Scope& child)
	{
		if (this == &child)
		{
			throw std::runtime_error("Cannont Adopt yourself :{");
		}

		if (this != child._parent || !(IsAncestorOf(child)))
		{
			Datum* scopeDatum = &Append(key);


			if (child._parent != nullptr)
			{
				Orphan(child);
			}

			child._parent = this;


			if (scopeDatum->Type() != DatumTypes::TABLE && scopeDatum->Type() != DatumTypes::UNKNOWN)
			{
				throw std::runtime_error("Non Scope Data Already in this Datum. Please try another key :{");
			}
			scopeDatum->PushBack(child);
		}
	}

}