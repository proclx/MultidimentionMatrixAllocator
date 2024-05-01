template <typename ReserveType, typename T>
size_t CalculateSize(std::initializer_list<T> list)
функція призначена для обчислення кількості байт, що потрібні для створення багатовимірної матриці, створена з оглядом на майбутнє, якщо я або хтось інший придумає кращий спосіб ініціалізації матриці(без використання вказівників, натомість просто суцільною ділянкою пам'яті)

template <typename ReserveType, typename T>
void* ReserveMemory(std::initializer_list<T> list, size_t& saveSize = nullptr)
та 
void* ReserveMemory(size_t mem)
рекурсивна(перша) функція ReserveMemory слугує для побудову масиву вказівників, на наступні ділянки пам'яті. Вони виконують усі побудови пов'язані з вказівниками на наступні ділянки пам'яті, поки не відбудеться виклик void* ReserveMemory(size_t mem), яка побудує фінальні масиви, де вже будуть зберігатися значення.

template<typename ... Args>
void FreeMemory(void* memory, size_t size, Args ... args)
та
void FreeMemory(void* memory, size_t size = 0);
працють за таким же принципом як і сім'я функцій ReserveMemory, тільки видаляють матрицю (new стало delete[]).


