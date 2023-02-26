#pragma once
#include "User-System/DataManager.h"

namespace Auth_System
{
	class Authorization
	{
		User_System::User* currentUser;
		std::unique_ptr<User_System::DataManager>& managerPtr;
		void _firstLogin();
	public:
		Authorization(std::unique_ptr<User_System::DataManager>& managerPtr);
		void open();
		void studentRegistration();
		void login();
	};
}
