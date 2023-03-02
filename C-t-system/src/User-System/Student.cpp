#include "Header.h"
#include "User-System/Student.h"

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
	std::cout << name << "\n";
	std::cout << surname << "\n";
	std::cout << patronymic << "\n";
	std::cout << adress << "\n";
	std::cout << phoneNumber << "\n";
	std::cout << _login << "\n";
	std::cout << _password << "\n";
}
std::string Student::GetName() const
{
	return name;
}
const Security::HMAC_Generator User_System::Student::getLoginHashGen()
{
	return loginHashGen;
}
const Security::HMAC_Generator User_System::Student::getPassHashGen()
{
	return passHashGen;
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