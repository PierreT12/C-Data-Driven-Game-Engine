#pragma once
#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace FooSupport;

namespace UnitTests
{
	TEST_CLASS(DatumTest)
	{
	public:

		//Uniform initalization
		Foo first{ 10 };
		Foo second{ 20 };
		Foo third{ 30 };


		const int a = 12;
		const float b = 12.f;
		glm::vec4 c = { 10.f, 20.f, 30.f, 40.f };
		glm::mat4 d{ {99.f,86.5f,74.7f,56.f}, {50.6f,41.6f,82.9f,44.9f}, {89.6f,52.3f,52.8f,3.5f}, {6.6f,59.4f,80.6f,34.1f} };
		std::string e = "Datum";
		RTTI* r = &first;
		RTTI* r2 = &second;
		RTTI* r3 = &third;

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

			Datum da;
			Datum d1(DatumTypes::INT, 12);

			auto throwing = [] {Datum d1(DatumTypes::UNKNOWN); };
			Assert::ExpectException<std::exception>(throwing);
			
			Datum d3 = a;
			Datum d4 = b;
			Datum d5 = c;
			Datum d6 = d;
			Datum d7 = e;
			Datum d8 = r;

		}

		TEST_METHOD(CopyConstructor)
		{

			Datum d3 = a;
			Datum d7 = e;

			Datum d4 = d3;

			
			Assert::AreEqual(d3.Type(), d4.Type());
			Assert::AreEqual(d3.Size(), d4.Size());
			
			Assert::IsTrue(d3 == d4);
			Assert::IsFalse(d3 != d4);
			
			Datum d9 = d7;
			
			Assert::AreEqual(d7.Type(), d9.Type());
			Assert::AreEqual(d7.Size(), d9.Size());
			
			Assert::IsTrue(d7 == d9);
			Assert::IsFalse(d7 != d9);


		}

		TEST_METHOD(CopyOperator)
		{
			Datum d3 = a;

			Datum d4;

			d4 = d3;

			Assert::AreEqual(d3.Type(), d4.Type());
			Assert::AreEqual(d3.Size(), d4.Size());

			Assert::IsTrue(d3 == d4);
			Assert::IsFalse(d3 != d4);

			Datum d5;
			Datum d8;
			auto throwingUnknown = [&d5, &d8] { d8 = d5; };
			Assert::ExpectException<std::exception>(throwingUnknown);


		}


		TEST_METHOD(MoveConstructor)
		{
			Datum d3 = a;

			Datum d4 = std::move(d3);


			Assert::AreNotEqual(d3.Type(), d4.Type());

			Assert::AreNotEqual(d3.Size(), d4.Size());




		}


		TEST_METHOD(MoveOperator)
		{
			Datum d3 = a;

			Datum d4;
			
			d4 = std::move(d3);


			Assert::AreNotEqual(d3.Type(), d4.Type());

			Assert::AreNotEqual( d3.Size(),d4.Size());

		}

		TEST_METHOD(AssignmentOverloads)
		{
			Datum d1;
			Datum d2;
			Datum d3;
			Datum d4;
			Datum d5;
			Datum d6;

			d1 = a;
			d2 = b;
			d3 = c;
			d4 = d;
			d5 = e;
			d6 = r;

			Assert::AreEqual(DatumTypes::INT, d1.Type());
			Assert::AreEqual(DatumTypes::FLOAT, d2.Type());
			Assert::AreEqual(DatumTypes::VEC4, d3.Type());
			Assert::AreEqual(DatumTypes::MAT4, d4.Type());
			Assert::AreEqual(DatumTypes::STRING, d5.Type());
			Assert::AreEqual(DatumTypes::POINTER, d6.Type());

			RTTI* test = &first;

			auto throwingint = [&d1, &test] { d1 = test; };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&d2] {d2 = 10; };
			Assert::ExpectException<std::exception>(throwingfloat);

			std::string temp = "Temp";
			auto throwingvec = [&d3, &temp] {d3 = temp;  };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&d4] { d4 = glm::vec4{ 10.f, 20.f, 30.f, 40.f }; };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&d5] {d5 = glm::mat4{ {99.f,86.5f,74.7f,56.f}, {50.6f,41.6f,82.9f,44.9f}, {89.6f,52.3f,52.8f,3.5f}, {6.6f,59.4f,80.6f,34.1f} };  };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&d6] { d6 = 14.f;  };
			Assert::ExpectException<std::exception>(throwingRTTI);



		}


		TEST_METHOD(PushBack)
		{
			Datum da[7];


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);



			auto throwingint = [&da] { da[1].PushBack(12); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[4].PushBack(12.f); };
			Assert::ExpectException<std::exception>(throwingfloat);
			
			auto throwingvec = [&da] { da[5].PushBack(glm::vec4{ 10.f, 20.f, 30.f, 40.f }); };
			Assert::ExpectException<std::exception>(throwingvec);
			
			auto throwingmat = [&da] { da[2].PushBack(glm::mat4{ {99.f,86.5f,74.7f,56.f}, {50.6f,41.6f,82.9f,44.9f}, {89.6f,52.3f,52.8f,3.5f}, {6.6f,59.4f,80.6f,34.1f} }); };
			Assert::ExpectException<std::exception>(throwingmat);
			
			auto throwingstring = [&da] { da[3].PushBack("Datum"); };
			Assert::ExpectException<std::exception>(throwingstring);

			RTTI* test = &first;
			auto throwingRTTI = [&da, &test] { da[0].PushBack(test); };
			Assert::ExpectException<std::exception>(throwingRTTI);

			Datum da2[6];

			da2[0].PushBack(12);
			da2[1].PushBack(12.f);
			da2[2].PushBack(glm::vec4{ 10.f, 20.f, 30.f, 40.f });
			da2[3].PushBack(glm::mat4{ {99.f,86.5f,74.7f,56.f}, {50.6f,41.6f,82.9f,44.9f}, {89.6f,52.3f,52.8f,3.5f}, {6.6f,59.4f,80.6f,34.1f} });
			da2[4].PushBack("Datum");
			da2[5].PushBack(test);

			Assert::AreEqual(DatumTypes::INT, da2[0].Type());
			Assert::AreEqual(DatumTypes::FLOAT, da2[1].Type());
			Assert::AreEqual(DatumTypes::VEC4, da2[2].Type());
			Assert::AreEqual(DatumTypes::MAT4, da2[3].Type());
			Assert::AreEqual(DatumTypes::STRING, da2[4].Type());
			Assert::AreEqual(DatumTypes::POINTER, da2[5].Type());


		}



		TEST_METHOD(PopBack)
		{
			Datum da[7];

			auto throwingint = [&da] { da[0].PopBack(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].PopBack(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].PopBack(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].PopBack(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].PopBack(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].PopBack(); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);
		}



		TEST_METHOD(Front)
		{
			Datum da[7];



			auto throwingint = [&da] { da[0].Front<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].Front<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].Front<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].Front<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].Front<std::string>(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].Front<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingRTTI);



			CommonDatumTest(da[0], DatumTypes::INT);

			Assert::AreEqual(DatumTypes::INT, da[0].Type());

			CommonDatumTest(da[1], DatumTypes::FLOAT);

			Assert::AreEqual(DatumTypes::FLOAT, da[1].Type());

			CommonDatumTest(da[2], DatumTypes::VEC4);

			Assert::AreEqual(DatumTypes::VEC4, da[2].Type());

			CommonDatumTest(da[3], DatumTypes::MAT4);

			Assert::AreEqual(DatumTypes::MAT4, da[3].Type());

			CommonDatumTest(da[4], DatumTypes::STRING);

			Assert::AreEqual(DatumTypes::STRING, da[4].Type());

			CommonDatumTest(da[5], DatumTypes::POINTER);

			Assert::AreEqual(DatumTypes::POINTER, da[5].Type());

			CommonDatumTest(da[6], DatumTypes::UNKNOWN);
			
			auto throwingint2 = [&da] { da[4].Front<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da] { da[3].Front<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da] { da[0].Front<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da] { da[1].Front<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da] {da[2].Front<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da] {da[5].Front<std::string>(); };
			Assert::ExpectException<std::exception>(throwingRTTI2);


		}

		TEST_METHOD(FrontConst)
		{
			Datum const da[7];



			auto throwingint = [&da] { da[0].Front<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].Front<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].Front<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].Front<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].Front<std::string>(); };
			Assert::ExpectException<std::exception>(throwingstring);
			
			auto throwingRTTI = [&da] {da[5].Front<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingRTTI);

			Datum d2[7];

			CommonDatumTest(d2[0], DatumTypes::INT);

			Assert::AreEqual(DatumTypes::INT, d2[0].Type());

			CommonDatumTest(d2[1], DatumTypes::FLOAT);

			Assert::AreEqual(DatumTypes::FLOAT, d2[1].Type());

			CommonDatumTest(d2[2], DatumTypes::VEC4);

			Assert::AreEqual(DatumTypes::VEC4, d2[2].Type());

			CommonDatumTest(d2[3], DatumTypes::MAT4);

			Assert::AreEqual(DatumTypes::MAT4, d2[3].Type());

			CommonDatumTest(d2[4], DatumTypes::STRING);

			Assert::AreEqual(DatumTypes::STRING, d2[4].Type());

			CommonDatumTest(d2[5], DatumTypes::POINTER);

			Assert::AreEqual(DatumTypes::POINTER, d2[5].Type());

			CommonDatumTest(d2[6], DatumTypes::UNKNOWN);


			const Datum* da1 = &d2[0];
			const Datum* da2 = &d2[1];
			const Datum* da3 = &d2[2];
			const Datum* da4 = &d2[3];
			const Datum* da5 = &d2[4];
			const Datum* da6 = &d2[5];

			Assert::AreEqual(d2[0].Front<int32_t>(), da1->Front<int32_t>());
			Assert::AreEqual(d2[1].Front<float>(), da2->Front<float>());
			Assert::AreEqual(d2[2].Front<glm::vec4>(), da3->Front<glm::vec4>());
			Assert::AreEqual(d2[3].Front<glm::mat4>(), da4->Front<glm::mat4>());
			Assert::AreEqual(d2[4].Front<std::string>(), da5->Front<std::string>());
			Assert::AreEqual(d2[5].Front<RTTI*>()->ToString(), da6->Front<RTTI*>()->ToString());

			auto throwingint2 = [&da1] { da1->Front<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da2] { da2->Front<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da3] { da3->Front<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da4] { da4->Front<float>(); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da5] {da5->Front<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da6] {da6->Front<std::string>(); };
			Assert::ExpectException<std::exception>(throwingRTTI2);

		}

		TEST_METHOD(Back)
		{
			Datum da[7];



			auto throwingint = [&da] { da[0].Back<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint);
			
			auto throwingfloat = [&da] { da[1].Back<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat);
			
			auto throwingvec = [&da] { da[2].Back<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec);
			
			auto throwingmat = [&da] { da[3].Back<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat);
			
			auto throwingstring = [&da] {da[4].Back<std::string>(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].Back<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);

			Assert::AreEqual(DatumTypes::INT, da[0].Type());

			CommonDatumTest(da[1], DatumTypes::FLOAT);

			Assert::AreEqual(DatumTypes::FLOAT, da[1].Type());

			CommonDatumTest(da[2], DatumTypes::VEC4);

			Assert::AreEqual(DatumTypes::VEC4, da[2].Type());

			CommonDatumTest(da[3], DatumTypes::MAT4);

			Assert::AreEqual(DatumTypes::MAT4, da[3].Type());

			CommonDatumTest(da[4], DatumTypes::STRING);

			Assert::AreEqual(DatumTypes::STRING, da[4].Type());

			CommonDatumTest(da[5], DatumTypes::POINTER);

			Assert::AreEqual(DatumTypes::POINTER, da[5].Type());

			CommonDatumTest(da[6], DatumTypes::UNKNOWN);

			auto throwingint2 = [&da] { da[4].Back<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint2);
			
			auto throwingfloat2 = [&da] { da[3].Back<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat2);
			
			auto throwingvec2 = [&da] { da[0].Back<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec2);
			
			auto throwingmat2 = [&da] { da[1].Back<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat2);
			
			auto throwingstring2 = [&da] {da[2].Back<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da] {da[5].Back<std::string>(); };
			Assert::ExpectException<std::exception>(throwingRTTI2);

		}

		TEST_METHOD(BackConst)
		{
			Datum const da[7];



			auto throwingint = [&da] { da[0].Back<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].Back<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].Back<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].Back<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].Back<std::string>(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].Back<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingRTTI);

			Datum d2[7];

			CommonDatumTest(d2[0], DatumTypes::INT);

			Assert::AreEqual(DatumTypes::INT, d2[0].Type());

			CommonDatumTest(d2[1], DatumTypes::FLOAT);

			Assert::AreEqual(DatumTypes::FLOAT, d2[1].Type());

			CommonDatumTest(d2[2], DatumTypes::VEC4);

			Assert::AreEqual(DatumTypes::VEC4, d2[2].Type());

			CommonDatumTest(d2[3], DatumTypes::MAT4);

			Assert::AreEqual(DatumTypes::MAT4, d2[3].Type());

			CommonDatumTest(d2[4], DatumTypes::STRING);

			Assert::AreEqual(DatumTypes::STRING, d2[4].Type());

			CommonDatumTest(d2[5], DatumTypes::POINTER);

			Assert::AreEqual(DatumTypes::POINTER, d2[5].Type());

			CommonDatumTest(d2[6], DatumTypes::UNKNOWN);


			const Datum* da1 = &d2[0];
			const Datum* da2 = &d2[1];
			const Datum* da3 = &d2[2];
			const Datum* da4 = &d2[3];
			const Datum* da5 = &d2[4];
			const Datum* da6 = &d2[5];

			Assert::AreEqual(d2[0].Back<int32_t>(), da1->Back<int32_t>());
			Assert::AreEqual(d2[1].Back<float>(), da2->Back<float>());
			Assert::AreEqual(d2[2].Back<glm::vec4>(), da3->Back<glm::vec4>());
			Assert::AreEqual(d2[3].Back<glm::mat4>(), da4->Back<glm::mat4>());
			Assert::AreEqual(d2[4].Back<std::string>(), da5->Back<std::string>());
			Assert::AreEqual(d2[5].Back<RTTI*>()->ToString(), da6->Back<RTTI*>()->ToString());

			auto throwingint2 = [&da1] { da1->Back<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da2] { da2->Back<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da3] { da3->Back<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da4] { da4->Back<float>(); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da5] {da5->Back<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da6] {da6->Back<std::string>(); };
			Assert::ExpectException<std::exception>(throwingRTTI2);

		}


		TEST_METHOD(AreEqual)
		{
			Datum d3 = a;

			

			Datum d4 = d3;

			Datum d7;
			Datum d8 = 22;

			Datum dstring1 = "Hello";
			Datum dstring2 = "GoodBye";


			CommonDatumTest(d7, DatumTypes::FLOAT);

			Assert::IsTrue(d7 != d4);
			Assert::IsFalse(d7 == d4);

			Assert::IsTrue(d8 != d4);
			Assert::IsFalse(d8 == d4);
			
			Assert::AreEqual(d3.Type(), d4.Type());
			Assert::AreEqual(d3.Size(), d4.Size());
			
			Assert::IsTrue(d3 == d4);
			Assert::IsFalse(d3 != d4);
			
			
			Assert::IsTrue(dstring1 != dstring2);
			Assert::IsFalse(dstring1 == dstring2);
		}

		


		TEST_METHOD(Size)
		{
			Datum d3 = a;

			Assert::AreEqual(size_t(1), d3.Size());

		}

		TEST_METHOD(ReSize)
		{
			
			Datum dx;
			Datum dstring;

			auto throwingUnknown = [&dx] { dx.Resize(100); };
			Assert::ExpectException<std::exception>(throwingUnknown);
			
			CommonDatumTest(dx, DatumTypes::INT);
			CommonDatumTest(dstring, DatumTypes::STRING);

			std::string strfront = "One";

			 dx.Resize(1);
			 dstring.Resize(1);
			
			
			 Assert::AreEqual(size_t(1), dx.Size());
			 Assert::AreEqual(size_t(1), dstring.Size());

			 Assert::AreEqual(10, dx.Front<int32_t>());
			 Assert::AreEqual(strfront, dstring.Front<std::string>());

			 dx.Resize(100);
			 dstring.Resize(100);
			 
			 Assert::AreEqual(size_t(100), dx.Size());
			 Assert::AreEqual(size_t(100), dstring.Size());
			 
			 Assert::AreEqual(10, dx.Front<int32_t>());
			 Assert::AreEqual(strfront, dstring.Front<std::string>());

		}

		TEST_METHOD(SetStorage)
		{
			int32_t intptr[] = { 1, 2, 3 };

			float floatptr[] = { 10.f, 20.f, 30.f };
			glm::vec4 vec4ptr[] = { {129.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f} };

			glm::mat4 mat4ptr[] = { { {84.22f,37.66f,23.09f,38.36f}, {57.81f,87.94f,69.03f,45.73f}, {71.59f,88.98f,51.1f,24.84f}, {23.91f,33.78f,81.44f,74.81f} },
									{ {42.89f,91.86f,35.62f,53.33f}, {63.26f,82.53f,81.34f,56.88f}, {37.93f,6.91f,73.98f,16.16f}, {78.16f,17.25f,82.91f,41.69f} },
									{ {129.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f}, {12.7f,83.5f,66.8f,43.3f} } };
		
			std::string stringptr[] = { "Datum", "Scope", "RandomString"};

			RTTI* RTTIptr[] = { r, r2, r3 };


			int32_t* finalIntPtr = intptr;
			float* finalFloatPtr = floatptr;
			glm::vec4* finalVec4Ptr = vec4ptr;
			glm::mat4* finalMat4Ptr = mat4ptr;
			std::string* finalStringPtr = stringptr;
			RTTI** finalRTTIPtr = RTTIptr;


			Datum d1;
			Datum d2;
			Datum d3;
			Datum d4;
			Datum d5;
			Datum d6;

			d1.SetStorage(finalIntPtr, 3);
			d2.SetStorage(finalFloatPtr, 3);
			d3.SetStorage(finalVec4Ptr, 3);
			d4.SetStorage(finalMat4Ptr, 3);
			d5.SetStorage(finalStringPtr, 3);
			d6.SetStorage(finalRTTIPtr, 3);

			Assert::AreEqual(size_t(3), d1.Size());
			Assert::AreEqual(size_t(3), d2.Size());
			Assert::AreEqual(size_t(3), d3.Size());
			Assert::AreEqual(size_t(3), d4.Size());
			Assert::AreEqual(size_t(3), d5.Size());
			Assert::AreEqual(size_t(3), d6.Size());



			auto throwingint = [&d1, &finalFloatPtr] { d1.SetStorage(finalFloatPtr, 3); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&d2, &finalStringPtr] {d2.SetStorage(finalStringPtr, 3); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&d3, &finalMat4Ptr] { d3.SetStorage(finalMat4Ptr, 3); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&d4, &finalVec4Ptr] { d4.SetStorage(finalVec4Ptr, 3); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&d5,&finalRTTIPtr] { d5.SetStorage(finalRTTIPtr, 3); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&d6, &finalIntPtr] { d6.SetStorage(finalIntPtr, 3); };
			Assert::ExpectException<std::exception>(throwingRTTI);

			

			Datum dx  = d1;
			Datum dx2 = d2;
			Datum dx3 = d3;
			Datum dx4 = d4;
			Datum dx5 = d5;
			Datum dx6 = d6;
			Datum dx7;


			auto tempint = 12;
			auto tempfloat = 12.f;
			auto tempvec4 = glm::vec4{ 999.f,86.5f,74.7f,56.f };
			auto tempmat4 = glm::mat4{ {129.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f}, {12.7f,83.5f,66.8f,43.3f} };
			std::string tempstring = "Datum";
			RTTI* tempRTTI = &first;

			Assert::AreEqual(size_t(3), dx.Size());
			Assert::AreEqual(size_t(3), dx2.Size());
			Assert::AreEqual(size_t(3), dx3.Size());
			Assert::AreEqual(size_t(3), dx4.Size());
			Assert::AreEqual(size_t(3), dx5.Size());
			Assert::AreEqual(size_t(3), dx6.Size());



			Assert::AreEqual(d1.Front<int32_t>() , dx.Front<int32_t>());

			auto pushbackExternalInt = [&dx] { dx.PushBack(10); };
			Assert::ExpectException<std::exception>(pushbackExternalInt);

			auto pushbackExternalFloat = [&dx] { dx.PushBack(10.f); };
			Assert::ExpectException<std::exception>(pushbackExternalFloat);

			auto pushbackExternalVec4 = [&dx, &tempvec4] { dx.PushBack(tempvec4); };
			Assert::ExpectException<std::exception>(pushbackExternalVec4);

			auto pushbackExternalMat4 = [&dx, &tempmat4] { dx.PushBack(tempmat4); };
			Assert::ExpectException<std::exception>(pushbackExternalMat4);

			auto pushbackExternalString = [&dx, &tempstring] { dx.PushBack(tempstring); };
			Assert::ExpectException<std::exception>(pushbackExternalString);

			auto pushbackExternalPointer = [&dx, tempRTTI] { dx.PushBack(tempRTTI); };
			Assert::ExpectException<std::exception>(pushbackExternalPointer);




			auto resizeExternal = [&dx] { dx.Resize(100); };
			Assert::ExpectException<std::exception>(resizeExternal);

			auto reserveExternal = [&dx] { dx.Reserve(100);  };
			Assert::ExpectException<std::exception>(reserveExternal);


			dx7 = d1;

			Assert::AreEqual(size_t(3), dx7.Size());



		

			auto removeThrowingint = [&d1, &tempint] { d1.Remove(tempint); };
			Assert::ExpectException<std::exception>(removeThrowingint);

			auto removeThrowingfloat = [&d2, &tempfloat] { d2.Remove(tempfloat); };
			Assert::ExpectException<std::exception>(removeThrowingfloat);

			auto removeThrowingvec = [&d3, &tempvec4] { d3.Remove(tempvec4); };
			Assert::ExpectException<std::exception>(removeThrowingvec);

			auto removeThrowingmat = [&d4, &tempmat4] { d4.Remove(tempmat4); };
			Assert::ExpectException<std::exception>(removeThrowingmat);

			auto removeThrowingstring = [&d5, &tempstring] {d5.Remove(tempstring); };
			Assert::ExpectException<std::exception>(removeThrowingstring);

			auto removeThrowingRTTI = [&d6, tempRTTI] {d6.Remove(tempRTTI); };
			Assert::ExpectException<std::exception>(removeThrowingRTTI);


			auto removeThrowingint2 = [&d1] { d1.RemoveAt(100); };
			Assert::ExpectException<std::exception>(removeThrowingint2);


		}


		TEST_METHOD(Set)
		{

			auto tempint = 12;
			auto tempfloat = 12.f;
			auto tempvec4 = glm::vec4{ 999.f,86.5f,74.7f,56.f };
			auto tempmat4 = glm::mat4{ {129.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f}, {12.7f,83.5f,66.8f,43.3f} };
			std::string tempstring = "Datum";
			RTTI* tempRTTI = &first;

			Datum da[7];

			auto throwingint = [&da, &tempint] { da[0].Set(tempint); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da, &tempfloat] { da[1].Set(tempfloat); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da, &tempvec4] { da[2].Set(tempvec4); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da,&tempmat4] { da[3].Set(tempmat4); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da, &tempstring] {da[4].Set(tempstring); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da, tempRTTI] {da[5].Set(tempRTTI); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);

			auto throwingint2 = [&da, &tempint] {da[0].Set(tempint, 200); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da, &tempfloat] { da[1].Set(tempfloat, 200); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da, &tempvec4] { da[2].Set(tempvec4, 200); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da, &tempmat4] { da[3].Set(tempmat4, 200); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da, &tempstring] {da[4].Set(tempstring, 200); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da, tempRTTI] {da[5].Set(tempRTTI, 200); };
			Assert::ExpectException<std::exception>(throwingRTTI2);


			da[0].Set(tempint);
			da[1].Set(tempfloat);
			da[2].Set(tempvec4);
			da[3].Set(tempmat4);
			//da[4].Set(tempstring);
			da[5].Set(tempRTTI);


			Assert::AreEqual(tempint, da[0].Front<int32_t>());
			Assert::AreEqual(tempfloat, da[1].Front<float>());
			Assert::AreEqual(tempvec4, da[2].Front<glm::vec4>());
			Assert::AreEqual(tempmat4, da[3].Front<glm::mat4>());
			//Assert::AreEqual(tempstring.c_str(), da[4].Front<std::string>().c_str());
			Assert::AreEqual(tempRTTI->ToString(), da[5].Front<RTTI*>()->ToString());


		}

		TEST_METHOD(Get)
		{

			Datum da[7];
			
			auto throwingint = [&da] { da[0].Get<int32_t>(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].Get<float>(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].Get<glm::vec4>(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].Get<glm::mat4>(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].Get<std::string>(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].Get<RTTI*>(); };
			Assert::ExpectException<std::exception>(throwingRTTI);




			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);


			auto throwingint2 = [&da] { da[0].Get<int32_t>(200); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da] { da[1].Get<float>(200); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da] { da[2].Get<glm::vec4>(200); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da] { da[3].Get<glm::mat4>(200); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da] {da[4].Get<std::string>(200); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da] {da[5].Get<RTTI*>(200); };
			Assert::ExpectException<std::exception>(throwingRTTI2);

			Assert::AreEqual(da[0].Front<int32_t>(), da[0].Get<int32_t>());
			Assert::AreEqual(da[1].Front<float>(),   da[1].Get<float>());
			Assert::AreEqual(da[2].Front<glm::vec4>(), da[2].Get<glm::vec4>());
			Assert::AreEqual(da[3].Front<glm::mat4>(), da[3].Get<glm::mat4>());
			Assert::AreEqual(da[4].Front<std::string>(), da[4].Get<std::string>());
			Assert::AreEqual(da[5].Front<RTTI*>()->ToString(), da[5].Get<RTTI*>()->ToString());

		}

		TEST_METHOD(Reserve)
		{
			Datum d4;

			auto throwingUnknown = [&d4] { d4.Reserve(20); };
			Assert::ExpectException<std::exception>(throwingUnknown);

			d4 = 10;

			d4.Reserve(20);

			Assert::AreEqual(size_t(1), d4.Size());
			Assert::AreEqual(DatumTypes::INT, d4.Type());
		}

		TEST_METHOD(ClearList)
		{
			Datum da;
			CommonDatumTest(da, DatumTypes::INT);

			da.ClearList();


		}

		TEST_METHOD(SetFromString)
		{
			std::string  tempint = "12";
			std::string  tempfloat = "12.0";
			std::string  tempvec4 = "12.0 13.0 14.0 15.0";
			std::string  tempmat4 = "12.0 13.0 14.0 15.0 12.0 13.0 14.0 15.0 12.0 13.0 14.0 15.0 12.0 13.0 14.0 15.0";
			std::string tempstring = "Datum";


			Datum da[7];

			//auto throwingint = [&da] { da[0].SetFromString("1000"); };
			//Assert::ExpectException<std::exception>(throwingint);
			//
			//auto throwingfloat = [&da] { da[1].SetFromString("1000"); };
			//Assert::ExpectException<std::exception>(throwingfloat);
			//
			//auto throwingvec = [&da] { da[2].SetFromString("1000"); };
			//Assert::ExpectException<std::exception>(throwingvec);
			//
			//auto throwingmat = [&da] { da[3].SetFromString("1000"); };
			//Assert::ExpectException<std::exception>(throwingmat);
			//
			//auto throwingstring = [&da] {da[4].SetFromString("1000"); };
			//Assert::ExpectException<std::exception>(throwingstring);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);


			da[0].SetFromString(tempint);
			da[1].SetFromString(tempfloat);
			da[2].SetFromString(tempvec4);
			da[3].SetFromString(tempmat4);
			//da[4].SetFromString(tempstring);
			
			Assert::AreEqual(12, da[0].Front<int32_t>());
			Assert::AreEqual(12.f, da[1].Front<float>());
			Assert::AreEqual(glm::vec4{ 12.0, 13.0, 14.0, 15.0 }, da[2].Front<glm::vec4>());
			Assert::AreEqual(glm::mat4 {{12.f, 13.f, 14.f, 15.f}, {12.f ,13.f, 14.f,15.f}, {12.f, 13.f, 14.f, 15.f}, {12.f, 13.f, 14.f, 15.f} }, da[3].Front<glm::mat4>());
			//Assert::AreEqual(tempstring.c_str(), da[4].Front<std::string>().c_str());


		}

		
		TEST_METHOD(ToString)
		{
			Datum da[7];

			auto throwingint = [&da] { da[0].ToString(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].ToString(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].ToString(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].ToString(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].ToString(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].ToString(); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);


			auto throwingint2 = [&da] { da[0].ToString(200); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da] { da[1].ToString(200); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da] { da[2].ToString(200); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da] { da[3].ToString(200); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da] {da[4].ToString(200); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da] {da[5].ToString(200); };
			Assert::ExpectException<std::exception>(throwingRTTI2);
			
			std::string vec4case = "10.000000 20.000000 30.000000 40.000000";
			std::string mat4case = "99.000000 86.500000 74.699997 56.000000 50.599998 41.599998 82.900002 44.900002 89.599998 52.299999 52.799999 3.500000 6.600000 59.400002 80.599998 34.099998";

			Assert::AreEqual(std::to_string(da[0].Front<int32_t>()), da[0].ToString());
			Assert::AreEqual(std::to_string(da[1].Front<float>()), da[1].ToString());
			Assert::AreEqual(vec4case, da[2].ToString());
			Assert::AreEqual(mat4case, da[3].ToString());
			Assert::AreEqual(da[4].Front<std::string>().c_str(), da[4].ToString().c_str());
			Assert::AreEqual(da[5].Front<RTTI*>()->ToString(), da[5].ToString());


		}

		TEST_METHOD(Type)
		{
			Datum da;

			CommonDatumTest(da, DatumTypes::INT);

			Assert::AreEqual(DatumTypes::INT, da.Type());


		}

		TEST_METHOD(SetType)
		{
			Datum da;

			CommonDatumTest(da, DatumTypes::INT);

			auto throwingUnknown = [&da] { da.SetType(DatumTypes::UNKNOWN); };
			Assert::ExpectException<std::exception>(throwingUnknown);
		}
		

		TEST_METHOD(Find)
		{
			auto tempint = 12;
			auto tempfloat = 12.f;
			auto tempvec4 = glm::vec4{ 999.f,86.5f,74.7f,56.f };
			auto tempmat4 = glm::mat4{ {129.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f}, {12.7f,83.5f,66.8f,43.3f} };
			std::string tempstring = "Datum";
			RTTI* tempRTTI = &first;

			Datum da[7];

			auto throwingint = [&da, &tempint] { da[0].Find(tempint); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da, &tempfloat] { da[1].Find(tempfloat); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da, &tempvec4] { da[2].Find(tempvec4); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da, &tempmat4] { da[3].Find(tempmat4); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da, &tempstring] {da[4].Find(tempstring); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da, tempRTTI] {da[5].Find(tempRTTI); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);


			Assert::IsTrue(da[0].Find(20).second);
			Assert::IsTrue(da[1].Find(20.f).second);
			Assert::IsTrue(da[2].Find(glm::vec4{ 50.f, 60.f, 70.f, 80.f }).second);
			Assert::IsTrue(da[3].Find(glm::mat4{ {12.f, 13.f, 14.f, 15.f}, {12.f ,13.f, 14.f,15.f}, {12.f, 13.f, 14.f, 15.f}, {12.f, 13.f, 14.f, 15.f} }).second);
			Assert::IsTrue(da[4].Find("One").second);
			Assert::IsTrue(da[5].Find(r).second);

			Foo notfound = 1000;

			RTTI * not = &notfound;

			Assert::IsFalse(da[0].Find(tempint).second);
			Assert::IsFalse(da[1].Find(tempfloat).second);
			Assert::IsFalse(da[2].Find(tempvec4).second);
			Assert::IsFalse(da[3].Find(tempmat4).second);
			Assert::IsFalse(da[4].Find(tempstring).second);
			Assert::IsFalse(da[5].Find(not).second);


		}

		TEST_METHOD(Remove)
		{
			auto tempint = 12;
			auto tempfloat = 12.f;
			auto tempvec4 = glm::vec4{ 999.f,86.5f,74.7f,56.f };
			auto tempmat4 = glm::mat4{ {129.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f}, {12.7f,83.5f,66.8f,43.3f} };
			std::string tempstring = "Datum";
			RTTI* tempRTTI = &first;

			Datum da[7];

			auto throwingint = [&da, &tempint] { da[0].Remove(tempint); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da, &tempfloat] { da[1].Remove(tempfloat); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da, &tempvec4] { da[2].Remove(tempvec4); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da, &tempmat4] { da[3].Remove(tempmat4); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da, &tempstring] {da[4].Remove(tempstring); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da, tempRTTI] {da[5].Remove(tempRTTI); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);


			Assert::IsTrue(da[0].Remove(20));
			Assert::IsTrue(da[1].Remove(20.f));
			Assert::IsTrue(da[2].Remove(glm::vec4{ 50.f, 60.f, 70.f, 80.f }));
			Assert::IsTrue(da[3].Remove(glm::mat4{ {12.f, 13.f, 14.f, 15.f}, {12.f ,13.f, 14.f,15.f}, {12.f, 13.f, 14.f, 15.f}, {12.f, 13.f, 14.f, 15.f} }));
			Assert::IsTrue(da[4].Remove("One"));
			Assert::IsTrue(da[5].Remove(r));

			Assert::AreEqual(size_t(2), da[0].Size());
			Assert::AreEqual(size_t(2), da[1].Size());
			Assert::AreEqual(size_t(2), da[2].Size());
			Assert::AreEqual(size_t(2), da[3].Size());
			Assert::AreEqual(size_t(2), da[4].Size());
			Assert::AreEqual(size_t(2), da[5].Size());

			Foo notfound = 1000;

			RTTI * not = &notfound;

			Assert::IsFalse(da[0].Remove(tempint));
			Assert::IsFalse(da[1].Remove(tempfloat));
			Assert::IsFalse(da[2].Remove(tempvec4));
			Assert::IsFalse(da[3].Remove(tempmat4));
			Assert::IsFalse(da[4].Remove(tempstring));
			Assert::IsFalse(da[5].Remove(not));



		}

		TEST_METHOD(RemoveAt)
		{

			Datum da[7];

			auto throwingint = [&da] { da[0].RemoveAt(); };
			Assert::ExpectException<std::exception>(throwingint);

			auto throwingfloat = [&da] { da[1].RemoveAt(); };
			Assert::ExpectException<std::exception>(throwingfloat);

			auto throwingvec = [&da] { da[2].RemoveAt(); };
			Assert::ExpectException<std::exception>(throwingvec);

			auto throwingmat = [&da] { da[3].RemoveAt(); };
			Assert::ExpectException<std::exception>(throwingmat);

			auto throwingstring = [&da] {da[4].RemoveAt(); };
			Assert::ExpectException<std::exception>(throwingstring);

			auto throwingRTTI = [&da] {da[5].RemoveAt(); };
			Assert::ExpectException<std::exception>(throwingRTTI);


			CommonDatumTest(da[0], DatumTypes::INT);
			CommonDatumTest(da[1], DatumTypes::FLOAT);
			CommonDatumTest(da[2], DatumTypes::VEC4);
			CommonDatumTest(da[3], DatumTypes::MAT4);
			CommonDatumTest(da[4], DatumTypes::STRING);
			CommonDatumTest(da[5], DatumTypes::POINTER);
			CommonDatumTest(da[6], DatumTypes::UNKNOWN);



			auto throwingint2 = [&da] { da[0].RemoveAt(100); };
			Assert::ExpectException<std::exception>(throwingint2);

			auto throwingfloat2 = [&da] { da[1].RemoveAt(100); };
			Assert::ExpectException<std::exception>(throwingfloat2);

			auto throwingvec2 = [&da] { da[2].RemoveAt(100); };
			Assert::ExpectException<std::exception>(throwingvec2);

			auto throwingmat2 = [&da] { da[3].RemoveAt(100); };
			Assert::ExpectException<std::exception>(throwingmat2);

			auto throwingstring2 = [&da] {da[4].RemoveAt(100); };
			Assert::ExpectException<std::exception>(throwingstring2);

			auto throwingRTTI2 = [&da] {da[5].RemoveAt(100); };
			Assert::ExpectException<std::exception>(throwingRTTI2);


			da[0].RemoveAt();
			da[1].RemoveAt();
			da[2].RemoveAt();
			da[3].RemoveAt();
			da[4].RemoveAt();
			da[5].RemoveAt();

			Assert::AreEqual(size_t(2), da[0].Size());
			Assert::AreEqual(size_t(2), da[1].Size());
			Assert::AreEqual(size_t(2), da[2].Size());
			Assert::AreEqual(size_t(2), da[3].Size());
			Assert::AreEqual(size_t(2), da[4].Size());
			Assert::AreEqual(size_t(2), da[5].Size());



		}


	private:
		static _CrtMemState _startMemState;
		void CommonDatumTest(Datum& datum, DatumTypes type);




	};

	_CrtMemState DatumTest::_startMemState;




	void DatumTest::CommonDatumTest(Datum& datum, DatumTypes type)
	{
		datum.SetType(type);

		if (datum.Type() == DatumTypes::INT)
		{
			datum.PushBack(10);
			datum.PushBack(20);
			datum.PushBack(30);

			Assert::AreEqual(size_t(3), datum.Size());
			Assert::AreEqual(10, datum.Front<int32_t>());
			Assert::AreEqual(30, datum.Back<int32_t>());
		}

		if (datum.Type() == DatumTypes::FLOAT)
		{
			datum.PushBack(10.f);
			datum.PushBack(20.f);
			datum.PushBack(30.f);

			Assert::AreEqual(size_t(3), datum.Size());
			Assert::AreEqual(10.f, datum.Front<float>());
			Assert::AreEqual(30.f, datum.Back<float>());
		}

		if (datum.Type() == DatumTypes::VEC4)
		{
			glm::vec4 a1 = { 10.f, 20.f, 30.f, 40.f };
			glm::vec4 b1 = { 50.f, 60.f, 70.f, 80.f };
			glm::vec4 c1 = { 90.f, 100.f, 110.f, 120.f };

			datum.PushBack(a1);
			datum.PushBack(b1);
			datum.PushBack(c1);

			Assert::AreEqual(size_t(3), datum.Size());
			Assert::AreEqual(a1, datum.Front<glm::vec4>());
			Assert::AreEqual(c1, datum.Back<glm::vec4>());

		}

		if (datum.Type() == DatumTypes::MAT4)
		{
			glm::mat4 a1 = { {99.f,86.5f,74.7f,56.f}, {50.6f,41.6f,82.9f,44.9f}, {89.6f,52.3f,52.8f,3.5f}, {6.6f,59.4f,80.6f,34.1f} };
			glm::mat4 b1 = { {12.f, 13.f, 14.f, 15.f}, {12.f ,13.f, 14.f,15.f}, {12.f, 13.f, 14.f, 15.f}, {12.f, 13.f, 14.f, 15.f} };
			glm::mat4 c1 = { {59.4f,95.7f,97.f,1.9f}, {82.8f,79.3f,11.1f,72.4f}, {98.2f,32.1f,46.4f,87.5f}, {12.7f,83.5f,66.8f,43.3f} };

			datum.PushBack(a1);
			datum.PushBack(b1);
			datum.PushBack(c1);

			Assert::AreEqual(size_t(3), datum.Size());
			Assert::AreEqual(a1, datum.Front<glm::mat4>());
			Assert::AreEqual(c1, datum.Back<glm::mat4>());
		}


		if (datum.Type() == DatumTypes::STRING)
		{
			std::string a1 = "One";
			std::string b1 = "Two";
			std::string c1 = "Three";

			datum.PushBack(a1);
			datum.PushBack(b1);
			datum.PushBack(c1);

			Assert::AreEqual(size_t(3), datum.Size());
			Assert::AreEqual(a1, datum.Front<std::string>());
			Assert::AreEqual(c1, datum.Back<std::string>());
		}

		if (datum.Type() == DatumTypes::POINTER)
		{


			datum.PushBack(r);
			datum.PushBack(r2);
			datum.PushBack(r3);

			Assert::AreEqual(size_t(3), datum.Size());
			Assert::AreEqual(r->ToString(), datum.Front<RTTI*>()->ToString());
			Assert::AreEqual(r3->ToString(), datum.Back<RTTI*>()->ToString());
		}


	}

}