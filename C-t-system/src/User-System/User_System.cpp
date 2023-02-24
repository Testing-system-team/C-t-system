#include "Header.h"
#include "User-System/User_System.h"

using namespace User_System;

std::string User_System::convertTypeName(const std::string typeName)
{
	if (auto result = typeName.rfind(':'); result != typeName.npos)
		return std::string(typeName.begin() + result + 1, typeName.end());
	return std::string();
}

std::unique_ptr<User> User_System::getUser(const std::pair<std::string, pt::ptree>& user)
{
	if (user.first == convertTypeName(typeid(Student).name()))
	{
		return std::make_unique<Student>(user.second);
	}
	else if (user.first == convertTypeName(typeid(Admin).name()))
	{
		return std::make_unique<Admin>(user.second);
	}
	return std::unique_ptr<User>();
}
