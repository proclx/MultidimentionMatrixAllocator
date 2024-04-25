#include "allocator.h"
#include <iostream>

using namespace std;

int main() 
{
    void* matrix3D = nullptr;
    matrix3D = CreateMultidimentionalMatrix<int>(matrix3D, 2, 3, 4);
    int*** matrixOfInt = (int***)matrix3D;

    for (unsigned i = 0; i < 2; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
        {
            for (unsigned k = 0; k < 4; ++k)
            {
                matrixOfInt[i][j][k] = 1;
            }
        }
    }

    for (unsigned i = 0; i < 2; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
        {
            for (unsigned k = 0; k < 4; ++k)
            {
                std::cout << matrixOfInt[i][j][k] << ' ';
            }
        }
    }

    _CrtMemState oldState;
    _CrtMemState newState;
    _CrtMemState diff;

    _CrtMemCheckpoint(&oldState);
    FreeMemory(matrixOfInt, 2, 3, 4);
    _CrtMemCheckpoint(&newState);

    _CrtMemDifference(&diff, &newState, &oldState);

    std::cout << diff.lTotalCount << std::endl;

    return 0;
}
