#include "pch.h"
#include "Attributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed)

	Attributed::Attributed(IdType typeID)
	{
		Populate(typeID);
	}

	Attributed::Attributed(const Attributed& other):
		Scope::Scope(other),
		_prescribedSize{other._prescribedSize}
	{
		ReasignPointers(other.TypeIdInstance());

	}

	Attributed& Attributed::operator=(const Attributed& other)
	{
		if (this != &other)
		{
			ClearList();
			Scope::operator=(other);
			ReasignPointers(other.TypeIdInstance());
		}
		
		return *this;
	}

	Attributed::Attributed(Attributed&& other) noexcept :
		Scope::Scope(std::move(other)),
		_prescribedSize{ other._prescribedSize }
	{
		ReasignPointers(other.TypeIdInstance());

	}

	Attributed& Attributed::operator=(Attributed&& other) noexcept
	{
		if (this != &other)
		{
			ClearList();
			Scope::operator=(std::move(other));
			ReasignPointers(other.TypeIdInstance());

		}

		return *this;
	}

	std::string Attributed::ToString() const
	{
		return "Attributed :D";
	}

	void Attributed::Populate(IdType typeID)
	{
		Vector<Signature>& signature = TypeRegistry::GetInstance()->Get(typeID);

		Append("this") = this;
		uint8_t* thisptr = reinterpret_cast<uint8_t*>(this);
		for (auto it = signature.begin(); it != signature.end(); ++it)
		{
			Datum* createdDatum = &Append((*it)._name);
			createdDatum->SetType((*it)._type);
			if (createdDatum->Type() == DatumTypes::TABLE)
			{
				for (size_t index = 0; index < (*it)._size; ++index)
				{
					AppendScope((*it)._name);
				}
			}
			else
			{
				createdDatum->SetStorage((*it)._type,(thisptr + (*it)._offset), (*it)._size);
			}
		}

		_prescribedSize = signature.Size() + 1;
	}

	bool Attributed::IsAttribute(const std::string& key) const
	{
		bool found = false;

		const Datum* d = Find(key);
		
		if (d != nullptr)
		{
			found = true;
		}

		return found;
	}

	bool Attributed::IsPrescribedAttribute(const std::string& key) const
	{
		bool found = false;
		size_t index = 0;
		for (; index < _prescribedSize; ++index)
		{
			if (_orderInterted.At(index)->first == key)
			{
				found = true;
				break;
			}

		}


		return found;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& key) const
	{
		bool found = false;
		
		found = IsPrescribedAttribute(key);

		return !found;
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& key)
	{
		if (IsPrescribedAttribute(key))
		{
			throw std::runtime_error("Cannont Append to a Prescribed Attribute Name :{");
		}
		
		Datum* foundDatum = &Append(key);

		return *foundDatum;
	}



	void Attributed::ReasignPointers(size_t typeInstance)
	{
		Vector<Signature>& signature = TypeRegistry::GetInstance()->Get(typeInstance);
		Append("this") = this;
		uint8_t* thisptr = reinterpret_cast<uint8_t*>(this);
		for (auto it = signature.begin(); it != signature.end(); ++it)
		{
			Datum* createdDatum = &Append((*it)._name);
			createdDatum->SetStorage((*it)._type, (thisptr + (*it)._offset), (*it)._size);
		}
	}

	

}
