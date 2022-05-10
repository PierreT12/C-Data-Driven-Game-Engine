#pragma once
#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(VectorTest)
	{
	public:

		//Uniform initalization
		const Foo first{ 10 };
		const Foo second{ 20 };
		const Foo third{ 30 };




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
			Vector<Foo> list;

			CommonVectorSetupTest(list);

		}


		TEST_METHOD(CopyConstructor)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			Vector<Foo> list2{ list };

			Assert::IsTrue(std::equal(list.begin(), list.end(), list2.begin()));
		}


		TEST_METHOD(CopyOperator)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			Vector<Foo> list2;

			CommonVectorSetupTest(list2);

			list2 = list;


			Assert::IsTrue(std::equal(list.begin(), list.end(), list2.begin()));
		}

		TEST_METHOD(MoveConstructor)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			Vector<Foo> list2 = std::move(list);
			

			Assert::AreEqual(first, list2.Front());
			Assert::AreEqual(third, list2.Back());
			Assert::AreEqual(size_t(3), list2.Size());
			Assert::AreEqual(size_t(10), list2.Capacity());

			
		}


		TEST_METHOD(MoveOperator)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			Vector<Foo> list2;

			list2 = std::move(list);


			Assert::AreEqual(first, list2.Front());
			Assert::AreEqual(third, list2.Back());
			Assert::AreEqual(size_t(3), list2.Size());
			Assert::AreEqual(size_t(10), list2.Capacity());

		}

		TEST_METHOD(BracketOperator)
		{
			Vector<Foo> f;

			CommonVectorSetupTest(f);

			Assert::AreEqual(first, f[0]);

			auto At = [&f] {f[100]; };
			Assert::ExpectException<std::out_of_range>(At);

		}

		TEST_METHOD(BracketOperatorConst)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			const Vector<Foo>* ptrList = &list;

			Assert::AreEqual(first, ptrList->operator[](0));

			auto At = [&ptrList] {ptrList->operator[](100); };
			Assert::ExpectException<std::out_of_range>(At);

		}

		TEST_METHOD(At)
		{
			Vector<Foo> f;

			CommonVectorSetupTest(f);

			Assert::AreEqual(first, f.At(0));

			auto At = [&f] {f.At(100); };
			Assert::ExpectException<std::out_of_range>(At);

		}

		TEST_METHOD(AtConst)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			const Vector<Foo>* ptrList = &list;

			Assert::AreEqual(first, ptrList->At(0));

			auto At = [&ptrList] {ptrList->At(100); };
			Assert::ExpectException<std::out_of_range>(At);

		}

		TEST_METHOD(PopBack)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			list.PopBack();

			Assert::AreEqual(second, list.Back());
			Assert::AreEqual(first, list.Front());

			list.PopBack();

			Assert::AreEqual(first, list.Back());
			Assert::AreEqual(first, list.Front());

			list.PopBack();

			Assert::IsTrue(list.IsEmpty());
		}

		TEST_METHOD(PushBack)
		{
			Vector<Foo> f;

			CommonVectorSetupTest(f);
		}

		TEST_METHOD(IsEmpty)
		{
			Vector<Foo> f;

			Assert::IsTrue(f.IsEmpty());
			CommonVectorSetupTest(f);

			Assert::IsFalse(f.IsEmpty());
		}

		TEST_METHOD(Front)
		{
			Vector<Foo> list;

			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);


			CommonVectorSetupTest(list);
			
			Assert::AreEqual(first, list.Front());

		}

		TEST_METHOD(FrontConst)
		{
			Vector<Foo> list;

			const Vector<Foo>* ptrList = &list;

			auto Front = [&ptrList] {ptrList->Front(); };
			Assert::ExpectException<std::runtime_error>(Front);

			CommonVectorSetupTest(list);

			ptrList = &list;

			Assert::AreEqual(first, list.Front());
		}


		TEST_METHOD(Back)
		{
			Vector<Foo> list;

			auto Back = [&list] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(Back);

			CommonVectorSetupTest(list);
		
			Assert::AreEqual(third, list.Back());
		}

		TEST_METHOD(BackConst)
		{
			Vector<Foo> list;

			const Vector<Foo>* ptrList = &list;

			auto Back = [&ptrList] {ptrList->Back(); };
			Assert::ExpectException<std::runtime_error>(Back);

			CommonVectorSetupTest(list);

			ptrList = &list;

			Assert::AreEqual(third, list.Back());

		}

		TEST_METHOD(Size)
		{
			Vector<Foo> list;
			
			Assert::AreEqual(size_t(0), list.Size());

			CommonVectorSetupTest(list);
		}

		TEST_METHOD(Capacity)
		{
			Vector<Foo> list;

			Assert::AreEqual(size_t(10), list.Capacity());

			CommonVectorSetupTest(list);
		}

		TEST_METHOD(Reserve)
		{
			Vector<Foo> list;
			

			CommonVectorSetupTest(list);

			Assert::AreEqual(size_t(10), list.Capacity());

			list.Reserve(30);

			Assert::AreEqual(size_t(30), list.Capacity());

			Assert::AreEqual(size_t(3), list.Size());

			
		}

		TEST_METHOD(ClearList)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			list.ClearList();

			Assert::AreEqual(size_t(0), list.Size());

			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);
		}



	//Iterators

		TEST_METHOD(Iterator)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			Vector<Foo>::Iterator it = list.begin();
			CommonIteratorTest(list);

			Assert::AreEqual(first, *it);
		}

		TEST_METHOD(IteratorCopyConstructor)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonIteratorTest(list);
			Vector<Foo>::Iterator it = list.begin();

			Vector<Foo>::Iterator it2 = it;

			Assert::AreEqual(it, it2);
		}

		TEST_METHOD(IteratorCopyOperator)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonIteratorTest(list);
			Vector<Foo>::Iterator it = list.begin();

			Vector<Foo>::Iterator it2;

			it2 = it;

			Assert::AreEqual(it, it2);
		}


		TEST_METHOD(IteratorDeRef)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);

			Assert::AreEqual(first, *(list.begin()));

			auto DeRef = [&list] {*(list.end()); };
			Assert::ExpectException<std::out_of_range>(DeRef);
		}

		TEST_METHOD(IteratorPreFix)
		{
			Vector<Foo> list;
			Vector<Foo> list2;
			CommonVectorSetupTest(list);
			CommonIteratorTest(list);
			Vector<Foo>::Iterator it = list.begin();
			Vector<Foo>::Iterator it2 = list.begin();
			Vector<Foo>::Iterator itOther;

			auto Increase = [&itOther] {++itOther; };
			Assert::ExpectException<std::runtime_error>(Increase);

			++it2;

			Assert::AreEqual(first, *it);
			Assert::AreEqual(second, *it2);

			Assert::AreNotEqual(it, it2);

		}

		TEST_METHOD(IteratorPostFix)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonIteratorTest(list);
			Vector<Foo>::Iterator it = list.begin();
			Vector<Foo>::Iterator it2 = it++;
			Vector<Foo>::Iterator itOther;

			auto Increase = [&itOther] {itOther++; };
			Assert::ExpectException<std::runtime_error>(Increase);

			Assert::AreEqual(second, *it);
			Assert::AreEqual(first, *it2);

			Assert::AreNotEqual(it, it2);
		}

		TEST_METHOD(IteratorEqual)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonIteratorTest(list);
			Vector<Foo>::Iterator it = list.begin();
			Vector<Foo>::Iterator it2 = list.begin();

			Assert::AreEqual(first, *it);
			Assert::AreEqual(first, *it2);

			Assert::AreEqual(it, it2);
		}

		TEST_METHOD(IteratorNotEqual)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonIteratorTest(list);
			Vector<Foo>::Iterator it = list.begin();
			Vector<Foo>::Iterator it2 = list.begin();

			++it2;
			
			Assert::AreEqual(first, *it);
			Assert::AreEqual(second, *it2);
			Assert::AreNotEqual(it, it2);

		}


		TEST_METHOD(ConstIterator)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();
			CommonConstIteratorTest(list);

			Assert::AreEqual(first, *it);
		}

		TEST_METHOD(ConstIteratorCopyConstructor)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonConstIteratorTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();

			Vector<Foo>::ConstIterator it2 = it;

			Assert::AreEqual(it, it2);
		}

		TEST_METHOD(ConstIteratorCopyOperator)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonConstIteratorTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();

			Vector<Foo>::ConstIterator it2;

			it2 = it;

			Assert::AreEqual(it, it2);
		}


		TEST_METHOD(ConstIteratorDeRef)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);

			Assert::AreEqual(first, *(list.cbegin()));

			auto DeRef = [&list] {*(list.cend()); };
			Assert::ExpectException<std::out_of_range>(DeRef);
		}

		TEST_METHOD(ConstIteratorPreFix)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonConstIteratorTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();
			Vector<Foo>::ConstIterator it2 = list.cbegin();
			Vector<Foo>::ConstIterator itOther;

			auto Increase = [&itOther] {++itOther; };
			Assert::ExpectException<std::runtime_error>(Increase);

			++it2;

			Assert::AreEqual(first, *it);
			Assert::AreEqual(second, *it2);

			Assert::AreNotEqual(it, it2);

		}

		TEST_METHOD(ConstIteratorPostFix)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonConstIteratorTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();
			Vector<Foo>::ConstIterator it2 = it++;
			Vector<Foo>::ConstIterator itOther;

			auto Increase = [&itOther] {itOther++; };
			Assert::ExpectException<std::runtime_error>(Increase);


			Assert::AreEqual(second, *it);
			Assert::AreEqual(first, *it2);

			Assert::AreNotEqual(it, it2);
		}

		TEST_METHOD(ConstIteratorEqual)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonConstIteratorTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();
			Vector<Foo>::ConstIterator it2 = list.cbegin();

			Assert::AreEqual(first, *it);
			Assert::AreEqual(first, *it2);

			Assert::AreEqual(it, it2);
		}

		TEST_METHOD(ConstIteratorNotEqual)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			CommonConstIteratorTest(list);
			Vector<Foo>::ConstIterator it = list.cbegin();
			Vector<Foo>::ConstIterator it2 = list.cbegin();

			++it2;

			Assert::AreEqual(first, *it);
			Assert::AreEqual(second, *it2);
			Assert::AreNotEqual(it, it2);

		}





		TEST_METHOD(BeginEnd)
		{
			Vector<Foo> list;


			CommonVectorSetupTest(list);
		
			auto DeRef = [&list] {*(list.end()); };
			Assert::ExpectException<std::out_of_range>(DeRef);

			Vector<Foo>::Iterator begin = list.begin();
			Vector<Foo>::Iterator end = list.end();

			Assert::AreEqual(list.Front(), *begin);
			Assert::AreNotEqual(list.Back(), *begin);



		}

		TEST_METHOD(BeginEndConst)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);
			const Vector<Foo>* ptrList = &list;

			auto DeRef = [&ptrList] {*(ptrList->end()); };
			Assert::ExpectException<std::out_of_range>(DeRef);

			Vector<Foo>::ConstIterator begin = ptrList->begin();
			Vector<Foo>::ConstIterator end = ptrList->end();

			Assert::AreEqual(ptrList->Front(), *begin);
			Assert::AreNotEqual(ptrList->Back(), *begin);



		}

		TEST_METHOD(CBeginEnd)
		{
			Vector<Foo> list;

			CommonVectorSetupTest(list);

			auto DeRef = [&list] {*(list.end()); };
			Assert::ExpectException<std::out_of_range>(DeRef);

			Vector<Foo>::ConstIterator begin = list.cbegin();
			Vector<Foo>::ConstIterator end = list.cend();

			Assert::AreEqual(list.Front(), *begin);
			Assert::AreNotEqual(list.Back(), *begin);


		}

		TEST_METHOD(Find)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);

			Vector<Foo>::Iterator findValue = list.Find(first);

			Assert::AreEqual(first, *findValue);

			findValue = list.Find(100);

			auto NotFound = [&findValue] {*findValue; };
			Assert::ExpectException<std::exception>(NotFound);

			CommonIteratorTest(list);
		}

		TEST_METHOD(FindConst)
		{
			Vector<Foo> list;
			CommonVectorSetupTest(list);

			const Vector<Foo>* ptrList = &list;

			Vector<Foo>::ConstIterator findValue = ptrList->Find(first);

			Assert::AreEqual(first, *findValue);

			findValue = ptrList->Find(100);

			auto NotFound = [&findValue] {*findValue; };
			Assert::ExpectException<std::exception>(NotFound);

			CommonConstIteratorTest(list);
		}

		TEST_METHOD(Remove)
		{
			Vector<Foo> list;

			
			CommonVectorSetupTest(list);

			Vector<Foo>::Iterator broken;
			auto NotRemoved = [&list, &broken] { list.Remove(broken); };
			Assert::ExpectException<std::exception>(NotRemoved);
			Vector<Foo>::Iterator begin = list.begin();
			list.Remove(begin);
			list.Remove(begin);
			list.Remove(begin);


			for (Vector<Foo>::Iterator it = list.begin(); it != list.end(); ++it)
			{
				Assert::AreNotEqual(first, *it);
				Assert::AreNotEqual(second, *it);
			}

			CommonIteratorTest(list);

		}



	private:
		static _CrtMemState _startMemState;
		void CommonVectorSetupTest(Vector<Foo>& list);
		void CommonIteratorTest(Vector<Foo>& list);
		void CommonConstIteratorTest(Vector<Foo>& list);



	};

	_CrtMemState VectorTest::_startMemState;



	void VectorTest::CommonVectorSetupTest(Vector<Foo>& list)
	{
		list.PushBack(first);
		list.PushBack(second);
		list.PushBack(third);

		Assert::AreEqual(first, list.Front());
		Assert::AreEqual(third, list.Back());
		Assert::AreEqual(size_t(3), list.Size());
		Assert::AreEqual(size_t(10), list.Capacity());
	}

	void VectorTest::CommonIteratorTest(Vector<Foo>& list)
	{
		size_t count = 0;
		for (Vector<Foo>::Iterator it = list.begin(); it != list.end(); ++it, ++count)
		{
			it;
		}

		Assert::AreEqual(list.Size(), count);
	}


	void VectorTest::CommonConstIteratorTest(Vector<Foo>& list)
	{
		size_t count = 0;
		for (Vector<Foo>::ConstIterator it = list.cbegin(); it != list.cend(); ++it, ++count)
		{
			it;
		}

		Assert::AreEqual(list.Size(), count);
	}

}
