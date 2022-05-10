#pragma once
#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"
//#include "SList.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework; 
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(SListTest)
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

			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());


			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);


			auto Back = [&list] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(Back);
		}


		TEST_METHOD(MoveConstructor)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);

			SList<Foo> list2 = std::move(list);


			Assert::AreEqual(third, list2.Front());
			Assert::AreEqual(first, list2.Back());
			Assert::AreEqual(size_t(3), list2.Size());


		}


		TEST_METHOD(MoveOperator)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);

			SList<Foo> list2;

			list2 = std::move(list);


			Assert::AreEqual(third, list2.Front());
			Assert::AreEqual(first, list2.Back());
			Assert::AreEqual(size_t(3), list2.Size());

		}

		
		TEST_METHOD(PushFront)
		{
			SList<Foo> list;
			
			list.PushFront(first);
			Assert::AreEqual(first, list.Front());
			Assert::AreEqual(first, list.Back());
			Assert::AreEqual(size_t(1), list.Size());

			list.PushFront(second);
			Assert::AreEqual(second, list.Front());
			Assert::AreEqual(first, list.Back());
			Assert::AreEqual(size_t(2), list.Size());

			list.PushFront(third);
			Assert::AreEqual(third, list.Front());
			Assert::AreEqual(first, list.Back());
			Assert::AreEqual(size_t(3), list.Size());
		}


		TEST_METHOD(PopFront)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);

			list.PopFront();

			Assert::AreEqual(second, list.Front());
			Assert::AreEqual(first, list.Back());
			Assert::AreEqual(size_t(2), list.Size());

			list.PopFront();

			Assert::AreEqual(first, list.Front());
			Assert::AreEqual(first, list.Back());
			Assert::AreEqual(size_t(1), list.Size());

			list.PopFront();
			Assert::AreEqual(size_t(0), list.Size());

			list.PopFront();
			
			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);

		}

		TEST_METHOD(PushBack)
		{
			SList<Foo> list;

			Assert::AreEqual(size_t(0), list.Size());
			
			list.PushBack(first);
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(first, list.Front());
			Assert::AreEqual(first, list.Back());
			
			////Now Second should be in the front
			list.PushBack(second);
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(first, list.Front());
			Assert::AreEqual(second, list.Back());

			list.PushBack(third);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(first, list.Front());
			Assert::AreEqual(third, list.Back());

		}



		TEST_METHOD(PopBack)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);

			list.PopBack();

			Assert::AreEqual(third, list.Front());
			Assert::AreEqual(second, list.Back());
			Assert::AreEqual(size_t(2), list.Size());

			list.PopBack();

			Assert::AreEqual(third, list.Front());
			Assert::AreEqual(third, list.Back());
			Assert::AreEqual(size_t(1), list.Size());

			list.PopBack();
			Assert::AreEqual(size_t(0), list.Size());

			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);
		}


		TEST_METHOD(IsEmptyConst)
		{
			const SList<Foo> list;
			
			Assert::IsTrue(list.IsEmpty());

			SList<Foo> list2;

			list2.PushFront(first);

			const SList<Foo>* constList = &list2;

			Assert::IsFalse(constList->IsEmpty());
		}


		TEST_METHOD(Front)
		{
			SList<Foo> list;
			

			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);
			
			list.PushFront(first);
			Assert::AreEqual(first, list.Front());

			list.PushFront(second);
			Assert::AreEqual(second, list.Front());
			
			list.PushFront(third);
			Assert::AreEqual(third, list.Front());

		}

		TEST_METHOD(FrontConst)
		{
			const SList<Foo> list;


			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);

			SList<Foo> list2;

			list2.PushFront(first);
			list2.PushFront(second);
			list2.PushFront(third);

			const SList<Foo>* constList = &list2;

			Assert::AreEqual(third, constList->Front());



		}

		TEST_METHOD(Back)
		{
			SList<Foo> list;


			auto Back = [&list] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(Back);

			list.PushBack(first);
			Assert::AreEqual(first, list.Back());

			list.PushBack(second);
			Assert::AreEqual(second, list.Back());

			list.PushBack(third);
			Assert::AreEqual(third, list.Back());

		}

		TEST_METHOD(BackConst)
		{
			const SList<Foo> list;

			auto Back = [&list] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(Back);

			SList<Foo> list2;

			list2.PushFront(first);
			list2.PushBack(second);

			const SList<Foo>* constList = &list2;

			Assert::AreEqual(second, constList->Back());


		}



		TEST_METHOD(SizeConst)
		{
			const SList<Foo> list;

			//Get the size when enmpty
			Assert::AreEqual(size_t(0), list.Size());

			SList<Foo> list2;

			CommonSListSetupTest(list2);

			const SList<Foo>* constList = &list2;

			Assert::AreEqual(size_t(3), constList->Size());

		}


		TEST_METHOD(CopyConstructor)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);

			SList<Foo> listCopy = list;
			
			Assert::AreEqual(third, listCopy.Front());
			Assert::AreEqual(first, listCopy.Back());
			Assert::AreEqual(size_t(3), listCopy.Size());
			Assert::AreEqual(list.Front(), listCopy.Front());
			Assert::AreEqual(list.Back(), listCopy.Back());



		}

		TEST_METHOD(CopyOperator)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);

			SList<Foo> listCopy;

			listCopy = list;

			Assert::AreEqual(third, listCopy.Front());
			Assert::AreEqual(first, listCopy.Back());
			Assert::AreEqual(size_t(3), listCopy.Size());
			Assert::AreEqual(list.Front(), listCopy.Front());
			Assert::AreEqual(list.Back(), listCopy.Back());


		}

		TEST_METHOD(ClearList)
		{
			SList<Foo> list;

			CommonSListSetupTest(list);


			list.ClearList();

			Assert::AreEqual(size_t(0), list.Size());

			auto Front = [&list] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(Front);

			
		}


		//Iterators

		TEST_METHOD(Iterator)
		{
			SList<Foo> list;
			Assert::AreEqual(list.begin(),list.end());
			
			CommonSListSetupTest(list);
			
			Assert::AreNotEqual(list.end(), list.begin());
			
			CommonIteratorTest(list);


		}

		TEST_METHOD(ConstIterator)
		{
			SList<Foo> list;
			Assert::AreEqual(list.cend(),list.cbegin());
			CommonSListSetupTest(list);
			Assert::AreNotEqual(list.cend(), list.cbegin());

			CommonConstIteratorTest(list);
		}

		TEST_METHOD(BeginEnd)
		{
			SList<Foo> list;
			Assert::AreEqual(list.end(),list.begin());
			CommonSListSetupTest(list);
			Assert::AreNotEqual(list.end(), list.begin());

			SList<Foo>::Iterator begin = list.begin();
			SList<Foo>::Iterator end = list.end();

			Assert::AreEqual(list.Front(), *begin);
			Assert::AreNotEqual(list.Back(), *begin);

			

		}

		TEST_METHOD(BeginEndConst)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);
			const SList<Foo>* ptrList = &list;

			Assert::AreNotEqual(ptrList->end(), ptrList->begin());

			SList<Foo>::ConstIterator begin = ptrList->begin();
			SList<Foo>::ConstIterator end = ptrList->end();

			Assert::AreEqual(ptrList->Front(), *begin);
			Assert::AreNotEqual(ptrList->Back(), *begin);



		}

		TEST_METHOD(CBeginEnd)
		{
			SList<Foo> list;
			Assert::AreEqual(list.cend(),list.cbegin());
			CommonSListSetupTest(list);
			Assert::AreNotEqual(list.cend(), list.cbegin());

			SList<Foo>::ConstIterator begin = list.cbegin();
			SList<Foo>::ConstIterator end = list.cend();

			Assert::AreEqual(list.Front(), *begin);
			Assert::AreNotEqual(list.Back(), *begin);

			
		}

		TEST_METHOD(InsertAfter)
		{
			SList<Foo> list;
			


			list.InsertAfter(list.begin(), second);

			Assert::AreEqual(second, list.Front());
			Assert::AreEqual(second, *(list.begin()));

			list.InsertAfter(list.begin(), second);

			SList<Foo>::Iterator it = list.begin();

			++it;
			Assert::AreEqual(list.Back(), *it);
			Assert::AreEqual(second, *it);
			Assert::AreEqual(size_t(2), list.Size());
			
			list.PopBack();
			list.PopBack();
			
			
			CommonSListSetupTest(list);
			SList<Foo>::Iterator begin = list.begin();
			list.InsertAfter(begin, first);
			Assert::AreEqual(size_t(4), list.Size());
			
			++begin;
			Assert::AreEqual(first, *begin);
			
			CommonIteratorTest(list);

			SList<Foo>::Iterator test;

			auto Insert = [&list, &test] {list.InsertAfter(test, 10); };
			Assert::ExpectException<std::runtime_error>(Insert);
			


		}

		TEST_METHOD(FindIterator)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);

			SList<Foo>::Iterator findValue = list.Find(first);

			Assert::AreEqual(first, *findValue);

			findValue = list.Find(100);

			
			auto Null = [&findValue] {*findValue; };
			Assert::ExpectException<std::exception>(Null);
			

			CommonIteratorTest(list);
		}

		TEST_METHOD(FindConstIterator)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);

			SList<Foo>::Iterator findValue = list.Find(first);

			Assert::AreEqual(first, *findValue);

			findValue = list.Find(100);

			auto Null = [&findValue] {*findValue; };
			Assert::ExpectException<std::exception>(Null);

			CommonIteratorTest(list);
		}

		TEST_METHOD(Remove)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);

			//list.Remove(first);
			//
			//for (SList<Foo>::Iterator it = list.begin(); it != list.end(); ++it)
			//{
			//	Assert::AreNotEqual(first, *it);
			//}

			CommonIteratorTest(list);
		}


		TEST_METHOD(PreIncrement)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);

			SList<Foo>::Iterator its;


			auto PreInc = [&its] {++its; };
			Assert::ExpectException<std::runtime_error>(PreInc);


			its = list.begin();

			++its;

			Assert::AreEqual(second, *its);


		}


		TEST_METHOD(PreIncrementConst)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);


			SList<Foo>::ConstIterator its;


			auto PreInc = [&its] {++its; };
			Assert::ExpectException<std::runtime_error>(PreInc);


			its = list.cbegin();

			++its;

			Assert::AreEqual(second, *its);
		}


		TEST_METHOD(PostIncrement)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);

			SList<Foo>::Iterator its;


			auto PreInc = [&its] {its++; };
			Assert::ExpectException<std::runtime_error>(PreInc);


			its = list.begin();

			SList<Foo>::Iterator copy = its++;

			
			Assert::AreNotEqual(second, *copy);
			Assert::AreEqual(second, *its);

		}


		TEST_METHOD(PostIncrementConst)
		{
			SList<Foo> list;
			CommonSListSetupTest(list);


			SList<Foo>::ConstIterator its;


			auto PreInc = [&its] {its++; };
			Assert::ExpectException<std::runtime_error>(PreInc);


			its = list.cbegin();

			SList<Foo>::ConstIterator copy = its++;

			Assert::AreNotEqual(second, *copy);
			Assert::AreEqual(second, *its);
		}

		TEST_METHOD(NotEqual)
		{
			SList<Foo> list;
			SList<Foo> list2;
			CommonSListSetupTest(list);
			CommonSListSetupTest(list2);

			SList<Foo>::Iterator begin = list.begin();
			SList<Foo>::Iterator beginlist2 = list2.begin();
			SList<Foo>::Iterator begin2 = list.begin();
			SList<Foo>::Iterator end = list.end();


			Assert::IsTrue(begin != beginlist2);

			++begin;
			++begin2;

			Assert::IsTrue((begin != end));
			Assert::IsFalse((begin != begin2));

			SList<Foo>::Iterator it;
			SList<Foo>::Iterator its;

			auto Null = [&it, &its] {it != its; };
			Assert::ExpectException<std::exception>(Null);


		}


		TEST_METHOD(NotEqualConst)
		{
			SList<Foo> list;
			SList<Foo> list2;
			CommonSListSetupTest(list);
			CommonSListSetupTest(list2);

			SList<Foo>::ConstIterator begin = list.cbegin();
			SList<Foo>::ConstIterator beginlist2 = list2.cbegin();


			SList<Foo>::ConstIterator begin2 = list.cbegin();
			SList<Foo>::ConstIterator end = list.cend();


			Assert::IsTrue(begin != beginlist2);

			++begin;
			++begin2;

			Assert::IsTrue((begin != end));
			Assert::IsFalse((begin != begin2));

			SList<Foo>::ConstIterator it;
			SList<Foo>::ConstIterator its;

			auto Null = [&it, &its] {it != its; };
			Assert::ExpectException<std::exception>(Null);


		}


		TEST_METHOD(Equal)
		{
			SList<Foo> list;
			SList<Foo> list2;
			CommonSListSetupTest(list);
			CommonSListSetupTest(list2);

			SList<Foo>::Iterator begin = list.begin();
			SList<Foo>::Iterator beginlist2 = list2.begin();


			SList<Foo>::Iterator begin2 = list.begin();
			SList<Foo>::Iterator end = list.end();
		
			
			Assert::IsFalse(begin == beginlist2);

			++begin;
			++begin2;

			Assert::IsFalse((begin == end));
			Assert::AreNotEqual(end, begin);
			Assert::IsTrue((begin == begin2));

			SList<Foo>::Iterator it;
			SList<Foo>::Iterator its;

			auto Null = [&it, &its] {it == its; };
			Assert::ExpectException<std::exception>(Null);

		}


		TEST_METHOD(EqualConst)
		{
			SList<Foo> list;
			SList<Foo> list2;
			CommonSListSetupTest(list);
			list2.PushBack(22);
			list2.PushBack(32);

			SList<Foo>::ConstIterator begin = list.cbegin();
			SList<Foo>::ConstIterator beginlist2 = list2.cbegin();


			SList<Foo>::ConstIterator begin2 = list.cbegin();
			SList<Foo>::ConstIterator end = list.cend();


			Assert::IsFalse(begin == beginlist2);

			++begin;
			++begin2;

			Assert::IsFalse((begin == end));
			Assert::AreNotEqual(end, begin);
			Assert::IsTrue((begin == begin2));

			SList<Foo>::ConstIterator it;
			SList<Foo>::ConstIterator its;

			auto Null = [&it, &its] {it == its; };
			Assert::ExpectException<std::exception>(Null);

		}

		TEST_METHOD(Dereference)
		{
			SList<Foo> list;
			

			SList<Foo>::Iterator its = list.begin();

			auto Deref = [&its] {*its; };
			Assert::ExpectException<std::runtime_error>(Deref);

			CommonSListSetupTest(list);
			CommonIteratorTest(list);

			SList<Foo>::Iterator it = list.begin();

			auto Null = [&list] {*(list.end()); };
			Assert::ExpectException<std::exception>(Null);


			Assert::AreEqual(third, *it);
		}


		TEST_METHOD(DereferenceConst)
		{
			SList<Foo> list;


			SList<Foo>::ConstIterator its = list.cbegin();

			auto Deref = [&its] {*its; };
			Assert::ExpectException<std::runtime_error>(Deref);

			CommonSListSetupTest(list);
			CommonConstIteratorTest(list);

			SList<Foo>::ConstIterator it = list.cbegin();
			Assert::AreEqual(third, *it);

			auto Null = [&list] {*(list.cend()); };
			Assert::ExpectException<std::exception>(Null);



		}


	private:
		//Static is not const, Static is persistent and only created once and before any of the methods run
		static _CrtMemState _startMemState;
		void CommonSListSetupTest(SList<Foo>& list);
		void CommonIteratorTest(SList<Foo>& list);
		void CommonConstIteratorTest(SList<Foo>& list);



	};

	_CrtMemState SListTest::_startMemState;

	void SListTest::CommonSListSetupTest(SList<Foo>& list)
	{
		list.PushFront(first);
		list.PushFront(second);
		list.PushFront(third);

		Assert::AreEqual(third, list.Front());
		Assert::AreEqual(first, list.Back());
		Assert::AreEqual(size_t(3), list.Size());
	}
	void SListTest::CommonIteratorTest(SList<Foo>& list)
	{
		
		size_t count = 0;
		for (SList<Foo>::Iterator it = list.begin(); it != list.end(); ++it, ++count)
		{
			it;
		}

		Assert::AreEqual(list.Size(), count);

		Assert::AreNotEqual(list.end(), list.begin());
	}


	void SListTest::CommonConstIteratorTest(SList<Foo>& list)
	{

		size_t count = 0;
		for (SList<Foo>::ConstIterator it = list.cbegin(); it != list.cend(); ++it, ++count)
		{
			it;
		}

		Assert::AreEqual(list.Size(), count);

		Assert::AreNotEqual(list.cend(), list.cbegin());
	}


}
