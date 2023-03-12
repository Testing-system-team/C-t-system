#include "Header.h"
#include "User-System/Student.h"
#include "User-System/User_System.h"

using namespace User_System;

Security::HMAC_Generator Student::loginHashGen { std::basic_string<unsigned char>(reinterpret_cast<const unsigned char*>("Student\0Login"), 14) };
Security::HMAC_Generator Student::passHashGen { std::basic_string<unsigned char>(reinterpret_cast<const unsigned char*>("Student\0Password"), 17) };

Student::Student() : ID(0), User("", "", 0, 0, 1, 0), name(""), surname(""), patronymic(""), adress(""), phoneNumber("") {}

Student::Student(std::string name, std::string surname, std::string patronymic, std::string adress, std::string phoneNumber, std::string login, std::string password)
	: User(loginHashGen.generate_HMAC(login),
		passHashGen.generate_HMAC(password),
		0, 0, 1, 0), 
	name(name),surname(surname),patronymic(patronymic),adress(adress),phoneNumber(phoneNumber)
{}

Student::Student(const pt::ptree& s) : 
	ID(s.get<int>("ID")),
	User(s.get<std::string>("loginHash"), s.get<std::string>("passwordHash"), 0, 0, 1, 0),
	name(s.get<std::string>("name")),
	surname(s.get<std::string>("surname")),
	patronymic(s.get<std::string>("patronymic")),
	adress(s.get<std::string>("adress")),
	phoneNumber(s.get<std::string>("phoneNumber"))
{}

void Student::display() const
{
	std::cout 
		<< convertTypeName(typeid(*this).name()) << ":\n"
		<< name << "\n"
		<< surname << "\n"
		<< patronymic << "\n"
		<< adress << "\n"
		<< phoneNumber << "\n"
		<< _login << "\n"
		<< _password << "\n";
	system("pause");
}
std::string Student::GetName() const
{
	return name;
}
User_System::Student::operator Menu()
{
	Menu menu(L"Студент (" + std::to_wstring(id) + L')');
	menu[L"Показать"] = std::bind(&Student::display, this);
	return menu;
}
void User_System::Student::ChangeName(std::string name_)
{
	name = name_;
	std::cout << "Name was changed:\n";
	display();
	std::cout << "\n";
}
void User_System::Student::ChangeSurname(std::string surname_)
{
	surname = surname_;
	std::cout << "Surname was changed:\n";
	display();
	std::cout << "\n";
}
void User_System::Student::ChangePatronymic(std::string patronymic_)
{
	patronymic = patronymic_;
	std::cout << "Patronymic was changed:\n";
	display();
	std::cout << "\n";
}

void User_System::Student::ChangeAdress(std::string adress_)
{
	adress = adress_;
	std::cout << "Adress was changed:\n";
	display();
	std::cout << "\n";
}

void User_System::Student::ChangePhone(std::string phone_)
{
	phoneNumber = phone_;
	std::cout << "Phone was changed:\n";
	display();
	std::cout << "\n";
}

void User_System::Student::ChangeLogin(std::string login_)
{
	login = login_;
	std::cout << "Login was changed:\n";
	display();
	std::cout << "\n";
}

void User_System::Student::ChangePassword(std::string password_)
{
	password = password_;
	std::cout << "Password was changed:\n";
	display();
	std::cout << "\n";
}


const Security::HMAC_Generator User_System::Student::getLoginHashGen()
{
	return loginHashGen;
}
const Security::HMAC_Generator User_System::Student::getPassHashGen()
{
	return passHashGen;
}

void User_System::Student::setLogin(const std::string login)
{
	_login = loginHashGen.generate_HMAC(login);
}

void User_System::Student::setPassword(const std::string pass)
{
	_password = passHashGen.generate_HMAC(pass);
}

Student::operator pt::ptree()const
{
	pt::ptree stTags;
	stTags.put("ID", id);
	stTags.put("name", name);
	stTags.put("surname", surname);
	stTags.put("patronymic", patronymic);
	stTags.put("adress", adress);
	stTags.put("phoneNumber", phoneNumber);
	stTags.put("loginHash", login);
	stTags.put("passwordHash", password);
	return stTags;
}
//void Student::saveToFile(const Student& s)
//{
//	pt::ptree tree;
//
//	tree.add("List.students.student.name", s.name);
//	tree.add("List.students.student.surname", s.surname);
//	tree.add("List.students.student.patronymic", s.patronymic);
//	tree.add("List.students.student.adress", s.adress);
//	tree.add("List.students.student.phoneNumber", s.phoneNumber);
//	tree.add("List.students.student._login", s._login);
//	tree.add("List.students.student._password", s._password);
//
//	write_xml("student.xml", tree);
//	
//}