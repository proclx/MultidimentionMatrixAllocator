template <typename ReserveType, typename T>
size_t CalculateSize(std::initializer_list<T> list)
функція призначена для обчислення кількості байт, що потрібні для створення багатовимірної матриці, створена з оглядом на майбутнє, якщо я або хтось інший придумає кращий спосіб ініціалізації матриці(без використання вказівників, натомість просто суцільною ділянкою пам'яті)

template <typename ReserveType, typename T>
void* ReserveMemory(std::initializer_list<T> list, size_t& saveSize = nullptr)
та 
void* ReserveMemory(size_t mem)
рекурсивна(перша) функція ReserveMemory слугує для побудову масиву, який вміщатиме всю матрицю(також функція розрахована на майбутнє, якщо вдастся розробити функцію, що виділятиме всю матрицю неперервною). Вони виконують усі побудови пов'язані з вказівниками на наступні ділянки пам'яті, поки не відбудеться виклик void* ReserveMemory(size_t mem), яка побудує фінальні масиви, де вже будуть зберігатися значення. Також ReserveMemory(size_t mem) використовується у функції побудови матриці (яка працює вже зараз), займається виділенням усієї пам'яті (як для вказівників так і для самого масиву значень)

template<typename ... Args>
void FreeMemory(void* memory, size_t size, Args ... args)
та
void FreeMemory(void* memory, size_t size = 0);
працють за таким же принципом як і сім'я функцій ReserveMemory, тільки видаляють матрицю (new стало delete[]).

template <typename MatrixType, typename ... Args>
void* CreateMultidimentionalMatrix(void* p, size_t size, Args ... args)
та
template<typename MatrixType>
void* CreateMultidimentionalMatrix(void* p, size_t size)
Функція використовується для створення багатовимірного масиву заданого розміру. Викликається з різною кількістю параметрів залежно від розмірності масиву. Рекурсивно викликає сама себе для створення багатовимірного масиву. 

Зауваження* функції CalculateSize, void* ReserveMemory(std::initializer_list<T> list, size_t& saveSize = nullptr), з'явилися в ході невдалих спроб, проте вони можуть бути корисними у майбутньому, саме тому я не бачу причин їх видаляти.

Тести
Виконують перевірку всіх методів, у тому числі CalculateSize та void* ReserveMemory(std::initializer_list<T> list, size_t& saveSize = nullptr). Окрему увагу я приділив безпеці пам'яті, для чого використана бібліотека <memory>. 
