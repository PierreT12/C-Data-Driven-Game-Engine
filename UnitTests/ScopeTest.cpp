#pragma once
#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;


namespace UnitTests
{
	TEST_CLASS(ScopeTest)
	{
		const std::string hey = "H";
		const std::string bye = "Goodbye";
		const std::string adopt = "Adpoted";

	public:
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
			Scope s;

			Assert::IsNull(s.GetParent());

			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());

		}
		
		//Add in a Scope Check
		TEST_METHOD(CopyConstructor)
		{
			Scope s;

			Datum* d = &s.Append(hey);
			Datum* d2 = &s.Append(bye);
			s.AppendScope(adopt);
			

			*d = 12;
			*d2 = 1.0f;

			Scope s2 = s;

			Datum* adoptFound = &s2.Append(adopt);
			
			Assert::IsTrue(s.Equals(&s2));
			Assert::AreEqual(s.Append(hey).Get<int32_t>(), s2.Append(hey).Get<int32_t>());
			Assert::AreEqual(s.Append(bye).Get<float>(), s2.Append(bye).Get<float>());
			Assert::AreEqual(s.Append(adopt).Type(), s2.Append(adopt).Type());
			Assert::IsTrue(adoptFound == &s2.Append(adopt));

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());


			Assert::IsFalse(s2.IsEmpty());
			Assert::AreEqual(size_t(3), s2.Size());

		}

		TEST_METHOD(CopyAssignment)
		{
			Scope s;
			Scope s2;

			Datum* d = &s.Append(hey);
			Datum* d2 = &s.Append(bye);
			s.AppendScope(adopt);


			*d = 12;
			*d2 = 1.0f;

			Assert::IsFalse(s.Equals(&s2));
			
			s2 = s;


			Datum* adoptFound = &s2.Append(adopt);

			Assert::IsTrue(s.Equals(&s2));
			Assert::AreEqual(s.Append(hey).Get<int32_t>(), s2.Append(hey).Get<int32_t>());
			Assert::AreEqual(s.Append(bye).Get<float>(), s2.Append(bye).Get<float>());
			Assert::AreEqual(s.Append(adopt).Type(), s2.Append(adopt).Type());
			Assert::IsTrue(adoptFound == &s2.Append(adopt));

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());


			Assert::IsFalse(s2.IsEmpty());
			Assert::AreEqual(size_t(3), s2.Size());

		}

		TEST_METHOD(MoveConstructor)
		{
			Scope s;

			std::string childadd = "add";
			s.Append(hey).SetType(DatumTypes::INT);
			s.Append(bye).SetType(DatumTypes::FLOAT);

			Datum heyFound = s.Append(hey);
			Datum byeFound = s.Append(bye);
			Scope* child = &s.AppendScope(adopt);

			Datum* add = &child->Append(childadd);
			
			*add = 14.f;

			Datum adoptFound = s.Append(adopt);

			Scope sMove = std::move(s);


			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());

			Assert::IsFalse(s.Equals(&sMove));
			Assert::AreEqual(heyFound.Type(), sMove.Append(hey).Type());
			Assert::AreEqual(byeFound.Type(), sMove.Append(bye).Type());
			Assert::AreEqual(adoptFound.Type(), sMove.Append(adopt).Type());

			auto [datumOG, indexOG] = sMove.FindContainedScope(child);

			Scope* movedScope;
			movedScope = std::move(child);

			auto [datum, index] = sMove.FindContainedScope(movedScope);


			Assert::AreEqual(size_t(1), movedScope->Size());
			Assert::IsFalse(movedScope->IsEmpty());
			Assert::IsTrue(movedScope->GetParent() == &sMove);
		

			delete movedScope;

		}

		TEST_METHOD(MoveAssignment)
		{
			Scope s;

			std::string childadd = "add";
			s.Append(hey).SetType(DatumTypes::INT);
			s.Append(bye).SetType(DatumTypes::FLOAT);

			Datum heyFound = s.Append(hey);
			Datum byeFound = s.Append(bye);
			Scope* child = &s.AppendScope(adopt);

			Datum* add = &child->Append(childadd);

			*add = 14.f;

			Datum adoptFound = s.Append(adopt);

			Scope sMove;
			sMove = std::move(s);


			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());

			Assert::IsFalse(s.Equals(&sMove));
			Assert::AreEqual(heyFound.Type(), sMove.Append(hey).Type());
			Assert::AreEqual(byeFound.Type(), sMove.Append(bye).Type());
			Assert::AreEqual(adoptFound.Type(), sMove.Append(adopt).Type());

			auto [datumOG, indexOG] = sMove.FindContainedScope(child);

			Scope movedScope;
			movedScope = std::move(*child);

			auto [datum, index] = sMove.FindContainedScope(movedScope);

			Assert::IsTrue(child->IsEmpty());
			Assert::AreEqual(size_t(0), child->Size());

			Assert::AreEqual(size_t(1), movedScope.Size());
			Assert::IsFalse(movedScope.IsEmpty());
			Assert::IsTrue(movedScope.GetParent() == &sMove);

			delete child;
		}

		TEST_METHOD(Append)
		{
			Scope s;

			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());

			Datum * d = &s.Append(hey);
			*d = 12;

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), s.Size());
			Assert::AreEqual(d->Get<int32_t>(), s.Append(hey).Get<int32_t>());
			Assert::AreEqual(d->Type(), s.Append(hey).Type());


		}

		TEST_METHOD(AppendScope)
		{
			Scope s;

			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());

			s.AppendScope(hey);

			Datum* d = &s.Append(hey);

			Datum* d2 = &s.Append(bye);
			*d2 = 12;

			auto appendThrow = [&s] { s.AppendScope("Goodbye"); };
			Assert::ExpectException<std::exception>(appendThrow);
			
			Assert::IsNotNull(d->Get<Scope>().GetParent());
			Assert::AreEqual(d->Type(), s.Append(hey).Type());
			Assert::IsTrue(&d->Get<Scope>() == &s.Append(hey).Get<Scope>());

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(2), s.Size());

		}

	
		TEST_METHOD(Find)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Datum* adoptFound = &s.Append(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);
			adoptFound->SetType(DatumTypes::VEC4);

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());

			Datum* heyFind = s.Find(hey);
			Datum* byeFind = s.Find(bye);
			Datum* adoptFind = s.Find(adopt);

			Assert::IsTrue(heyFound == heyFind);
			Assert::IsTrue(byeFound == byeFind);
			Assert::IsTrue(adoptFound == adoptFind);

			std::string notFound = "NotFound!";

			Datum* notFoundDatum = s.Find(notFound);

			Assert::IsNull(notFoundDatum);





		}


		TEST_METHOD(FindConst)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Datum* adoptFound = &s.Append(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);
			adoptFound->SetType(DatumTypes::VEC4);

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());

			const Scope* cScope = &s;

			const Datum* heyFind = cScope->Find(hey);
			const Datum* byeFind = cScope->Find(bye);
			const Datum* adoptFind = cScope->Find(adopt);

			Assert::IsTrue(heyFound == heyFind);
			Assert::IsTrue(byeFound == byeFind);
			Assert::IsTrue(adoptFound == adoptFind);

			std::string notFound = "NotFound!";

			const Datum* notFoundDatum = cScope->Find(notFound);

			Assert::IsNull(notFoundDatum);





		}




		TEST_METHOD(Search)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Scope* s2 = &s.AppendScope(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);
			

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());

			Datum* found = s2->Search(hey);

			Assert::IsNotNull(found);
			Assert::IsTrue(found == heyFound);


		}

		TEST_METHOD(SearchConst)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Scope* s2 = &s.AppendScope(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);

			const Scope* cScope = s2;

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());

			const Datum* found = cScope->Search(hey);

			Assert::IsNotNull(found);
			Assert::IsTrue(found == heyFound);


		}


		TEST_METHOD(SearchScopeRelavent)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Scope* s2 = &s.AppendScope(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);

			Datum* found = s2->Search(hey, s2);

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());

			Assert::IsNotNull(found);
			Assert::IsTrue(found == heyFound);

		}

		TEST_METHOD(SearchScopeRelaventConst)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Scope* s2 = &s.AppendScope(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);

			const Scope* cScope = s2;

			const Datum* found = cScope->Search(hey, s2);

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(3), s.Size());

			Assert::IsNotNull(found);
			Assert::IsTrue(found == heyFound);

		}

		TEST_METHOD(Adpot)
		{
			Scope s;
			Scope s2;

			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());

		
			Datum* d = &s.Append(hey);
			*d = 12;
		
			auto Self = [ &s] {s.Adopt("adopt", s); };
			Assert::ExpectException<std::exception>(Self);

			auto OtherDatum = [ &s, &s2] {s.Adopt("H", s2); };
			Assert::ExpectException<std::exception>(OtherDatum);

			Scope* childScope = new Scope();

			Assert::IsTrue(childScope->IsEmpty());
			Assert::AreEqual(size_t(0), childScope->Size());

			s.Adopt(adopt, *childScope);

			Assert::IsTrue(childScope == &s.Append(adopt).operator[](0));

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(2), s.Size());
			Assert::IsTrue(childScope->GetParent() == &s);
		}
		
		TEST_METHOD(GetParent)
		{
			Scope s;
			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());
			Assert::IsNull(s.GetParent());
			
			Scope* schild = &s.AppendScope(bye);
			

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), s.Size());
			Assert::IsNotNull(schild->GetParent());
			Assert::IsTrue(schild->GetParent() == &s);

		}

		TEST_METHOD(BracketWrapper)
		{
			Scope s;
			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());
			Datum* d = &s[hey];
			*d = 12;

			Assert::AreEqual(size_t(1), d->Size());

			Assert::AreEqual(d->Get<int32_t>(), s[hey].Get<int32_t>());
			Assert::AreEqual(d->Type(), s[hey].Type());
			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), s.Size());

		}

		TEST_METHOD(BracketIndex)
		{
			Scope s;
			Assert::IsTrue(s.IsEmpty());
			Assert::AreEqual(size_t(0), s.Size());
			Datum* d = &s[hey];
			*d = 12;

			Assert::AreEqual(size_t(1), d->Size());

			int32_t index = 0;
			Assert::AreEqual(d->Get<int32_t>(), s[index].Get<int32_t>());
			Assert::AreEqual(d->Type(), s[index].Type());
			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), s.Size());

		}

		TEST_METHOD(EqualNotEqual)
		{
			Scope s;

			Datum* heyFound = &s.Append(hey);
			Datum* byeFound = &s.Append(bye);
			Datum* adoptFound = &s.Append(adopt);
			heyFound->SetType(DatumTypes::INT);
			byeFound->SetType(DatumTypes::FLOAT);
			adoptFound->SetType(DatumTypes::VEC4);

			Scope s2;
			Datum* heyFound2 = &s2.Append(hey);
			Datum* byeFound2 = &s2.Append(bye);
			Datum* adoptFound2 = &s2.Append(adopt);
			heyFound2->SetType(DatumTypes::FLOAT);
			byeFound2->SetType(DatumTypes::FLOAT);
			adoptFound2->SetType(DatumTypes::FLOAT);

			Assert::IsTrue(s.Equals(&s));

			Assert::IsTrue(!(s.Equals(&s2)));
			Assert::IsFalse((s.Equals(&s2)));
			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(s2.Size(), s.Size());
			Assert::AreEqual(s2.IsEmpty(), s.IsEmpty());



			Assert::IsTrue(s != s2);
			Assert::IsFalse(s == s2);

			Scope* nullScope = nullptr;

			Assert::IsFalse((s.Equals(nullScope)));

		}


		TEST_METHOD(FindContainedScope)
		{
			Scope s;

			Scope* childScope = &s.AppendScope(hey);
			Datum* childDatum = &s.Append(hey);

			Scope* childScope2 = &s.AppendScope(hey);

			Scope* childScope3 = &s.AppendScope(hey);
			
			Scope* childScopeOther = &s.AppendScope(bye);
			Datum* childDatumOther = &s.Append(bye);
			

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(2), s.Size());

			auto [datum, size ] = s.FindContainedScope(*childScope);
			auto [datum2, size2 ] = s.FindContainedScope(*childScope2);
			auto [datum3, size3 ] = s.FindContainedScope(*childScope3);


			auto [datumother, sizeother ] = s.FindContainedScope(*childScopeOther);

			Scope s2;
			auto [datumNotFound, sizeNotFound] = s.FindContainedScope(s2);

			Assert::AreEqual(size_t(0), size);
			Assert::AreEqual(size_t(1), size2);
			Assert::AreEqual(size_t(2), size3);
			Assert::IsTrue(childDatum == datum);
			Assert::IsTrue(childDatum == datum2);
			Assert::IsTrue(childDatum == datum3);
			
			Assert::AreEqual(size_t(0), sizeother);
			Assert::IsTrue(childDatumOther == datumother);


			Assert::AreEqual(size_t(0), sizeNotFound);
			Assert::IsNull(datumNotFound);

		}

		TEST_METHOD(FindContainedScopeConst)
		{
			Scope s;

			Scope* childScope = &s.AppendScope(hey);
			Datum* childDatum = &s.Append(hey);

			Scope* childScope2 = &s.AppendScope(hey);

			Scope* childScope3 = &s.AppendScope(hey);

			Scope* childScopeOther = &s.AppendScope(bye);
			Datum* childDatumOther = &s.Append(bye);

			Scope s2;

			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(2), s.Size());

			const Scope* cScope = &s;

			auto [datum, size] = cScope->FindContainedScope(*childScope);
			auto [datum2, size2] = cScope->FindContainedScope(*childScope2);
			auto [datum3, size3] = cScope->FindContainedScope(*childScope3);


			auto [datumother, sizeother] = cScope->FindContainedScope(*childScopeOther);


			auto [datumNotFound, sizeNotFound] = cScope->FindContainedScope(s2);

			Assert::AreEqual(size_t(0), size);
			Assert::AreEqual(size_t(1), size2);
			Assert::AreEqual(size_t(2), size3);
			Assert::IsTrue(childDatum == datum);
			Assert::IsTrue(childDatum == datum2);
			Assert::IsTrue(childDatum == datum3);

			
			Assert::AreEqual(size_t(0), sizeother);
			Assert::IsTrue(childDatumOther == datumother);


			Assert::AreEqual(size_t(0), sizeNotFound);
			Assert::IsNull(datumNotFound);
		}

		TEST_METHOD(Clear)
		{
			Scope s;

			Scope * childScope = &s.AppendScope(hey);

			Datum* childDatum =	&childScope->Append(bye);
		
			*childDatum = 14;

			Assert::AreEqual(size_t(1), s.Size());
			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), childScope->Size());
			Assert::IsFalse(childScope->IsEmpty());

			s.ClearList();
			
			Assert::AreEqual(size_t(0), s.Size());
			Assert::IsTrue(s.IsEmpty());
			Assert::IsNull(s.Find(bye));
			Assert::IsNull(s.Find(hey));
		}

		TEST_METHOD(Orphan)
		{
			Scope s;
			Scope* childScope = &s.AppendScope(hey);
			
			auto OrphanSelf = [&s] { s.Orphan(s); };
			Assert::ExpectException<std::exception>(OrphanSelf);


			childScope;
			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), s.Size());
			Assert::IsNotNull(childScope->GetParent());
			Assert::IsTrue(childScope->GetParent() == &s);
			
			s.Orphan(*childScope);
			Assert::IsNull(childScope->GetParent());

			delete childScope;
		}


		TEST_METHOD(Ancestors)
		{
			Scope s;
			Scope* childScope = &s.AppendScope(hey);




			Assert::IsFalse(s.IsEmpty());
			Assert::AreEqual(size_t(1), s.Size());
			Assert::IsNotNull(childScope->GetParent());
			Assert::IsTrue(childScope->GetParent() == &s);

			Assert::IsTrue(s.IsAncestorOf(childScope));
			Assert::IsTrue(childScope->IsDescendantOf(s));

		}


	private:
		static _CrtMemState _startMemState;


	};

	_CrtMemState ScopeTest::_startMemState;
}