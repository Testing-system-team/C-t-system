#pragma once
#include "User-System/DataManager.h"

namespace User_System
{
	// Конвертирует type_name имя в чистое имя класса
	extern std::string convertTypeName(const std::string typeName);

	// Преобразует сущность из property_tree в пользователя
	extern std::unique_ptr<User> getUser(const std::pair<std::string, pt::ptree>& user);
}
