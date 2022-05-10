#pragma once
#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(HaspMapTest)
	{
	public:

		//Uniform initalization
		const Foo first{ 10 };
		const Foo second{ 20 };
		const Foo third{ 30 };


		std::pair<int, Foo> a{ 1, first };
		std::pair<int, Foo> ab{ 2, first };
		std::pair<int, Foo> b{ 22, second };
		std::pair<int, Foo> c{ 50, third };




		TEST_METHOD_INITIALIZE(Initalize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"There was a Memory Leak!! :{");
			}
#endif
		}

		TEST_METHOD(Constructor)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			auto TooSmall = [] {HashMap<int, Foo> map2(1); };
			Assert::ExpectException<std::exception>(TooSmall);

			HashMap<int, std::string>map2(23);
		
		}


		TEST_METHOD(CopyConstructor)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			HashMap<int, Foo> map2(map);

			
			Assert::AreEqual(size_t(4), map2.Size());
			Assert::AreEqual(size_t(12), map2.GetBuckets());
			Assert::AreNotEqual(size_t(12), map2.GetEmptyBuckets());
			Assert::AreEqual(map.At(1), map2.At(1));

		}


		TEST_METHOD(CopyOperator)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			HashMap<int, Foo> map2(23);


			map2 = map;

			Assert::AreEqual(size_t(4), map2.Size());
			Assert::AreEqual(size_t(12), map2.GetBuckets());
			Assert::AreNotEqual(size_t(12), map2.GetEmptyBuckets());
			Assert::AreEqual(map.At(1), map2.At(1));
		}

		TEST_METHOD(MoveConstructor)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			HashMap<int, Foo> map2 = std::move(map);


			Assert::AreEqual(size_t(4), map2.Size());
			Assert::AreEqual(size_t(12), map2.GetBuckets());
			Assert::AreNotEqual(size_t(12), map2.GetEmptyBuckets());

			Assert::AreEqual(size_t(0), map.Size());
			Assert::AreEqual(size_t(0), map.GetBuckets());
			Assert::AreEqual(size_t(0), map.GetEmptyBuckets());

		
		}

		TEST_METHOD(MoveOperator)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			HashMap<int, Foo> map2(22);

			map2 = std::move(map);

			Assert::AreEqual(size_t(4), map2.Size());
			Assert::AreEqual(size_t(12), map2.GetBuckets());
			Assert::AreNotEqual(size_t(12), map2.GetEmptyBuckets());

			Assert::AreEqual(size_t(0), map.Size());
			Assert::AreEqual(size_t(0), map.GetBuckets());
			Assert::AreEqual(size_t(0), map.GetEmptyBuckets());


		}

		TEST_METHOD(BracketOperator)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			Assert::AreEqual(first, map[1]);

			//Assert::AreNotEqual(first, map[77]);

		}

		TEST_METHOD(At)
		{
			HashMap<int, Foo> map(12);

			auto NotFound = [&map] {map.At(1); };
			Assert::ExpectException<std::exception>(NotFound);

			CommonHashMapSetUp(map);

			Assert::AreEqual(first, map.At(1));
			Assert::AreEqual(second, map.At(22));
			Assert::AreEqual(third, map.At(50));

			
		}

		TEST_METHOD(AtConst)
		{
			HashMap<int, Foo> map(12);
			
			const HashMap<int, Foo>* mapPtr = &map;

			auto NotFound = [&mapPtr] {mapPtr->At(1); };
			Assert::ExpectException<std::exception>(NotFound);

			CommonHashMapSetUp(map);
			
			Assert::AreEqual(first, mapPtr->At(1));
			Assert::AreEqual(second, mapPtr->At(22));
			Assert::AreEqual(third, mapPtr->At(50));


			map.ClearList();

			const HashMap<int, Foo>* mapPtr2 = &map;

			auto NotFound2 = [&mapPtr2] {mapPtr2->At(1); };
			Assert::ExpectException<std::exception>(NotFound2);
		}

		TEST_METHOD(GetLoadFactor)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			Assert::AreEqual(0.333333333f, map.GetLoadFactor());
		}

		TEST_METHOD(GetEmptyBuckets)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			Assert::AreNotEqual(size_t(12), map.GetEmptyBuckets());
		}
	
		TEST_METHOD(GetBuckets)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
		}

		TEST_METHOD(ContainsKey)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			Assert::IsTrue(std::get<1>(map.ContainsKey(1)));


			Assert::IsFalse(std::get<1>(map.ContainsKey(100)));
		}


		TEST_METHOD(ContainsKeyConst)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			const HashMap<int, Foo>* mapPtr = &map;

			Assert::IsTrue(std::get<1>(mapPtr->ContainsKey(1)));


			Assert::IsFalse(std::get<1>(mapPtr->ContainsKey(100)));
		}


		TEST_METHOD(Resize)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			map.Resize(20);

			Assert::AreEqual(size_t(4), map.Size());
			Assert::AreEqual(size_t(20), map.GetBuckets());
			Assert::AreNotEqual(size_t(20), map.GetEmptyBuckets());
		}

		TEST_METHOD(Rehash)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			map.Rehash();

			Assert::AreEqual(size_t(4), map.Size());
			Assert::AreEqual(size_t(12), map.GetBuckets());
			Assert::AreNotEqual(size_t(12), map.GetEmptyBuckets());
		}

		TEST_METHOD(IsEmpty)
		{
			HashMap<int, Foo> map(12);

			Assert::IsTrue(map.IsEmpty());

			CommonHashMapSetUp(map);

			Assert::IsFalse(map.IsEmpty());
		}

		

		TEST_METHOD(Size)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
		}

	


		TEST_METHOD(ClearList)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			map.ClearList();

			Assert::AreEqual(size_t(0), map.Size());
			Assert::AreEqual(size_t(12), map.GetEmptyBuckets());

			auto NotFound = [&map] {map.At(1); };
			Assert::ExpectException<std::exception>(NotFound);

		}



		//Iterators

		TEST_METHOD(Iterator)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);

		}

		TEST_METHOD(IteratorCopyConstructor)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);

			HashMap<int, Foo>::Iterator it = map.begin();

			HashMap<int, Foo>::Iterator it2 = it;

			Assert::AreEqual(it, it2);

		}

		TEST_METHOD(IteratorCopyOperator)
		{
			HashMap<int, Foo> map(12);
			HashMap<int, Foo> map2(12);

			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);

			map2.Insert({ 200, third });
			
			HashMap<int, Foo>::Iterator it = map.begin();
			
			HashMap<int, Foo>::Iterator it2 = map2.begin();
			
			Assert::AreNotEqual(it, it2);
			
			it2 = it;
			
			Assert::AreEqual(it, it2);
		}


		TEST_METHOD(IteratorDeRef)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);

			

			HashMap<int, Foo>::Iterator it = map.begin();
			HashMap<int, Foo>::Iterator it2 = map.end();

			auto NotFound = [&it2] { *it2; };
			Assert::ExpectException<std::exception>(NotFound);


			Assert::AreEqual(first, (*it).second);
		}

		TEST_METHOD(IteratorDeRefPointer)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);

			HashMap<int, Foo>::Iterator it = map.begin();
			HashMap<int, Foo>::Iterator it2 = map.end();

			auto NotFound = [&it2] { it2->second; };
			Assert::ExpectException<std::exception>(NotFound);

		

			Assert::AreEqual(first, it->second);
		}

		TEST_METHOD(IteratorPreFix)
		{
			HashMap<int,Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);
			HashMap<int, Foo>::Iterator it = map.begin();
			HashMap<int, Foo>::Iterator it2 = map.begin();
			HashMap<int, Foo>::Iterator itOther;

			auto Increase = [&itOther] {++itOther; };
			Assert::ExpectException<std::runtime_error>(Increase);

			++it2;

			Assert::AreEqual(first, (*it).second);
			Assert::AreEqual(third, (*it2).second);

			Assert::AreNotEqual(it, it2);

		}

		TEST_METHOD(IteratorPostFix)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);
			HashMap<int, Foo>::Iterator it = map.begin();
			HashMap<int, Foo>::Iterator it2 = it++;
			HashMap<int, Foo>::Iterator itOther;

			auto Increase = [&itOther] {itOther++; };
			Assert::ExpectException<std::runtime_error>(Increase);

			Assert::AreEqual(third, (*it).second);
			Assert::AreEqual(first, (*it2).second);

			Assert::AreNotEqual(it, it2);
		}

		TEST_METHOD(IteratorEqual)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);
			HashMap<int, Foo>::Iterator it = map.begin();
			HashMap<int, Foo>::Iterator it2 = map.begin();

			Assert::AreEqual(first, (*it).second);
			Assert::AreEqual(first, (*it2).second);

			Assert::AreEqual(it, it2);
		}

		TEST_METHOD(IteratorNotEqual)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);
			HashMap<int, Foo>::Iterator it = map.begin();
			HashMap<int, Foo>::Iterator it2 = map.begin();

			Assert::AreEqual(first, (*it).second);
			Assert::AreEqual(first, (*it2).second);

			++it2;

			Assert::AreNotEqual(it, it2);

		}


		TEST_METHOD(ConstIterator)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);

			HashMap<int, Foo>::Iterator it = map.begin();

			HashMap<int, Foo>::ConstIterator constIt = it;

			size_t count = 0;
			for (constIt; constIt != map.cend(); ++constIt, ++count)
			{
				constIt;
			}

			Assert::AreEqual(map.Size(), count);


		}



		TEST_METHOD(ConstIteratorCopyConstructor)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);

			HashMap<int, Foo>::ConstIterator it = map.cbegin();

			HashMap<int, Foo>::ConstIterator it2 = it;

			Assert::AreEqual(it, it2);
		}

		TEST_METHOD(ConstIteratorCopyOperator)
		{
			HashMap<int, Foo> map(12);
			HashMap<int, Foo> map2(12);

			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);

			map2.Insert({ 200, third });

			HashMap<int, Foo>::ConstIterator it = map.cbegin();

			HashMap<int, Foo>::ConstIterator it2 = map2.cbegin();

			Assert::AreNotEqual(it, it2);

			it2 = it;

			Assert::AreEqual(it, it2);
		}


		TEST_METHOD(ConstIteratorDeRef)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);



			HashMap<int, Foo>::ConstIterator it = map.cbegin();
			HashMap<int, Foo>::ConstIterator it2 = map.cend();

			auto NotFound = [&it2] { *it2; };
			Assert::ExpectException<std::exception>(NotFound);


			Assert::AreEqual(first, (*it).second);
		}

		TEST_METHOD(ConstIteratorDeRefPointer)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);

			HashMap<int, Foo>::ConstIterator it = map.cbegin();
			HashMap<int, Foo>::ConstIterator it2 = map.cend();

			auto NotFound = [&it2] { it2->second; };
			Assert::ExpectException<std::exception>(NotFound);



			Assert::AreEqual(first, it->second);
		}


		TEST_METHOD(ConstIteratorPreFix)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);
			HashMap<int, Foo>::ConstIterator it = map.cbegin();
			HashMap<int, Foo>::ConstIterator it2 = map.cbegin();
			HashMap<int, Foo>::ConstIterator itOther;

			auto Increase = [&itOther] {++itOther; };
			Assert::ExpectException<std::runtime_error>(Increase);

			++it2;

			Assert::AreEqual(first, (*it).second);
			Assert::AreEqual(third, (*it2).second);

			Assert::AreNotEqual(it, it2);

		}

		TEST_METHOD(ConstIteratorPostFix)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);
			HashMap<int, Foo>::ConstIterator it = map.cbegin();
			HashMap<int, Foo>::ConstIterator it2 = it++;
			HashMap<int, Foo>::ConstIterator itOther;

			auto Increase = [&itOther] {itOther++; };
			Assert::ExpectException<std::runtime_error>(Increase);

			Assert::AreEqual(third, (*it).second);
			Assert::AreEqual(first, (*it2).second);

			Assert::AreNotEqual(it, it2);
		}

		TEST_METHOD(ConstIteratorEqual)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);
			HashMap<int, Foo>::ConstIterator it = map.cbegin();
			HashMap<int, Foo>::ConstIterator it2 = map.cbegin();

			Assert::AreEqual(first, (*it).second);
			Assert::AreEqual(first, (*it2).second);

			Assert::AreEqual(it, it2);

		}

		TEST_METHOD(ConstIteratorNotEqual)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);
			HashMap<int, Foo>::ConstIterator it = map.cbegin();
			HashMap<int, Foo>::ConstIterator it2 = map.cbegin();

			Assert::AreEqual(first, (*it).second);
			Assert::AreEqual(first, (*it2).second);

			++it2;

			Assert::AreNotEqual(it, it2);

		}





		TEST_METHOD(BeginEnd)
		{
			
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonIteratorSetUp(map);
			HashMap<int, Foo>::Iterator it = map.begin();

			//Assert::AreNotEqual(map.begin(), map.end());

			Assert::AreEqual(first, (*it).second);
		}

		TEST_METHOD(BeginEndConst)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);
			
			const HashMap<int, Foo>* ptrMap = &map;

			ptrMap;
			
			HashMap<int, Foo>::ConstIterator it = ptrMap->begin();
			
			//Assert::AreNotEqual(ptrMap->begin(), ptrMap->end());
			
			Assert::AreEqual(first, (*it).second);



		}

		TEST_METHOD(CBeginEnd)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);
			HashMap<int, Foo>::ConstIterator it = map.cbegin();

			//Assert::AreNotEqual(map.cbegin(), map.cend());

			Assert::AreEqual(first, (*it).second);


		}



		TEST_METHOD(Insert)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			Assert::AreEqual(first, map.At(1));
			Assert::AreEqual(second, map.At(22));
			Assert::AreEqual(third, map.At(50));

		}

		TEST_METHOD(Find)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			std::tuple<HashMap<int, Foo>::Iterator, bool, size_t>  findValue = map.Find(1);

			Assert::AreEqual(first, (*(findValue._Myfirst._Val)).second);

			findValue = map.Find(100);

			auto NotFound = [&findValue] {(*(findValue._Myfirst._Val)).second; };
			Assert::ExpectException<std::exception>(NotFound);

			CommonIteratorSetUp(map);


		}

		TEST_METHOD(FindConst)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);

			const HashMap<int, Foo>* mapPtr = &map;

			std::tuple<HashMap<int, Foo>::ConstIterator, bool, size_t>  findValue = mapPtr->Find(1);

			Assert::AreEqual(first, (*(findValue._Myfirst._Val)).second);

			findValue = mapPtr->Find(100);

			auto NotFound = [&findValue] {(*(findValue._Myfirst._Val)).second; };
			Assert::ExpectException<std::exception>(NotFound);

			CommonIteratorSetUp(map);

		}

		TEST_METHOD(Remove)
		{
			HashMap<int, Foo> map(12);
			CommonHashMapSetUp(map);
			CommonConstIteratorSetUp(map);

			HashMap<int, Foo>::Iterator begin = map.begin();
			map.Remove(1);
			Assert::AreEqual(size_t(3), map.Size());


		}



	private:
		static _CrtMemState _startMemState;

		void CommonHashMapSetUp(HashMap<int, Foo>& map);
		void CommonIteratorSetUp(HashMap<int, Foo>& map);
		void CommonConstIteratorSetUp(HashMap<int, Foo>& map);


	};

	_CrtMemState HaspMapTest::_startMemState;



	void HaspMapTest::CommonHashMapSetUp(HashMap<int, Foo>& map)
	{
		Assert::AreEqual(size_t(0), map.Size());
		Assert::AreEqual(size_t(12), map.GetBuckets());
		Assert::AreEqual(size_t(12), map.GetEmptyBuckets());

		map.Insert(a);
		
		Assert::AreEqual(size_t(1), map.Size());
		
		map.Insert(b);
		
		Assert::AreEqual(size_t(2), map.Size());
		
		map.Insert(c);
		
		Assert::AreEqual(size_t(3), map.Size());

		map.Insert(ab);

		Assert::AreEqual(size_t(4), map.Size());
	}

	void HaspMapTest::CommonIteratorSetUp(HashMap<int, Foo>& map)
	{
		size_t count = 0;
		for (HashMap<int, Foo>::Iterator it = map.begin(); it != map.end(); ++it, ++count)
		{
			map.Size();
			it;
		}

		Assert::AreEqual(map.Size(), count);

	}

	void HaspMapTest::CommonConstIteratorSetUp(HashMap<int, Foo>& map)
	{
		size_t count = 0;
		for (HashMap<int, Foo>::ConstIterator it = map.cbegin(); it != map.cend(); ++it, ++count)
		{
			it;
		}

		Assert::AreEqual(map.Size(), count);


	}

}
