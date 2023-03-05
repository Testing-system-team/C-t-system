#include "Header.h"

#ifdef _DEBUG
#include "Auth-System/Authorization.h"
#include "Testing/category.h"
#include "Menu/Menu.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	auto menuPtr = std::make_unique<Menu>(L"Главное меню");
	auto managerPtr = std::make_unique<User_System::DataManager>();
	auto authPtr = std::make_unique<Auth_System::Authorization>(managerPtr.get());
	User_System::User* currentUser = nullptr;

	Testing::test t = Testing::test("test", 11);
	t.addQuestion(Testing::question(u8"2+2?", u8"2", u8"3", u8"4", u8"4"));
	
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
		(*menuPtr)[L"Тесты"] += t;
	}
	if (currentUser->permissions.watchStatistics)
	{
		(*menuPtr)[L"Просмотр статистики"];
	}

	menuPtr->open(L"Ваш выбор: ");
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


