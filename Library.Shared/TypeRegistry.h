#pragma once
#include "Scope.h"
#include "Signature.h"

namespace FieaGameEngine
{
	class TypeRegistry final
	{
	public:


		static TypeRegistry* GetInstance();


		void AddEntry(const std::pair<size_t, Vector<Signature>>& pair);

		Vector<Signature>& Get(size_t key);

	private:


		TypeRegistry();
		~TypeRegistry() = delete;

		static TypeRegistry* _instance;
		
		HashMap<size_t, Vector<Signature>> _pairs;
	};
}


