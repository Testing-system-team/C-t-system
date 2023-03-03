#pragma once
#include "User-System/Permissions.h"

namespace User_System
{
	class User
	{
	protected:
		//
		// Аттрибуты
		//

		std::string _login;
		std::string _password;

		Permissions _permissions;
		// // //
	public:
		//
		// Конструкторы
		//

		User();
		User(std::string login, std::string password, bool configureUsers, bool configureTests, bool passTests, bool watchStatistics);
		// // //

		// Преобразование в property_tree
		virtual operator pt::ptree() const = 0;

		//
		// Геттеры
		//

		std::string getLogin() const;
		std::string getPassword() const;
		Permissions getPermissions() const;
		// // //

		//
		// Сеттеры
		//

		void setLogin(const std::string login);
		void setPassword(const std::string login);
		// // //

		//
		// Декларация property
		//

		__declspec(property(get = getLogin, put = setLogin)) std::string login;
		__declspec(property(get = getPassword, put = setPassword)) std::string password;
		__declspec(property(get = getPermissions)) Permissions permissions;
		// // //
	};
}
