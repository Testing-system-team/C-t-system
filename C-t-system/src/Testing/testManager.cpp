#include "Header.h"
#include "Testing/testManager.h"
using namespace Testing;
void Testing::testManager::_addCategory()
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring name;

	std::cout << u8"Введите название категории: ";
	std::getline(std::wcin, name);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), &str[0], count, NULL, NULL);

	addcategory(category(str));
}
void Testing::testManager::_categoryChange(tstring tchoice)
{
	bool category_exit = 0;
	while (!category_exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;
		int count = 1;

		system("cls");

		tMenu::tcout << L"Изменить категории: " << '\n';

		for (auto& category : categories)
		{
			int wstr_count = MultiByteToWideChar(CP_UTF8, 0, category.getname().c_str(), category.getname().length(), NULL, 0);
			std::wstring wstr(wstr_count, 0);
			MultiByteToWideChar(CP_UTF8, 0, category.getname().c_str(), category.getname().length(), &wstr[0], wstr_count);

			tcout << count << ". " << wstr << '\n';
			count++;
		}
		tMenu::tcout << "0. " << back_name << '\n'
			<< '\n'
			<< tchoice;
		tMenu::tcin >> choice;
		tMenu::tcin.ignore();

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif
		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice >= count)
				throw std::runtime_error("Bad choice");

			system("cls");

			if (choice)
			{
				_categoryMenu(tchoice, categories.begin() + choice - 1);

				if (!categories.size()) category_exit = 1;
			}
			else category_exit = 1;
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}
void Testing::testManager::_categoryMenu(tstring tchoice, std::vector<category>::iterator category)
{
	bool categoryMenu_exit = 0;

	while (!categoryMenu_exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;

		int count = MultiByteToWideChar(CP_UTF8, 0, category->getname().c_str(), category->getname().length(), NULL, 0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_UTF8, 0, category->getname().c_str(), category->getname().length(), &wstr[0], count);

		system("cls");

		tcout << wstr << ":\n"
			<< L"1. Добавить тест\n"
			<< L"2. Изменить имя\n";
		if (category->getTests().size())
		{
			tcout << L"3. Изменить тесты\n"
				<< L"4. Удалить\n";
		}
		else
			tcout << L"3. Удалить\n";

		std::wcout << L"0. " << back_name << '\n'
			<< '\n'
			<< tchoice;
		tcin >> choice;
		tcin.ignore();

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif

		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice > 4 || choice > 3 && !category->getTests().size())
				throw std::runtime_error("Bad choice");

			system("cls");

			switch (choice)
			{
			case 0: categoryMenu_exit = 1; break;
			case 1: _addTest(*category); break;
			case 2: _changeCategoryName(*category); break;
			case 3:
				if (!category->getTests().size())
				{
					categories.erase(category);
					saveData();
					categoryMenu_exit = 1;
				}
				else
					_testChange(tchoice, *category);
				break;
			default: 
				categories.erase(category);
				saveData();
				categoryMenu_exit = 1;
			}
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}
void Testing::testManager::_addTest(category& category)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring name;

	std::cout << u8"Введите название теста: ";
	std::getline(std::wcin, name);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), &str[0], count, NULL, NULL);

	category.addtest(test(str));
	saveData();
}
void Testing::testManager::_changeCategoryName(category& category)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring name;

	std::cout << u8"Введите новое название категории: ";
	std::getline(std::wcin, name);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), &str[0], count, NULL, NULL);

	category.setName(str);
	saveData();
}
void Testing::testManager::_testChange(tstring tchoice, category& category)
{
	bool test_exit = 0;
	while (!test_exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;
		int count = 1;

		system("cls");

		tMenu::tcout << L"Изменить тесты: " << '\n';

		for (auto& test : category.getTests())
		{
			int wstr_count = MultiByteToWideChar(CP_UTF8, 0, test.getname().c_str(), test.getname().length(), NULL, 0);
			std::wstring wstr(wstr_count, 0);
			MultiByteToWideChar(CP_UTF8, 0, test.getname().c_str(), test.getname().length(), &wstr[0], wstr_count);

			tcout << count << ". " << wstr << '\n';
			count++;
		}
		tMenu::tcout << "0. " << back_name << '\n'
			<< '\n'
			<< tchoice;
		tMenu::tcin >> choice;
		tMenu::tcin.ignore();

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif
		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice >= count)
				throw std::runtime_error("Bad choice");

			if (choice)
			{
				_testMenu(tchoice, category, category.getTests().begin() + choice - 1);

				if (!category.getTests().size()) test_exit = 1;
			}
			else test_exit = 1;
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}
void Testing::testManager::_testMenu(tstring tchoice, category& category, std::vector<test>::iterator test)
{
	bool testMenu_exit = 0;

	while (!testMenu_exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;

		int count = MultiByteToWideChar(CP_UTF8, 0, test->getname().c_str(), test->getname().length(), NULL, 0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_UTF8, 0, test->getname().c_str(), test->getname().length(), &wstr[0], count);

		system("cls");

		tcout << wstr << ":\n"
			<< L"1. Добавить вопрос\n"
			<< L"2. Изменить имя\n";
		if (test->getQuestions().size())
		{
			tcout << L"3. Изменить вопросы\n"
				<< L"4. Удалить\n";
		}
		else
			tcout << L"3. Удалить\n";

		std::wcout << L"0. " << back_name << '\n'
			<< '\n'
			<< tchoice;
		tcin >> choice;
		tcin.ignore();

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif

		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice > 4 || choice > 3 && !test->getQuestions().size())
				throw std::runtime_error("Bad choice");

			system("cls");

			switch (choice)
			{
			case 0: testMenu_exit = 1; break;
			case 1: _addQuestion(*test); break;
			case 2: _changeTestName(*test); break;
			case 3:
				if (!test->getQuestions().size())
				{
					category.getTests().erase(test);
					saveData();
					testMenu_exit = 1;
				}
				else
					_questionsChange(tchoice, *test);
				break;
			default:
				category.getTests().erase(test);
				saveData();
				testMenu_exit = 1;
			}
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}
void Testing::testManager::_addQuestion(test& test)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring data;
	std::wstring a;
	std::wstring b;
	std::wstring c;
	std::wstring rightAnswer;

	std::cout << u8"Введите вопрос: ";
	std::getline(std::wcin, data);
	std::cout << u8"Введите вариант ответа \"a\": ";
	std::getline(std::wcin, a);
	std::cout << u8"Введите вариант ответа \"b\": ";
	std::getline(std::wcin, b);
	std::cout << u8"Введите вариант ответа \"c\": ";
	std::getline(std::wcin, c);
	std::cout << u8"Введите правильный ответ: ";
	std::getline(std::wcin, rightAnswer);
	_setmode(_fileno(stdin), prevIn);

	int count_data = WideCharToMultiByte(CP_UTF8, 0, &data[0], data.size(), NULL, 0, NULL, NULL);
	int count_a = WideCharToMultiByte(CP_UTF8, 0, &a[0], a.size(), NULL, 0, NULL, NULL);
	int count_b = WideCharToMultiByte(CP_UTF8, 0, &b[0], b.size(), NULL, 0, NULL, NULL);
	int count_c = WideCharToMultiByte(CP_UTF8, 0, &c[0], c.size(), NULL, 0, NULL, NULL);
	int count_rightAnswer = WideCharToMultiByte(CP_UTF8, 0, &rightAnswer[0], rightAnswer.size(), NULL, 0, NULL, NULL);
	std::string str_data(count_data, 0);
	std::string str_a(count_a, 0);
	std::string str_b(count_b, 0);
	std::string str_c(count_c, 0);
	std::string str_rightAnswer(count_rightAnswer, 0);
	WideCharToMultiByte(CP_UTF8, 0, &data[0], data.size(), &str_data[0], count_data, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, &a[0], a.size(), &str_a[0], count_a, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, &b[0], b.size(), &str_b[0], count_b, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, &c[0], c.size(), &str_c[0], count_c, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, &rightAnswer[0], rightAnswer.size(), &str_rightAnswer[0], count_rightAnswer, NULL, NULL);

	test.addQuestion(question(str_data, str_a, str_b, str_c, str_rightAnswer));
	saveData();
}
void Testing::testManager::_changeTestName(test& test)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring name;

	std::cout << u8"Введите новое название теста: ";
	std::getline(std::wcin, name);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &name[0], name.size(), &str[0], count, NULL, NULL);

	test.setName(str);
	saveData();
}
void Testing::testManager::_questionsChange(tstring tchoice, test& test)
{
	bool question_exit = 0;
	while (!question_exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;
		int count = 1;

		system("cls");

		tMenu::tcout << L"Изменить вопросы: " << '\n';

		for (auto& question : test.getQuestions())
		{
			int wstr_count = MultiByteToWideChar(CP_UTF8, 0, question.getData().c_str(), question.getData().length(), NULL, 0);
			std::wstring wstr(wstr_count, 0);
			MultiByteToWideChar(CP_UTF8, 0, question.getData().c_str(), question.getData().length(), &wstr[0], wstr_count);

			tcout << count << ". " << wstr << '\n';
			count++;
		}
		tMenu::tcout << "0. " << back_name << '\n'
			<< '\n'
			<< tchoice;
		tMenu::tcin >> choice;
		tMenu::tcin.ignore();

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif
		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice >= count)
				throw std::runtime_error("Bad choice");

			if (choice)
			{
				_questionMenu(tchoice, test, test.getQuestions().begin() + choice - 1);

				if (!test.getQuestions().size()) question_exit = 1;
			}
			else question_exit = 1;
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}
void Testing::testManager::_questionMenu(tstring tchoice, test& test, std::vector<question>::iterator question)
{
	bool questionMenu_exit = 0;

	while (!questionMenu_exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;

		int count = MultiByteToWideChar(CP_UTF8, 0, question->getData().c_str(), question->getData().length(), NULL, 0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_UTF8, 0, question->getData().c_str(), question->getData().length(), &wstr[0], count);

		system("cls");

		tcout << wstr << ":\n"
			<< L"1. Изменить вопрос\n"
			<< L"2. Изменить вариант ответа \"a\"\n"
			<< L"3. Изменить вариант ответа \"b\"\n"
			<< L"4. Изменить вариант ответа \"c\"\n"
			<< L"5. Изменить правильный вариант ответа\n"
			<< L"6. Удалить\n"
			<< L"0. " << back_name << '\n'
			<< '\n'
			<< tchoice;
		tcin >> choice;
		tcin.ignore();

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif

		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice > 6)
				throw std::runtime_error("Bad choice");

			system("cls");

			switch (choice)
			{
			case 0: questionMenu_exit = 1; break;
			case 1: _changeQuestionData(*question); break;
			case 2: _changeQuestionA(*question); break;
			case 3: _changeQuestionB(*question); break;
			case 4: _changeQuestionC(*question); break;
			case 5: _changeQuestionRightAnswer(*question); break;
			default:
				test.getQuestions().erase(question);
				saveData();
				questionMenu_exit = 1;
			}
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}
void Testing::testManager::_changeQuestionData(question& question)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring data;

	std::cout << u8"Введите новый вопрос: ";
	std::getline(std::wcin, data);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &data[0], data.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &data[0], data.size(), &str[0], count, NULL, NULL);

	question.Data = str;
	saveData();
}
void Testing::testManager::_changeQuestionA(question& question)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring a;

	std::cout << u8"Введите новый вопрос: ";
	std::getline(std::wcin, a);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &a[0], a.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &a[0], a.size(), &str[0], count, NULL, NULL);

	question.A = str;
	saveData();
}
void Testing::testManager::_changeQuestionB(question& question)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring b;

	std::cout << u8"Введите новый вопрос: ";
	std::getline(std::wcin, b);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &b[0], b.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &b[0], b.size(), &str[0], count, NULL, NULL);

	question.B = str;
	saveData();
}
void Testing::testManager::_changeQuestionC(question& question)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring c;

	std::cout << u8"Введите новый вопрос: ";
	std::getline(std::wcin, c);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &c[0], c.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &c[0], c.size(), &str[0], count, NULL, NULL);

	question.C = str;
	saveData();
}
void Testing::testManager::_changeQuestionRightAnswer(question& question)
{
	auto prevIn = _setmode(_fileno(stdin), _O_U16TEXT);
	std::wstring rightAnswer;

	std::cout << u8"Введите новый вопрос: ";
	std::getline(std::wcin, rightAnswer);
	_setmode(_fileno(stdin), prevIn);

	int count = WideCharToMultiByte(CP_UTF8, 0, &rightAnswer[0], rightAnswer.size(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, &rightAnswer[0], rightAnswer.size(), &str[0], count, NULL, NULL);

	question.RightAnswer = str;
	saveData();
}
Testing::testManager::testManager() : Menu(L"Конфигурация тестов"), fileName("Tests.xml")
{
	exit_name = L"Выход";
	back_name = L"Назад";
	loadData();
}
Testing::testManager::testManager(std::string fileName) : Menu(L"Конфигурация тестов"), fileName(fileName)
{
	exit_name = L"Выход";
	back_name = L"Назад";
	loadData();
}
void Testing::testManager::display()
{
	if (categories.size() == 0)
	{
		std::cout << u8" Категорії не були додані\n";
	}
	else
	{
		for (category& c : categories)
		{
			c.display();
		}
	}


}

void Testing::testManager::loadData()
{
	categories.clear();

	if (std::filesystem::exists(fileName))
	{
		pt::ptree tree;
		pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);

		try
		{
			for (auto& c : tree.get_child("Categories"))
			{
				categories.push_back(category(c.second.get<std::string>("name")));
				for (auto& t : c.second.get_child("Tests"))
				{
					categories[categories.size() - 1].addtest(test(t.second.get<std::string>("name")));

					for (auto& q : t.second.get_child("questions"))
					{

						std::string data = q.second.get<std::string>("data");
						std::string a = q.second.get<std::string>("a");
						std::string b = q.second.get<std::string>("b");
						std::string c = q.second.get<std::string>("c");
						std::string rightanswer = q.second.get<std::string>("rightAnswer");
						categories[categories.size() - 1].
							getTests()[categories[categories.size() - 1].getTests().size() - 1].
							addQuestion(question(data, a, b, c, rightanswer));
					}
				}
			}
		}
		catch (pt::ptree_bad_path& ex)
		{
			std::cerr << "pt::ptree_bad_path: " << ex.what() << '\n';
			system("pause");
		}
	}
}

void Testing::testManager::saveData()
{
	pt::xml_writer_settings<std::string> settings('\t', 1);
	pt::ptree tree;
	int k = 0;

	for (category& c : categories)
		tree.add_child("Categories.Category", c);

	pt::write_xml(fileName, tree, std::locale(), settings);
}

void Testing::testManager::addcategory(const Testing::category& c)
{
	categories.push_back(c);
	saveData();
}

std::vector<category>& Testing::testManager::getcategories()
{
	return categories;
}

void Testing::testManager::open(tstring tchoice) noexcept
{
	exit = 0;

	while (!exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = 0;

		system("cls");

		tMenu::tcout << name << ": " << '\n';

		tcout << L"1. Добавить категорию\n";
		if (categories.size()) tcout << L"2. Изменить категории\n";
		std::wcout << L"0. " << exit_name << '\n'
			<< '\n'
			<< tchoice;
		tcin >> choice;

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif

		try
		{
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice > 2 || choice > 1 && !categories.size())
				throw std::runtime_error("Bad choice");

			system("cls");

			switch (choice)
			{
			case 0: exit = 1; break;
			case 1: _addCategory(); break;
			default: _categoryChange(tchoice);
			}
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}

