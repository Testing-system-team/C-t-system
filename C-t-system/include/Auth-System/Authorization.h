#pragma once
#include "User-System/DataManager.h"

namespace Auth_System
{
	class Authorization
	{
		// Текущий авторизованный пользователь
		User_System::User* currentUser;

		// Указатель на меннеджер данных
		User_System::DataManager* managerPtr;

		// Регистрация администратора
		void _firstLogin();
	public:
		// Конструктор
		Authorization(User_System::DataManager* managerPtr);

		// Открывает меню авторизации
		void open();

		// Регистрация студента
		void studentRegistration();

		// Вход
		void login();

		// Возвращает текущего пользователя
		User_System::User* getCurrentUser();
	};
}
