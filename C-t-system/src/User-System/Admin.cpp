#include "Header.h"
#include "User-System/Admin.h"
#include "User-System/User_System.h"

using namespace User_System;

Security::HMAC_Generator Admin::loginHashGen { std::basic_string<unsigned char>(reinterpret_cast<const unsigned char*>("Admin\0Login"), 11), 4096, 32 };
Security::HMAC_Generator Admin::passHashGen { std::basic_string<unsigned char>(reinterpret_cast<const unsigned char*>("Admin\0Password"), 14), 4096, 32 };

Admin::Admin() : ID(0), User("", "", 1, 1, 0, 1) {}

Admin::Admin(std::string login, std::string password) : 
	User(loginHashGen.generate_HMAC(login),
		passHashGen.generate_HMAC(password),
		1, 1, 0, 1) 
{}

Admin::Admin(const pt::ptree& a) : 
	ID(a.get<int>("ID")),
	User(a.get<std::string>("loginHash"), a.get<std::string>("passwordHash"), 1, 1, 0, 1) 
{}


bool Admin::CheckLogin(Admin a,std::string login)
{
	return a._login == _login;
}

//void Admin::CreateAdmin()
//{
//	pt::ptree tree;
//	do
//	{
//		std::cout << "\nEnter login for Admin-> ";
//		std::getline(std::cin, _login);
//
//		std::cout << "\nEnter password for Admin-> ";
//		std::getline(std::cin, _password);
//	} while (_login == "" || _password == "");
//	Admin newAdmin(_login, _password);
//	tree.add_child("Users." + convertTypeName(typeid(*this).name()), newAdmin);
//	
//	pt::write_xml("Users.xml", tree);
//}
//

void Admin::Display() const
{
	std::cout << convertTypeName(typeid(*this).name()) << ": " << _login << "\n" << _password << "\n";
	system("pause");
}

User_System::Admin::operator Menu()
{
	Menu menu(L"������������� (" + std::to_wstring(id) + L')');
	menu[L"��������"] = std::bind(&Admin::Display, this);
	return menu;
}

const Security::HMAC_Generator User_System::Admin::getLoginHashGen()
{
	return loginHashGen;
}

const Security::HMAC_Generator User_System::Admin::getPassHashGen()
{
	return passHashGen;
}

//Admin Admin::loadData()
//{
//	pt::ptree tree;
//	//2 ������� ��� �� ��������� ����� � ������ ������
//	pt::read_xml("Users.xml", tree); 
//
//	BOOST_FOREACH(auto & admins, tree.get_child("Users"))
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
	stTags.put("ID", id);
	stTags.put("loginHash", _login);
	stTags.put("passwordHash", _password);
	return stTags;
}

bool Admin::CheckPassword(Admin a, std::string password)
{
	return a._password == password;
}
