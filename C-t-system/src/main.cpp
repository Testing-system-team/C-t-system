#include "Header.h"
#include "ID-System/ID_System.h"

//
// Классы для теста ID системы
//

class test : ID_System::ID<test> { 
public:
	test() {} 
	test(int id) : ID(id) { } 
};

class test_1 : ID_System::ID<test_1> {
	std::string test_str;
public:
	test_1() : ID(0), test_str("") {}
	test_1(std::string test_str) : test_str(test_str) {}
	void display() const { std::cout << test_str; }
};
// // //

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	ID_System d;
	try
	{
		test test1;
		auto test2 = std::make_unique<test>();
		test test3;

		// Воспроизведение ошибки, при создании не наследуемого ID
		/*ID_System::ID<void> test4;*/

		// Воспроизведение ошибки, при указании ID существующего в системе
		/*test test5(1);*/

		// 1 - Первое отображение всех ID в системе
		std::cout << "1:\n";
		for (auto id : d)
		{
			std::cout << id.first << ' ';
		}
		std::cout << "\n\n";

		// 2 - Отображение всех ID в системе, после удаления 2 ID
		std::cout << "2:\n";
		test2.reset();
		for (auto id : d)
		{
			std::cout << id.first << ' ';
		}
		std::cout << "\n\n";

		// 3 - Отображение всех ID в системе, после повторного создания 2 ID
		std::cout << "3:\n";
		test2 = std::make_unique<test>();
		for (auto id : d)
		{
			std::cout << id.first << ' ';
		}
		std::cout << "\n\n";

		

		// 4 - Тест поиска 3 ID, с сущностью test_1
		test_1 test4(u8"class test_1 с ID (4), найден");
		std::cout << "4:\n";
		if (auto result = ID_System::find_by_ID<test_1>(3))
			result->display();
		else
			std::cout << u8"class test_1 с ID (3), не найден";
		std::cout << "\n\n";

		// 5 - Тест поиска 4 ID, с сущностью test_1
		std::cout << "5:\n";
		if (auto result = ID_System::find_by_ID<test_1>(4))
			result->display();
		else
			std::cout << u8"class test_1 с ID (4), не найден";
		std::cout << "\n\n";

		// 6 - Тест поиска всех существующих сущностей в ID системе
		std::cout << "6:\n";
		std::cout << u8"Количество class test в системе: " << ID_System::find_all_entitys<test>().size() << "\n";
		std::cout << u8"Количество class test_1 в системе: " << ID_System::find_all_entitys<test_1>().size() << "\n";
	}
	catch (std::exception ex)
	{
		// Вывод ошибки
		std::cerr << u8"Ошибка в main: " << ex.what() << '\n';
	}

	// Отображение всех ID в системе, в конце программы
	for (auto id : d)
	{
		std::cout << id.first;
	}
}