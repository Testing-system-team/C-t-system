#include "Header.h"
#include "Auth-System/Authorization.h"

void Auth_System::Authorization::_firstLogin()
{
	std::string login;
	std::string password;

	std::cout << u8"������ ������ (�������� �������� ��������������):\n"
		<< u8"������� �����: ";
	std::getline(std::cin, login);
	std::cout << u8"������� ������: ";
	std::getline(std::cin, password);

	managerPtr->addUser(std::make_unique<User_System::Admin>(login, password));
	currentUser = managerPtr->getAdmin().get();
}

Auth_System::Authorization::Authorization(std::unique_ptr<User_System::DataManager>& managerPtr)
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
			<< u8"��� �� ������ �������?\n"
			<< u8"1. �����������������\n"
			<< u8"2. �����\n"
			<< '\n'
			<< u8"��� �����: ";

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
	currentUser = &*(managerPtr->getCatalog().GetStudents().end() - 1);
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

	if (managerPtr->getAdmin()->login == login) currentUser = managerPtr->getAdmin().get();
	else
	currentUser = &*std::find_if(managerPtr->getCatalog().GetStudents().begin(), managerPtr->getCatalog().GetStudents().end(),
		[login](auto student)
		{
			return student.login == login;
		});

	do
	{
		std::cout << "\npassword-> ";
		std::getline(std::cin, password);
		if (password != currentUser->password)
			std::cout << "\nwrong password> ";
	} while (password != currentUser->password);
	std::cout << "\nYou have been successfully authorised\n";
}
