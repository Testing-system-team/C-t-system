#include "Header.h"

#ifdef _DEBUG
#include "User-System/Admin.h"

int main()
{
	User_System::Admin admin("d", "d");
	if (auto result = ID_System::find_by_ID<User_System::Admin>(2))
		result->Display();
}
#else
#include "Auth-System/Authorization.h"
#include "Menu/Menu.h"
#include "Testing/testManager.h"
#include "Testing/Statistic/statisticManager.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	auto menuPtr = std::make_unique<Menu>(L"Главное меню");
	auto userManagerPtr = std::make_unique<User_System::DataManager>();
	auto testManagerPtr = std::make_unique<Testing::testManager>();
	auto statisticManagerPtr = std::make_unique<Testing::Statistic::statisticManager>();
	auto authPtr = std::make_unique<Auth_System::Authorization>(userManagerPtr.get());
	User_System::User* currentUser = nullptr;

	authPtr->open();
	currentUser = authPtr->getCurrentUser();

	menuPtr->exit_name = L"Выход";
	menuPtr->back_name = L"Назад";

	if (currentUser->permissions.configureUsers)
	{
		userManagerPtr->name = L"Конфигурация пользователей";
		userManagerPtr->exit_name = L"Назад";
		(*menuPtr)[L"Конфигурация пользователей"] = std::bind(&User_System::DataManager::open, 
			userManagerPtr.get(), statisticManagerPtr.get(), 
			L"Ваш выбор: ");
	}
	if (currentUser->permissions.configureTests)
	{
		testManagerPtr->exit_name = L"Назад";
		(*menuPtr)[L"Конфигурация тестов"] = std::bind(&Testing::testManager::open, testManagerPtr.get(), L"Ваш выбор: ");
	}
	if (currentUser->permissions.passTests)
	{
		for (auto& category : testManagerPtr->getcategories())
		{
			int count = MultiByteToWideChar(CP_UTF8, 0, category.getname().c_str(), category.getname().length(), NULL, 0);
			std::wstring categoryName(count, 0);
			MultiByteToWideChar(CP_UTF8, 0, category.getname().c_str(), category.getname().length(), &categoryName[0], count);

			for (auto& test : category.getTests())
			{
				Menu testMenu = test;

				if (auto user = dynamic_cast<User_System::Student*>(currentUser))
				{
					testMenu[L"Пройти тест"] = std::bind([](const int userId, const std::string categoryName, Testing::test* test, Testing::Statistic::statisticManager* statisticManagerPtr)
					{
						test->startTest();
						statisticManagerPtr->addStatistic(Testing::Statistic::Statistic(userId, categoryName, *test));
						std::cin.ignore();
					}, user->id, category.getname(), &test, statisticManagerPtr.get());
				}

				(*menuPtr)[L"Пройти тесты"][categoryName][testMenu.name] = (std::vector<Menu>)testMenu;
			}
		}

		if (auto user = dynamic_cast<User_System::Student*>(currentUser))
		{
			(*menuPtr)[L"Показать свою статистику"] = [&]()
			{
				for (auto& statistic : statisticManagerPtr->getStatistics())
				{
					if (statistic.getUserId() == user->id)
					{
						statistic.display();
						std::cout << "---------------------------------------------\n";
					}
				}
				system("pause");
			};
		}
	}
	if (currentUser->permissions.watchStatistics)
	{
		(*menuPtr)[L"Просмотр статистики"] = [&]()
		{
			std::cout << u8"Статистика всех пользователей:\n\n";
			for (auto& statistic : statisticManagerPtr->getStatistics())
			{
				statistic.display();
				std::cout << "---------------------------------------------\n";
			}
			system("pause");
		};
	}

	menuPtr->open(L"Ваш выбор: ");
}
#endif // 


