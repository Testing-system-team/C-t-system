#include "Header.h"
#include "User-System/DataManager.h"
#include "User-System/Student.h"
#include "User-System/StudentList.h"
#include "User-System/User_System.h"
#include "Security/HMAC_Generator.h"

using namespace User_System;

DataManager::DataManager() : fileName("Users.xml") { loadData(); }

void DataManager::display() const
{
	studentCatalog.display();
}
void DataManager::displayByName(std::string login) const
{
	studentCatalog.displayByLogin(login);
}

void DataManager::loadData()
{
	if (std::filesystem::exists(fileName))
	{
		pt::ptree tree;

		pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);

		BOOST_FOREACH(auto & user, tree.get_child("Users"))
		{
			if (user.first == convertTypeName(typeid(Student).name()))
				studentCatalog.AddStudent(std::make_unique<Student>(user.second));
			else if (user.first == convertTypeName(typeid(Admin).name()))
				admin = std::make_unique<Admin>(user.second);
		}
	}
}

bool DataManager::FindLogin(std::string login) const
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		if (user.first == convertTypeName(typeid(Student).name()))
		{
			if (Student::getLoginHashGen().compare_HMAC(login, user.second.get<std::string>("loginHash")))
				return true;
		}
		else if (user.first == convertTypeName(typeid(Admin).name()))
			if (Admin::getLoginHashGen().compare_HMAC(login, user.second.get<std::string>("loginHash")))
				return true;
	}
	return false;
	
}

bool DataManager::CheckPassword(std::string password) const
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		if (user.first == convertTypeName(typeid(Student).name()))
		{
			if (Student::getPassHashGen().compare_HMAC(password, user.second.get<std::string>("passwordHash")))
				return true;
		}
		else if (user.first == convertTypeName(typeid(Admin).name()))
			if (Admin::getPassHashGen().compare_HMAC(password, user.second.get<std::string>("passwordHash")))
				return true;
	}
	return false;
}

void User_System::DataManager::addUser(std::unique_ptr<User> user)
{
	pt::xml_writer_settings<std::string> settings('\t', 1);
	pt::ptree tree;
	if (std::filesystem::exists(fileName)) pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	tree.add_child("Users." + convertTypeName(typeid(*user).name()), *user);

	write_xml(fileName, tree, std::locale(), settings);

	if (typeid(*user) == typeid(Student)) studentCatalog.AddStudent(std::move((std::unique_ptr<User_System::Student>&)user));
	else if (typeid(*user) == typeid(Admin)) admin = std::move((std::unique_ptr<User_System::Admin>&)(user));
}

StudentList& DataManager::getCatalog()
{
	return studentCatalog;
}

std::unique_ptr<User_System::Admin>& User_System::DataManager::getAdmin()
{
	return admin;
}
