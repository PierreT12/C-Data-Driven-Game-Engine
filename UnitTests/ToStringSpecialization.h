#pragma once
#include "pch.h"
#include "Foo.h"
//#include "RTTI.h"
#include "AttributedFoo.h"
#include "DerivedAttributedFoo.h"



using namespace FooSupport;
using namespace FieaGameEngine;


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	static const char* DatumStrings[static_cast<size_t>(DatumTypes::END) + 1] = { "UNKNOWN","INT", "FLOAT", "VEC4", "MAT4", "STRING", "POINTER", "TABLE"};



	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<Foo>(const Foo& _Type)
	{
		//Just a funky Macro, nothing special
		RETURN_WIDE_STRING(_Type.Data());
	}


	template<>
	inline std::wstring ToString<Foo>(const Foo* _Type)
	{
		
		RETURN_WIDE_STRING(_Type->Data());
	}


	template<>
	inline std::wstring ToString<Foo>(Foo* _Type)
	{
		
		RETURN_WIDE_STRING(_Type->Data());
	}

	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4& _Type)
	{
		std::wstring temp = (ToString(_Type.x) + L" " + ToString(_Type.y) + L" " + ToString(_Type.z) + L" " + ToString(_Type.w));
		//Just a funky Macro, nothing special
		RETURN_WIDE_STRING(temp);
	}


	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4* _Type)
	{

		std::wstring temp = (ToString(_Type->x) + L" " + ToString(_Type->y) + L" " + ToString(_Type->z) + L" " + ToString(_Type->w));
		RETURN_WIDE_STRING(temp);
	}
	


	template<>
	inline std::wstring ToString<glm::vec4>(glm::vec4* _Type)
	{

		std::wstring temp = (ToString(_Type->x) + L" " + ToString(_Type->y) + L" " + ToString(_Type->z) + L" " + ToString(_Type->w));
		RETURN_WIDE_STRING(temp);
	}

	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4& _Type)
	{
		std::wstring temp = (ToString(_Type[0].x) + L" " + ToString(_Type[0].y) + L" " + ToString(_Type[0].z) + L" " + ToString(_Type[0].w)+ L","+
			ToString(_Type[1].x) + L" " + ToString(_Type[1].y) + L" " + ToString(_Type[1].z) + L" " + ToString(_Type[1].w) + L"," +
			ToString(_Type[2].x) + L" " + ToString(_Type[2].y) + L" " + ToString(_Type[2].z) + L" " + ToString(_Type[2].w) + L"," +
			ToString(_Type[3].x) + L" " + ToString(_Type[3].y) + L" " + ToString(_Type[3].z) + L" " + ToString(_Type[3].w));
		//Just a funky Macro, nothing special
		RETURN_WIDE_STRING(temp);
	}
	
	
	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4* _Type)
	{
	
		std::wstring temp = (ToString((*_Type)[0].x) + L" " + ToString((*_Type)[0].y) + L" " + ToString((*_Type)[0].z) + L" " + ToString((*_Type)[0].w) + L"," +
			ToString((*_Type)[1].x) + L" " + ToString((*_Type)[1].y) + L" " + ToString((*_Type)[1].z) + L" " + ToString((*_Type)[1].w) + L"," +
			ToString((*_Type)[2].x) + L" " + ToString((*_Type)[2].y) + L" " + ToString((*_Type)[2].z) + L" " + ToString((*_Type)[2].w) + L"," +
			ToString((*_Type)[3].x) + L" " + ToString((*_Type)[3].y) + L" " + ToString((*_Type)[3].z) + L" " + ToString((*_Type)[3].w));
		RETURN_WIDE_STRING(temp);
	}
	
	
	
	template<>
	inline std::wstring ToString<glm::mat4>(glm::mat4* _Type)
	{
	
		std::wstring temp = (ToString((*_Type)[0].x) + L" " + ToString((*_Type)[0].y) + L" " + ToString((*_Type)[0].z) + L" " + ToString((*_Type)[0].w) + L"," +
			ToString((*_Type)[1].x) + L" " + ToString((*_Type)[1].y) + L" " + ToString((*_Type)[1].z) + L" " + ToString((*_Type)[1].w) + L"," +
			ToString((*_Type)[2].x) + L" " + ToString((*_Type)[2].y) + L" " + ToString((*_Type)[2].z) + L" " + ToString((*_Type)[2].w) + L"," +
			ToString((*_Type)[3].x) + L" " + ToString((*_Type)[3].y) + L" " + ToString((*_Type)[3].z) + L" " + ToString((*_Type)[3].w));
		RETURN_WIDE_STRING(temp);
	}





	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<DatumTypes>(const DatumTypes& _Type)
	{
		//Just a funky Macro, nothing special
		RETURN_WIDE_STRING(DatumStrings[static_cast<size_t>(_Type)]);
	}


	template<>
	inline std::wstring ToString<DatumTypes>(const DatumTypes* _Type)
	{

		RETURN_WIDE_STRING(DatumStrings[static_cast<size_t>(*_Type)]);
	}


	template<>
	inline std::wstring ToString<DatumTypes>(DatumTypes* _Type)
	{

		RETURN_WIDE_STRING(DatumStrings[static_cast<size_t>(*_Type)]);
	}




	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<std::pair<const int, Foo>>(const std::pair<const int, Foo>& _Type)
	{
		try
		{
			return ToString((_Type.second));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}
	
	
	template<>
	inline std::wstring ToString<std::pair<const int, Foo>>(const std::pair<const int, Foo>* _Type)
	{
	
		try
		{
			return ToString((_Type->second));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}
	
	
	template<>
	inline std::wstring ToString<std::pair<const int, Foo>>(std::pair<const int, Foo>* _Type)
	{
	
		try
		{
			return ToString((_Type->second));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}


	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator& _Type)
	{
	
		try
		{
			return ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}
	
	template<>
	inline std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator* _Type)
	{
	
		try
		{
			ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}
	
	
	template<>
	inline std::wstring ToString<SList<Foo>::Iterator>(SList<Foo>::Iterator* _Type)
	{
	
		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}




	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& _Type)
	{
		try
		{
			return ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}

	template<>
	inline std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator* _Type)
	{
		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}
	
	
	template<>
	inline std::wstring ToString<SList<Foo>::ConstIterator>(SList<Foo>::ConstIterator* _Type)
	{
		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}



	template<>
	inline std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& _Type)
	{

		try
		{
			return ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}

	template<>
	inline std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator* _Type)
	{

		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}


	template<>
	inline std::wstring ToString<Vector<Foo>::Iterator>(Vector<Foo>::Iterator* _Type)
	{

		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}




	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& _Type)
	{
		try
		{
			return ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}

	template<>
	inline std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator* _Type)
	{
		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}


	template<>
	inline std::wstring ToString<Vector<Foo>::ConstIterator>(Vector<Foo>::ConstIterator* _Type)
	{
		try
		{
			ToString(*_Type);
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}




	template<>
	inline std::wstring ToString<HashMap<int,Foo>::Iterator>(const HashMap<int, Foo>::Iterator& _Type)
	{

		try
		{
			return ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::Iterator>(const HashMap<int, Foo>::Iterator* _Type)
	{

		try
		{
			return ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}


	template<>
	inline std::wstring ToString<HashMap<int, Foo>::Iterator>(HashMap<int, Foo>::Iterator* _Type)
	{

		try
		{
			ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}




	//Telling the compiler this is a specialization
	template<>
	inline std::wstring ToString<HashMap<int, Foo>::ConstIterator>(const HashMap<int, Foo>::ConstIterator& _Type)
	{
		try
		{
			return ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}

	template<>
	inline std::wstring ToString<HashMap<int, Foo>::ConstIterator>(const HashMap<int, Foo>::ConstIterator* _Type)
	{
		try
		{
			ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}


	template<>
	inline std::wstring ToString<HashMap<int, Foo>::ConstIterator>(HashMap<int, Foo>::ConstIterator* _Type)
	{
		try
		{
			ToString(*(_Type));
		}
		catch (std::runtime_error)
		{
			RETURN_WIDE_STRING(L"End of the list");
		}
	}

















}