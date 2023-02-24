#pragma once
#include "User-System/Permissions.h"

namespace User_System
{
	class User
	{
	protected:
		std::string _login;
		std::string _password;

		Permissions _permissions;
	public:
		User();
		User(std::string login, std::string password, bool configureUsers, bool configureTests, bool passTests, bool watchStatistics);
		virtual operator pt::ptree() const = 0;

		std::string getLogin() const;
		std::string getPassword() const;
		Permissions getPermissions() const;

		void setLogin(const std::string login);
		void setPassword(const std::string login);

		__declspec(property(get = getLogin, put = setLogin)) std::string login;
		__declspec(property(get = getPassword, put = setPassword)) std::string password;
		__declspec(property(get = getPermissions)) Permissions permissions;
	};
}
