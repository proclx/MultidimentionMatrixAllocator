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
			_CrtMemState oldState;
			_CrtMemState newState;
			_CrtMemState diff;

			_CrtMemState oldState1;
			_CrtMemState newState1;
			_CrtMemState diff1;

			void* matrix2D = nullptr;
			short** matrixOfShort = nullptr;

			_CrtMemCheckpoint(&oldState);
			matrix2D = CreateMultidimentionalMatrix<short>(matrix2D, 2, 3);
			matrixOfShort = (short**)matrix2D;
			_CrtMemCheckpoint(&newState);

			_CrtMemDifference(&diff, &oldState, &newState);

			Assert::AreEqual(diff.lTotalCount, 20ull + sizeof(void*));

			_CrtMemCheckpoint(&oldState1);
			FreeMemory(matrix2D, 2, 3);
			_CrtMemCheckpoint(&newState1);

			_CrtMemDifference(&diff1, &oldState1, &newState1);
			Assert::AreEqual(diff1.lTotalCount, 0ull);
		}
		TEST_METHOD(_CreateMultidimentionalMatrix_3d)
		{
			_CrtMemState oldState;
			_CrtMemState newState;
			_CrtMemState diff;

			_CrtMemState oldState1;
			_CrtMemState newState1;
			_CrtMemState diff1;

			void* matrix3D = nullptr;
			short*** matrixOfShort = nullptr;

			_CrtMemCheckpoint(&oldState);
			matrix3D = CreateMultidimentionalMatrix<short>(matrix3D, 2, 2, 2);
			matrixOfShort = (short***)matrix3D;
			_CrtMemCheckpoint(&newState);

			_CrtMemDifference(&diff, &oldState, &newState);

			Assert::AreEqual(diff.lTotalCount, 2ull * 2 * 2 + 6 * sizeof(void*) + sizeof(void*));

			_CrtMemCheckpoint(&oldState1);
			FreeMemory(matrix3D, 2, 2, 2);
			_CrtMemCheckpoint(&newState1);

			_CrtMemDifference(&diff1, &oldState1, &newState1);
			Assert::AreEqual(diff1.lTotalCount, 0ull);
		}
		TEST_METHOD(_2dMatrixIsOK)
		{
			void* matrix2D = nullptr;
			matrix2D = CreateMultidimentionalMatrix<short>(matrix2D, 2, 3);
			short** matrixOfShort = (short**)matrix2D;

			for (unsigned i = 0; i < 2; ++i)
			{
				for (unsigned j = 0; j < 3; ++j)
				{
					matrixOfShort[i][j] = (i + j);
				}
			}

			for (unsigned i = 0; i < 2; ++i)
			{
				for (unsigned j = 0; j < 3; ++j)
				{
					Assert::AreEqual(matrixOfShort[i][j], (short)(i + j));
				}
			}
		}
	};
}
