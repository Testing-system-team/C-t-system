#include "Header.h"
#include "User-System/User.h"

using namespace User_System;

User::User() : _login(""), _password(""), _permissions({0, 0, 0, 0}) {}

User::User(std::string login, std::string password, bool configureUsers, bool configureTests, bool passTests, bool watchStatistics)
	: _login(login), _password(password), _permissions({configureUsers, configureTests, passTests, watchStatistics})
{}

std::string User::getLogin() const
{
	return _login;
}

std::string User_System::User::getPassword() const
{
	return _password;
}

Permissions User_System::User::getPermissions() const
{
	return _permissions;
}

void User_System::User::setLogin(const std::string login)
{
	_login = login;
}

void User_System::User::setPassword(const std::string login)
{
	_password = password;
}
