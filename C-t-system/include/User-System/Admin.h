#pragma once
#include "User-System/StudentList.h"
#include "User-System/User.h"
#include "ID-System/ID_System.h"
#include "Security/HMAC_Generator.h"

namespace User_System
{
	class Admin : public User, public ID_System::ID<Admin>
	{
		static Security::HMAC_Generator loginHashGen;
		static Security::HMAC_Generator passHashGen;
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

		static const Security::HMAC_Generator getLoginHashGen();
		static const Security::HMAC_Generator getPassHashGen();
	};
}
