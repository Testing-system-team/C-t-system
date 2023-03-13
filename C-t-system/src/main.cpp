#include "Header.h"

#ifdef _DEBUG
#include "Auth-System/Authorization.h"

#include "Testing/testManager.h"
#include "Menu/Menu.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	/*
	* 	auto menuPtr = std::make_unique<Menu>(L"Главное меню");
	auto managerPtr = std::make_unique<User_System::DataManager>();
	auto authPtr = std::make_unique<Auth_System::Authorization>(managerPtr.get());
	User_System::User* currentUser = nullptr;

	Testing::category c = Testing::category(u8"математика");
	//c.addtest(Testing::test(u8"Тест з арифметики", 10));
	c.display();
	authPtr->open();
	currentUser = authPtr->getCurrentUser();

	menuPtr->exit_name = L"Выход";
	menuPtr->back_name = L"Назад";

	if (currentUser->permissions.configureUsers)
	{
		managerPtr->name = L"Конфигурация пользователей";
		managerPtr->exit_name = L"Назад";
		(*menuPtr)[L"Конфигурация пользователей"] = std::bind(&User_System::DataManager::open, managerPtr.get(), L"Ваш выбор: ");
	}
	if (currentUser->permissions.configureTests)
	{
		(*menuPtr)[L"Конфигурация тестов"];
	}

	if (currentUser->permissions.passTests)
	{
		(*menuPtr)[L"Тесты"] += t;
	}
	
	if (currentUser->permissions.watchStatistics)
	{
		(*menuPtr)[L"Просмотр статистики"];
	}

	menuPtr->open(L"Ваш выбор: ");
	*/

	Testing::testManager manager;
	manager.loadData();
	manager.display();

	
	
	/*
	manager.addcategory(Testing::category(u8"математика"));
	manager.getcategories()[0].addtest(Testing::test(u8"Тест з арифметики", 10));
	manager.getcategories()[0].getTests()[0].addQuestion(Testing::question(u8"2+2?", u8"2", u8"3", u8"4", u8"4"));
	manager.getcategories()[0].getTests()[0].addQuestion(Testing::question(u8"4+4?", u8"2", u8"8", u8"4", u8"8"));
	manager.display();
    	
	
	manager.getcategories()[0].getTests()[0].startTest();
	*/


	
	
	
}
#else
#include "Auth-System/Authorization.h"
#include "Menu/Menu.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	auto menuPtr = std::make_unique<Menu>(L"Главное меню");
	auto managerPtr = std::make_unique<User_System::DataManager>();
	auto authPtr = std::make_unique<Auth_System::Authorization>(managerPtr.get());
	User_System::User* currentUser = nullptr;

	authPtr->open();
	currentUser = authPtr->getCurrentUser();

	menuPtr->exit_name = L"Выход";
	menuPtr->back_name = L"Назад";

	if (currentUser->permissions.configureUsers)
	{
		(*menuPtr)[L"Конфигурация пользователей"];
	}
	if (currentUser->permissions.configureTests)
	{
		(*menuPtr)[L"Конфигурация тестов"];
	}
	if (currentUser->permissions.passTests)
	{
		(*menuPtr)[L"Тесты"];
	}
	if (currentUser->permissions.watchStatistics)
	{
		(*menuPtr)[L"Просмотр статистики"];
	}

	menuPtr->open(L"Ваш выбор: ");
}
#endif // 


