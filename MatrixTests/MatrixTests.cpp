#include "pch.h"
#include "CppUnitTest.h"
#include "../MultidimentionMatrixAllocator/allocator.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
	TEST_CLASS(MatrixTests)
	{
	public:
		TEST_METHOD(_CalculateSize)
		{
			size_t first = CalculateSize<char>({2, 3});
			Assert::AreEqual(first, 6ull);

			size_t second = CalculateSize<short>({ 3 });
			Assert::AreEqual(second, 6ull);

			size_t third = CalculateSize<int>({ 2, 3, 4, 5, 6 });
			Assert::AreEqual(third, 2ull * 3 * 4 * 5 * 6 * 4);
		}
		TEST_METHOD(_ReserveMemory_size_t_char)
		{
			_CrtMemState oldState;
			_CrtMemState newState;
			_CrtMemState diff;

			_CrtMemState oldState1;
			_CrtMemState newState1;
			_CrtMemState diff1;
			
			size_t n = CalculateSize<char>({ 2, 3 });
			void* memory = nullptr;
			_CrtMemCheckpoint(&oldState);

			memory = ReserveMemory(n);

			_CrtMemCheckpoint(&newState);

			_CrtMemDifference(&diff, &oldState, &newState);
			Assert::AreEqual(diff.lTotalCount, 6ull);

			_CrtMemCheckpoint(&oldState1);
			FreeMemory(memory);
			_CrtMemCheckpoint(&newState1);

			_CrtMemDifference(&diff1, &oldState1, &newState1);
			Assert::AreEqual(diff1.lTotalCount, 0ull);
		}
		TEST_METHOD(_ReserveMemory_size_t_int)
		{
			_CrtMemState oldState;
			_CrtMemState newState;
			_CrtMemState diff;

			_CrtMemState oldState1;
			_CrtMemState newState1;
			_CrtMemState diff1;

			size_t n = CalculateSize<int>({ 2, 3 });
			void* memory = nullptr;
			_CrtMemCheckpoint(&oldState);

			memory = ReserveMemory(n);

			_CrtMemCheckpoint(&newState);

			_CrtMemDifference(&diff, &oldState, &newState);

			Assert::AreEqual(diff.lTotalCount, 6ull * 4);

			_CrtMemCheckpoint(&oldState1);
			FreeMemory(memory);
			_CrtMemCheckpoint(&newState1);
			
			_CrtMemDifference(&diff1, &oldState1, &newState1);
			Assert::AreEqual(diff1.lTotalCount, 0ull);
		}
		TEST_METHOD(_CreateMultidimentionalMatrix_2d)
		{
			void* matrix3D = nullptr;
			matrix3D = CreateMultidimentionalMatrix<int>(matrix3D, 2, 3, 4);
			int*** matrixOfInt = (int***)matrix3D;
		}
	};
}
