#pragma once
#include "User-System/StudentList.h"
#include "User-System/User.h"

namespace User_System
{
	class Admin : public User
	{
	public:
		Admin();
		Admin(std::string login, std::string password);
		Admin(const pt::ptree& a);
		bool CheckLogin(Admin a, std::string login);
		bool CheckPassword(Admin a, std::string password);
		void CreateAdmin();
		void Display()const;
		/*static Admin loadData();*/
		operator pt::ptree()const;
	};
}
