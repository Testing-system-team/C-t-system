#include "Header.h"
#include "Auth-System/Authorization.h"

void Auth_System::Authorization::_firstLogin()
{
	std::string login;
	std::string password;

	std::cout << u8"Первый запуск (создание аккаунта администратора):\n"
		<< u8"Введите логин: ";
	std::getline(std::cin, login);
	std::cout << u8"Введите пароль: ";
	std::getline(std::cin, password);

	managerPtr->addUser(std::make_unique<User_System::Admin>(login, password));
	currentUser = managerPtr->getAdmin().get();
}

Auth_System::Authorization::Authorization(User_System::DataManager* managerPtr)
	: managerPtr(managerPtr), currentUser(nullptr)
{}

void Auth_System::Authorization::open()
{
	if (!managerPtr->getAdmin())
		_firstLogin();
	else
	{
		int choice;
		std::cout
			<< u8"Что вы хотите сделать?\n"
			<< u8"1. Зарегистрироватся\n"
			<< u8"2. Войти\n"
			<< '\n'
			<< u8"Ваш выбор: ";

		std::cin >> choice;
		std::cin.ignore();

		switch (choice)
		{
		case 1: studentRegistration(); break;
		case 2: login(); break;
		}
	}
}

void Auth_System::Authorization::studentRegistration()
{
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string adress;
	std::string phone;
	std::string login;
	std::string password;

	std::cout << "\nname-> ";
	std::getline(std::cin, name);
	std::cout << "\nsurname-> ";
	std::getline(std::cin, surname);
	std::cout << "\npatronymic-> ";
	std::getline(std::cin, patronymic);
	std::cout << "\nadress-> ";
	std::getline(std::cin, adress);
	std::cout << "\nphone-> ";
	std::getline(std::cin, phone);
	do
	{
		std::cout << "\nlogin-> ";
		std::getline(std::cin, login);
		if (managerPtr->FindLogin(login))
			std::cout << "\nthis login already exist, choose another one->\n";
	} while (managerPtr->FindLogin(login));
	std::cout << "\npassword-> ";
	std::getline(std::cin, password);
	managerPtr->addUser(std::make_unique<User_System::Student>(
		name, surname, patronymic, adress, phone, login, password));
	currentUser = (managerPtr->getCatalog().GetStudents().end() - 1)->get();
}

void Auth_System::Authorization::login()
{
	std::string login;
	std::string password;

	do
	{
		std::cout << "\nlogin-> ";
		std::getline(std::cin, login);
		if (!managerPtr->FindLogin(login))
			std::cout << "\nuser not found->\n";
	} while (!managerPtr->FindLogin(login));

	if (User_System::Admin::getLoginHashGen().compare_HMAC(login, managerPtr->getAdmin()->login)) currentUser = managerPtr->getAdmin().get();
	else
		currentUser = std::find_if(managerPtr->getCatalog().GetStudents().begin(), managerPtr->getCatalog().GetStudents().end(),
			[login](auto& student)
			{
				return User_System::Student::getLoginHashGen().compare_HMAC(login, student->login);
			})->get();

	if (auto result = dynamic_cast<User_System::Student*>(currentUser))
	{
		do
		{
			std::cout << "\npassword-> ";
			std::getline(std::cin, password);
			if (!result->getPassHashGen().compare_HMAC(password, result->password))
				std::cout << "\nwrong password>\n";
		} while (!result->getPassHashGen().compare_HMAC(password, result->password));
		std::cout << "\nYou have been successfully authorised\n";
	}
	else if (auto result = dynamic_cast<User_System::Admin*>(currentUser))
	{
		do
		{
			std::cout << "\npassword-> ";
			std::getline(std::cin, password);
			if (!result->getPassHashGen().compare_HMAC(password, result->password))
				std::cout << "\nwrong password>\n";
		} while (!result->getPassHashGen().compare_HMAC(password, result->password));
		std::cout << "\nYou have been successfully authorised\n";
	}
}
