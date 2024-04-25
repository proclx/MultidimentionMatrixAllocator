#include "allocator.h"
#include <iostream>

using namespace std;

int main() 
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
			std::cout << matrixOfShort[i][j] << ' ';
		}
		std::cout << std::endl;
	}

    return 0;
}