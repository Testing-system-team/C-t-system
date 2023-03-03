#pragma once
#include "User-System/DataManager.h"

namespace User_System
{
	// ������������ type_name ��� � ������ ��� ������
	extern std::string convertTypeName(const std::string typeName);

	// ����������� �������� �� property_tree � ������������
	extern std::unique_ptr<User> getUser(const std::pair<std::string, pt::ptree>& user);
}
