#include "Header.h"
#include "User-System/Admin.h"
#include "User-System/DataManager.h"

using namespace User_System;

Admin::Admin() : User("", "", 1, 1, 0, 1) {}

Admin::Admin(std::string login, std::string password) : User(login, password, 1, 1, 0, 1) {}

Admin::Admin(const pt::ptree& a) : User(a.get<std::string>("loginHash"), a.get<std::string>("passwordHash"), 1, 1, 0, 1) {}


bool Admin::CheckLogin(Admin a,std::string login)
{
	if (a._login == _login)
		return true;
	return false;
}

void Admin::CreateAdmin()
{
	pt::ptree tree;
	do
	{
		std::cout << "\nEnter login for Admin-> ";
		std::getline(std::cin, _login);

		std::cout << "\nEnter password for Admin-> ";
		std::getline(std::cin, _password);
	} while (login == "" || password == "");
	Admin newAdmin(_login, _password);
	tree.add_child("List.admin", newAdmin);
	
	pt::write_xml("Admin.xml", tree);
}


void Admin::Display() const
{
	std::cout << _login << "\n" << _password << "\n";
}

//Admin Admin::loadData()
//{
//	pt::ptree tree;
//	//2 зчитуємо дані із вказаного файла у дерево данних
//	pt::read_xml("Admin.xml", tree); 
//
//	BOOST_FOREACH(auto & admins, tree.get_child("List"))
//	{
//	
//		std::string login = admins.second.get<std::string>("loginHash");
//		std::string password = admins.second.get<std::string>("loginHash");
//		
//
//		
//		Admin a(login, password);
//		if(login==""||password=="")
//		{
//			std::cout << "\nYou need to register";
//			a.CreateAdmin();
//			login = admins.second.get<std::string>("loginHash");
//			password = admins.second.get<std::string>("passwordHash");
//		}
//		return a;
//	}
//
//
//}
Admin::operator pt::ptree()const
{
	pt::ptree stTags;
	
	stTags.put("loginHash", _login);
	stTags.put("passwordHash", _password);
	return stTags;
}

bool Admin::CheckPassword(Admin a, std::string password)
{
	if (a._password == password)
		return true;
	return false;
}
