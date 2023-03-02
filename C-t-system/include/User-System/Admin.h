#pragma once
#include "User-System/StudentList.h"
#include "User-System/User.h"
#include "ID-System/ID_System.h"
#include "Security/HMAC_Generator.h"

namespace User_System
{
	class Admin : public User, public ID_System::ID<Admin>
	{
		//
		// Хэш генераторы
		//

		static Security::HMAC_Generator loginHashGen;
		static Security::HMAC_Generator passHashGen;
		// // //
	public:
		//
		// Конструкторы
		//

		Admin();
		Admin(std::string login, std::string password);
		Admin(const pt::ptree& a);
		// // //

		// Сравнение хэша логинов
		bool CheckLogin(Admin a, std::string login);

		// Сравнение хэша паролей
		bool CheckPassword(Admin a, std::string password);

		/*void CreateAdmin();*/

		// Вывод администратора на экран
		void Display()const;

		/*static Admin loadData();*/

		// Преобразование в property_tree
		operator pt::ptree()const;

		//
		// Геттеры хэш генераторов
		//

		static const Security::HMAC_Generator getLoginHashGen();
		static const Security::HMAC_Generator getPassHashGen();
		// // //
	};
}
