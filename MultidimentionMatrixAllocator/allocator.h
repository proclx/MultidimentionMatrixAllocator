#pragma once
#include <initializer_list>
#include <cstring>

template <typename ReserveType, typename T>
size_t CalculateSize(std::initializer_list<T> list)
{
	size_t result = sizeof(ReserveType);
	for (auto val: list)
	{
		result *= val;
	}
	return result;
}

template <typename ReserveType, typename T>
void* ReserveMemory(std::initializer_list<T> list, size_t& saveSize = nullptr)
{
    size_t result = sizeof(ReserveType);
    for (auto val : list)
    {
        result *= val;
    }
    char* memory = new char[result];
    saveSize = result;
    return memory;
}

void* ReserveMemory(size_t mem);
void FreeMemory(void* memory, size_t size = 0);

template<typename ... Args>
void FreeMemory(void* memory, size_t size, Args ... args)
{
    void** currRow = (void**)memory;
    for (unsigned i = 0; i < size; ++i)
    {
        FreeMemory(currRow[i], args ...);
    }
    delete[] memory;
}

template<typename MatrixType>
void* CreateMultidimentionalMatrix(void* p, size_t size)
{
    p = ReserveMemory(size * sizeof(MatrixType));
    return p;
}

template <typename MatrixType, typename ... Args>
void* CreateMultidimentionalMatrix(void* p, size_t size, Args ... args)
{
    size_t pointerSize = size * sizeof(void*);

    p = ReserveMemory(pointerSize);

    void** nextSubArray = (void**)p;
    for (unsigned i = 0; i < size; ++i)
    {
        nextSubArray[i] = CreateMultidimentionalMatrix<MatrixType>(nextSubArray[i], args ...);
    }
    return p;
}