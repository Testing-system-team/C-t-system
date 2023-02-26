#include "Header.h"
#include "User-System/Permissions.h"

using namespace User_System;

Permissions::operator pt::ptree() const
{
	pt::ptree permissionsTag;
	permissionsTag.put("configureUsers", configureUsers);
	permissionsTag.put("configureTests", configureTests);
	permissionsTag.put("passTests", passTests);
	permissionsTag.put("watchStatistics", watchStatistics);
	return permissionsTag;
}