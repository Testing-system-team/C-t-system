#pragma once
#include "User-System/Admin.h"
#include "User-System/Student.h"
#include "User-System/StudentList.h"
#include "User-System/DataManager.h"

namespace User_System
{
	extern std::string convertTypeName(const std::string typeName);
	extern std::unique_ptr<User> getUser(const std::pair<std::string, pt::ptree>& user);
}
