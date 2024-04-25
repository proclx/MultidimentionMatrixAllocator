#include "allocator.h"

void* ReserveMemory(size_t mem)
{
	char* memory = new char[mem];
	return (void*)memory;
}

void FreeMemory(void* memory, size_t size)
{
	delete[] memory;
	memory = nullptr;
}
